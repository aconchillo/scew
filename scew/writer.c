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

#include "xwriter.h"

#include "str.h"

#include "xerror.h"

#include <assert.h>


// Private

static bool print_eol_ (scew_writer *writer);
static bool print_indent_ (scew_writer *writer);
static bool print_element_header_ (scew_writer *writer,
                                   scew_element const *element,
                                   bool *closed);


// Public

void
scew_writer_set_indented (scew_writer *writer, bool indented)
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

bool
scew_writer_close (scew_writer *writer)
{
  assert (writer != NULL);

  return (writer->close != NULL) ? writer->close (writer) : true;
}

void
scew_writer_free (scew_writer *writer)
{
  if (writer != NULL)
    {
      scew_writer_close (writer);
      free (writer);
    }
}

bool
scew_writer_print_tree (scew_writer *writer, scew_tree const *tree)
{
  assert (writer != NULL);
  assert (tree != NULL);

  XML_Char const *version = scew_tree_xml_version (tree);
  XML_Char const *encoding = scew_tree_xml_encoding (tree);
  scew_tree_standalone standalone = scew_tree_xml_standalone (tree);

  bool result = writer->printf (writer, _XT("<?xml version=\"%s\""), version);
  if (encoding)
    {
      result = result && writer->printf (writer, _XT(" encoding=\"%s\""),
                                         encoding);
    }
  if (result)
    {
      switch (standalone)
        {
        case scew_tree_standalone_unknown:
          break;
        case scew_tree_standalone_no:
          result = writer->printf (writer, _XT(" standalone=\"no\""));
          break;
        case scew_tree_standalone_yes:
          result = writer->printf (writer, _XT(" standalone=\"yes\""));
          break;
        };
    }

  result = result && writer->printf (writer, _XT(" ?>\n"));

  result = result && scew_writer_print_element (writer, scew_tree_root (tree));

  if (!result)
    {
      scew_error_set_last_error_ (scew_error_io);
    }

  return result;
}

bool
scew_writer_print_element (scew_writer *writer, scew_element const *element)
{
  assert (writer != NULL);
  assert (element != NULL);

  bool result = print_indent_ (writer);

  bool closed = true;

  result = result && print_element_header_ (writer, element, &closed);

  if (!closed)
    {
      result = result && scew_writer_print_element_children (writer, element);

      XML_Char const *contents = scew_element_contents (element);
      if (contents != NULL)
        {
          result = result && writer->printf (writer, contents);
        }
      else
        {
          result = result && print_indent_ (writer);
        }
      result = result && writer->printf (writer, _XT ("</%s>"),
                                         scew_element_name (element));
      result = result && print_eol_ (writer);
    }

  if (!result)
    {
      scew_error_set_last_error_ (scew_error_io);
    }

  return result;
}

bool
scew_writer_print_element_children (scew_writer *writer,
                                    scew_element const  *element)
{
  assert (writer != NULL);
  assert (element != NULL);

  unsigned int indent = writer->indent;

  bool result = true;
  scew_list *list = scew_element_children (element);
  while (result && (list != NULL))
    {
      writer->indent = indent + 1;

      scew_element *child = scew_list_data (list);
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


bool
scew_writer_print_element_attributes (scew_writer *writer,
                                      scew_element const *element)
{
  assert (writer != NULL);
  assert (element != NULL);

  bool result = true;
  scew_list *list = scew_element_attributes (element);
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

bool
scew_writer_print_attribute (scew_writer *writer,
                             scew_attribute const *attribute)
{
  assert (writer != NULL);
  assert (attribute != NULL);

  bool result = writer->printf (writer,
                                _XT (" %s=\"%s\""),
                                scew_attribute_name (attribute),
                                scew_attribute_value (attribute));

  if (!result)
    {
      scew_error_set_last_error_ (scew_error_io);
    }

  return result;
}


// Private

bool
print_eol_ (scew_writer *writer)
{
  assert (writer != NULL);

  bool result = true;

  if (writer->indented)
    {
      result = writer->printf (writer, _XT ("\n"));
    }

  return result;
}

bool
print_indent_ (scew_writer *writer)
{
  assert (writer != NULL);

  bool result = true;

  if (writer->indented)
    {
      unsigned int i = 0;
      unsigned int spaces = writer->indent * writer->spaces;
      for (i = 0; result && (i < spaces); ++i)
        {
          result = writer->printf (writer, _XT (" "));
        }
    }

  return result;
}

bool
print_element_header_ (scew_writer *writer,
                       scew_element const *element,
                       bool *closed)
{
  assert (writer != NULL);
  assert (element != NULL);

  bool result = writer->printf (writer,
                                _XT ("<%s"),
                                scew_element_name (element));

  result = result && scew_writer_print_element_attributes (writer, element);

  XML_Char const *contents = scew_element_contents (element);
  scew_element *parent = scew_element_parent (element);

  *closed = false;
  scew_list *list = scew_element_children (element);
  if ((contents == NULL) && (list == NULL) && (parent != NULL))
    {
      result = result && writer->printf (writer, _XT ("/>"));
      result = result && print_eol_ (writer);
      *closed = true;
    }
  else
    {
      result = result && writer->printf (writer, _XT (">"));
      if (contents == NULL)
        {
	  result = result && print_eol_ (writer);
        }
    }

  return result;
}
