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

static void print_eol_ (scew_writer *writer);
static void print_indent_ (scew_writer *writer);
static bool print_element_header_ (scew_writer *writer,
                                   scew_element const *element);


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

  return writer->close (writer);
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

void
scew_writer_print_tree (scew_writer *writer, scew_tree const *tree)
{
  assert (writer != NULL);
  assert (tree != NULL);

  XML_Char const *version = scew_tree_xml_version (tree);
  XML_Char const *encoding = scew_tree_xml_encoding (tree);
  bool standalone = scew_tree_xml_standalone (tree);

  writer->printf (writer, _XT("<?xml version=\"%s\""), version);
  if (encoding)
    {
      writer->printf (writer, _XT(" encoding=\"%s\""), encoding);
    }
  writer->printf (writer, _XT(" standalone=\"%s\"?>\n"),
                  standalone ? _XT ("yes") : _XT ("no"));

  scew_writer_print_element (writer, scew_tree_root (tree));
}

void
scew_writer_print_element (scew_writer *writer, scew_element const *element)
{
  assert (writer != NULL);
  assert (element != NULL);

  print_indent_ (writer);

  bool closed = print_element_header_ (writer, element);

  if (!closed)
    {
      scew_writer_print_element_children (writer, element);

      XML_Char const *contents = scew_element_contents (element);
      if (contents != NULL)
        {
          writer->printf (writer, contents);
        }
      else
        {
          print_indent_ (writer);
        }
      writer->printf (writer, _XT ("</%s>"), scew_element_name (element));
      print_eol_ (writer);
    }
}

void
scew_writer_print_element_children (scew_writer *writer,
                                    scew_element const  *element)
{
  assert (writer != NULL);
  assert (element != NULL);

  unsigned int indent = writer->indent;

  scew_list *list = scew_element_children (element);
  while (list != NULL)
    {
      writer->indent = indent + 1;

      scew_element *child = scew_list_data (list);
      scew_writer_print_element (writer, child);
      list = scew_list_next (list);
    }

  writer->indent = indent;
}


void
scew_writer_print_element_attributes (scew_writer *writer,
                                      scew_element const *element)
{
  assert (writer != NULL);
  assert (element != NULL);

  scew_list *list = scew_element_attributes (element);
  while (list != NULL)
    {
      scew_attribute *attribute = scew_list_data (list);
      scew_writer_print_attribute (writer, attribute);
      list = scew_list_next (list);
    }
}

void
scew_writer_print_attribute (scew_writer *writer,
                             scew_attribute const *attribute)
{
  assert (writer != NULL);
  assert (attribute != NULL);

  if (attribute != NULL)
    {
      writer->printf (writer,
                      _XT (" %s=\"%s\""),
                      scew_attribute_name (attribute),
                      scew_attribute_value (attribute));
    }
}


// Private

void
print_eol_ (scew_writer *writer)
{
  assert (writer != NULL);

  if (writer->indented)
    {
      writer->printf (writer, _XT ("\n"));
    }
}

void
print_indent_ (scew_writer *writer)
{
  assert (writer != NULL);

  if (writer->indented)
    {
      unsigned int spaces = writer->indent * writer->spaces;
      for (unsigned int i = 0; i < spaces; ++i)
        {
          writer->printf (writer, _XT (" "));
        }
    }
}

bool
print_element_header_ (scew_writer *writer, scew_element const *element)
{
  assert (writer != NULL);
  assert (element != NULL);

  writer->printf (writer, _XT ("<%s"), scew_element_name (element));

  scew_writer_print_element_attributes (writer, element);

  XML_Char const *contents = scew_element_contents (element);
  scew_element *parent = scew_element_parent (element);

  bool closed = false;
  scew_list *list = scew_element_children (element);
  if ((contents == NULL) && (list == NULL) && (parent != NULL))
    {
      writer->printf (writer, _XT ("/>"));
      print_eol_ (writer);
      closed = true;
    }
  else
    {
      writer->printf (writer, _XT (">"));
      if (contents == NULL)
        {
	  print_eol_ (writer);
        }
    }

  return closed;
}
