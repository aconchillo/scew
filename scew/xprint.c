/**
 *
 * @file     xprint.c
 * @brief    SCEW private tree type declaration
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Sun Mar 30, 2003 13:23
 *
 * @if copyright
 *
 * Copyright (C) 2003, 2004, 2005, 2006, 2007 Aleix Conchillo Flaque
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * @endif
 */

#include "xprint.h"

#include "element.h"
#include "str.h"

#include <assert.h>

/* indentation size (in whitespaces) */
static int const indent_size = 3;

void
indent_print (FILE *out, unsigned int indent)
{
  unsigned int i = 0;

  for (i = 0; i < indent * indent_size; i++)
    {
      scew_fprintf (out, _XT (" "));
    }
}

void
tree_print (scew_tree const *tree, FILE *out)
{
  static XML_Char const *version = _XT("1.0");
#ifdef XML_UNICODE_WCHAR_T
  static XML_Char const *encoding = _XT("UTF-16");
#else
  static XML_Char const *encoding = _XT("UTF-8");
#endif /* XML_UNICODE_WCHAR_T */

  XML_Char const *tree_version = scew_tree_xml_version (tree);
  XML_Char const *tree_encoding = scew_tree_xml_encoding (tree);
  int tree_standalone = scew_tree_xml_standalone (tree);

  scew_fprintf (out,
		_XT("<?xml version=\"%s\" encoding=\"%s\" standalone=\"%s\"?>\n\n"),
		(tree_version == NULL ? version : tree_version),
		(tree_encoding == NULL ? encoding : tree_encoding),
		(tree_standalone > 0 ? _XT ("yes") : _XT ("no")));

  element_print (scew_tree_root (tree), out, 0);
}

void
element_print (scew_element const *element, FILE *out, unsigned int indent)
{
  unsigned int closed = 0;
  scew_list *list = NULL;
  scew_element *parent = NULL;
  XML_Char const *contents = NULL;

  assert (element != NULL);

  indent_print (out, indent);
  scew_fprintf (out, _XT ("<%s"), scew_element_name (element));

  list = scew_element_attributes (element);
  while (list != NULL)
    {
      scew_attribute *attribute = scew_list_data (list);
      attribute_print (attribute, out);
      list = scew_list_next (list);
    }

  contents = scew_element_contents (element);
  parent = scew_element_parent (element);

  list = scew_element_children (element);
  if ((contents == NULL) && (list == NULL) && (parent != NULL))
    {
      scew_fprintf (out, _XT ("/>\n"));
      closed = 1;
    }
  else
    {
      scew_fprintf (out, _XT (">"));
      if (contents == NULL)
        {
	  scew_fprintf (out, _XT ("\n"));
        }
    }

  while (list != NULL)
    {
      scew_element *child = scew_list_data (list);
      element_print (child, out, indent + 1);
      list = scew_list_next (list);
    }

  if (contents != NULL)
    {
      scew_fprintf (out, _XT ("%s"), contents);
    }
  else if (!closed)
    {
      indent_print (out, indent);
    }

  if (!closed)
    {
      scew_fprintf (out, _XT ("</%s>\n"), scew_element_name (element));
    }
}

void
attribute_print (scew_attribute const *attribute, FILE *out)
{
  if (attribute != NULL)
    {
      scew_fprintf (out, _XT (" %s=\"%s\""),
                    scew_attribute_name (attribute),
                    scew_attribute_value (attribute));
    }
}
