/**
 * @file     writer.c
 * @brief    writer.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Sep 11, 2003 00:39
 *
 * @if copyright
 *
 * Copyright (C) 2003-2008 Aleix Conchillo Flaque
 *
 * SCEW is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SCEW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * @endif
 */

#include "writer.h"

#include "str.h"

#include "xerror.h"

#include <assert.h>


/* Private */

enum
  {
    DEFAULT_INDENT_SPACES_ = 3  /**< Default number of indent spaces */
  };

struct scew_writer
{
  scew_bool indented;
  unsigned int indent;
  unsigned int spaces;
  scew_writer_hooks *hooks;
};

static scew_bool print_eol_ (scew_writer *writer);
static scew_bool print_indent_ (scew_writer *writer);
static scew_bool print_element_header_ (scew_writer *writer,
                                        scew_element const *element,
                                        scew_bool *closed);


/* Public */

scew_writer*
scew_writer_create (scew_writer_hooks *hooks)
{
  scew_writer *writer = calloc (1, sizeof (scew_writer));

  if (writer != NULL)
    {
      writer->hooks = hooks;

      scew_writer_set_indented (writer, SCEW_TRUE);
      scew_writer_set_indent_spaces (writer, DEFAULT_INDENT_SPACES_);
    }

  return writer;
}

void*
scew_writer_interface (scew_writer *writer)
{
  return (writer != NULL) ? writer->hooks : NULL;
}

scew_bool
scew_writer_close (scew_writer *writer)
{
  assert (writer != NULL);
  assert (writer->hooks != NULL);

  scew_bool result = (writer->hooks->close != NULL)
    ? writer->hooks->close (writer)
    : SCEW_TRUE;

  if (!result)
    {
      scew_error_set_last_error_ (scew_error_io);
    }

  return result;
}

void
scew_writer_free (scew_writer *writer)
{
  if ((writer != NULL)
      && (writer->hooks != NULL)
      && (writer->hooks->free != NULL))
    {
      writer->hooks->free (writer);
      free (writer);
    }
}

void
scew_writer_set_indented (scew_writer *writer, scew_bool indented)
{
  assert (writer != NULL);

  writer->indented = indented;
}

void
scew_writer_set_indent_spaces (scew_writer *writer, unsigned int spaces)
{
  assert (writer != NULL);

  writer->spaces = spaces;
}

scew_bool
scew_writer_print_tree (scew_writer *writer, scew_tree const *tree)
{
  scew_bool result = SCEW_TRUE;
  XML_Char const *version = NULL;
  XML_Char const *encoding = NULL;
  scew_tree_standalone standalone = scew_tree_standalone_unknown;

  assert (writer != NULL);
  assert (tree != NULL);
  assert (writer->hooks != NULL);

  scew_writer_hooks *hooks = writer->hooks;

  version = scew_tree_xml_version (tree);
  encoding = scew_tree_xml_encoding (tree);
  standalone = scew_tree_xml_standalone (tree);

  result = hooks->printf (writer, _XT("<?xml version=\"%s\""), version);

  if (encoding)
    {
      result = result && hooks->printf (writer, _XT(" encoding=\"%s\""),
                                        encoding);
    }

  if (result)
    {
      switch (standalone)
        {
        case scew_tree_standalone_unknown:
          break;
        case scew_tree_standalone_no:
          result = hooks->printf (writer, _XT(" standalone=\"no\""));
          break;
        case scew_tree_standalone_yes:
          result = hooks->printf (writer, _XT(" standalone=\"yes\""));
          break;
        };
    }

  result = result && hooks->printf (writer, _XT("?>\n"));

  result = result && scew_writer_print_element (writer, scew_tree_root (tree));

  if (!result)
    {
      scew_error_set_last_error_ (scew_error_io);
    }

  return result;
}

scew_bool
scew_writer_print_element (scew_writer *writer, scew_element const *element)
{
  scew_bool result = SCEW_TRUE;
  scew_bool closed = SCEW_TRUE;

  assert (writer != NULL);
  assert (element != NULL);
  assert (writer->hooks != NULL);

  scew_writer_hooks *hooks = writer->hooks;

  result = print_indent_ (writer);

  result = result && print_element_header_ (writer, element, &closed);

  if (!closed)
    {
      XML_Char const *contents = NULL;

      result = result && scew_writer_print_element_children (writer, element);

      contents = scew_element_contents (element);
      if (contents != NULL)
        {
          result = result && hooks->printf (writer, contents);
        }
      else
        {
          result = result && print_indent_ (writer);
        }
      result = result && hooks->printf (writer, _XT ("</%s>"),
                                        scew_element_name (element));
      result = result && print_eol_ (writer);
    }

  if (!result)
    {
      scew_error_set_last_error_ (scew_error_io);
    }

  return result;
}

scew_bool
scew_writer_print_element_children (scew_writer *writer,
                                    scew_element const  *element)
{
  unsigned int indent = 0;
  scew_list *list = NULL;
  scew_bool result = SCEW_TRUE;

  assert (writer != NULL);
  assert (element != NULL);

  indent = writer->indent;

  list = scew_element_children (element);
  while (result && (list != NULL))
    {
      scew_element *child = scew_list_data (list);

      writer->indent = indent + 1;

      result = scew_writer_print_element (writer, child);
      list = scew_list_next (list);
    }

  writer->indent = indent;

  if (!result)
    {
      scew_error_set_last_error_ (scew_error_io);
    }

  return result;
}


scew_bool
scew_writer_print_element_attributes (scew_writer *writer,
                                      scew_element const *element)
{
  scew_bool result = SCEW_TRUE;
  scew_list *list = NULL;

  assert (writer != NULL);
  assert (element != NULL);

  list = scew_element_attributes (element);
  while (result && (list != NULL))
    {
      scew_attribute *attribute = scew_list_data (list);
      result = scew_writer_print_attribute (writer, attribute);
      list = scew_list_next (list);
    }

  if (!result)
    {
      scew_error_set_last_error_ (scew_error_io);
    }

  return result;
}

scew_bool
scew_writer_print_attribute (scew_writer *writer,
                             scew_attribute const *attribute)
{
  scew_bool result = SCEW_TRUE;

  assert (writer != NULL);
  assert (attribute != NULL);
  assert (writer->hooks != NULL);

  result = writer->hooks->printf (writer,
                                  _XT (" %s=\"%s\""),
                                  scew_attribute_name (attribute),
                                  scew_attribute_value (attribute));

  if (!result)
    {
      scew_error_set_last_error_ (scew_error_io);
    }

  return result;
}


/* Private */

scew_bool
print_eol_ (scew_writer *writer)
{
  scew_bool result = SCEW_TRUE;

  assert (writer != NULL);
  assert (writer->hooks != NULL);

  if (writer->indented)
    {
      result = writer->hooks->printf (writer, _XT ("\n"));
    }

  return result;
}

scew_bool
print_indent_ (scew_writer *writer)
{
  scew_bool result = SCEW_TRUE;

  assert (writer != NULL);
  assert (writer->hooks != NULL);

  if (writer->indented)
    {
      unsigned int i = 0;
      unsigned int spaces = writer->indent * writer->spaces;
      for (i = 0; result && (i < spaces); ++i)
        {
          result = writer->hooks->printf (writer, _XT (" "));
        }
    }

  return result;
}

scew_bool
print_element_header_ (scew_writer *writer,
                       scew_element const *element,
                       scew_bool *closed)
{
  scew_bool result = SCEW_TRUE;
  scew_list *list = NULL;
  XML_Char const *contents = NULL;

  assert (writer != NULL);
  assert (element != NULL);
  assert (writer->hooks != NULL);

  scew_writer_hooks *hooks = writer->hooks;

  result = hooks->printf (writer, _XT ("<%s"), scew_element_name (element));

  result = result && scew_writer_print_element_attributes (writer, element);

  contents = scew_element_contents (element);

  *closed = SCEW_FALSE;
  list = scew_element_children (element);
  if ((contents == NULL) && (list == NULL))
    {
      result = result && hooks->printf (writer, _XT ("/>"));
      result = result && print_eol_ (writer);
      *closed = SCEW_TRUE;
    }
  else
    {
      result = result && hooks->printf (writer, _XT (">"));
      if (contents == NULL)
        {
	  result = result && print_eol_ (writer);
        }
    }

  return result;
}

