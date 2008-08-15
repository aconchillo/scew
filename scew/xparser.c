/**
 * @file     xparser.c
 * @brief    xparser.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Tue Dec 03, 2002 00:21
 *
 * @if copyright
 *
 * Copyright (C) 2002-2008 Aleix Conchillo Flaque
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

#include "xparser.h"

#include "str.h"

#include "xerror.h"

#include <assert.h>


// Private

struct stack_element
{
  scew_element* element;
  struct stack_element* prev;
};

// Expat callback for XML declaration.
static void expat_xmldecl_handler_ (void *data,
                                    XML_Char const *version,
                                    XML_Char const *encoding,
                                    int standalone);

// Expat callback for starting elements.
static void expat_start_handler_ (void *data,
                                  XML_Char const *elem,
                                  XML_Char const **attr);

// Expat callback for ending elements.
static void expat_end_handler_ (void *data, XML_Char const *elem);

// Expat callback for element contents.
static void expat_char_handler_ (void *data, XML_Char const *s, int len);

// Pushes an element into the stack.
static stack_element* stack_push_ (stack_element **stack,
                                   scew_element *element);

// Pops an element from the stack.
static scew_element* stack_pop_ (stack_element **stack);


// Protected

bool
scew_parser_expat_init_ (scew_parser *parser)
{
  assert (parser != NULL);

  parser->parser = XML_ParserCreate (NULL);

  bool result = (parser->parser != NULL);

  if (result)
    {
      XML_SetXmlDeclHandler (parser->parser, expat_xmldecl_handler_);
      XML_SetElementHandler (parser->parser,
                             expat_start_handler_,
                             expat_end_handler_);
      XML_SetCharacterDataHandler (parser->parser, expat_char_handler_);
      XML_SetUserData (parser->parser, parser);
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return result;
}


// Private

void
expat_xmldecl_handler_ (void *data,
                        XML_Char const *version,
                        XML_Char const *encoding,
                        int standalone)
{
  scew_parser *parser = (scew_parser *) data;

  if (parser == NULL)
    {
      return;
    }

  if (parser->tree == NULL)
    {
      parser->tree = scew_tree_create ();
    }

  if (parser->tree == NULL)
    {
      return;
    }

  if (version != NULL)
    {
      scew_tree_set_xml_version (parser->tree, scew_strdup (version));
    }
  if (encoding != NULL)
    {
      scew_tree_set_xml_encoding (parser->tree, scew_strdup (encoding));
    }

  scew_tree_set_xml_standalone (parser->tree, standalone + 1);
}

void
expat_start_handler_ (void *data, XML_Char const *elem, XML_Char const **attr)
{
  int i = 0;
  scew_parser *parser = (scew_parser *) data;

  if (parser == NULL)
    {
      return;
    }

  if ((parser->tree == NULL) || (scew_tree_root (parser->tree) == NULL))
    {
      if (parser->tree == NULL)
        {
	  parser->tree = scew_tree_create ();
        }
      parser->current = scew_tree_set_root (parser->tree, elem);
    }
  else
    {
      stack_push_ (&parser->stack, parser->current);
      parser->current = scew_element_add (parser->current, elem);
    }

  for (i = 0; attr[i]; i += 2)
    {
      scew_element_add_attribute_pair (parser->current, attr[i], attr[i + 1]);
    }
}

void
expat_end_handler_ (void *data, XML_Char const *elem)
{
  scew_element *current = NULL;
  XML_Char const *contents = NULL;
  scew_parser *parser = (scew_parser *) data;

  if (parser == NULL)
    {
      return;
    }

  current = parser->current;
  contents = scew_element_contents (current);

  if ((current != NULL) && (contents != NULL))
    {
      if (parser->ignore_whitespaces)
        {
          XML_Char *new_contents = scew_strdup (contents);
	  scew_strtrim (new_contents);
	  if (scew_strlen (new_contents) == 0)
            {
	      scew_element_free_contents (current);
            }
        }
    }
  parser->current = stack_pop_ (&parser->stack);
}

void
expat_char_handler_ (void *data, XML_Char const *s, int len)
{
  scew_element *current = NULL;
  scew_parser *parser = (scew_parser *) data;

  if (parser == NULL)
    {
      return;
    }

  current = parser->current;

  if (current != NULL)
    {
      unsigned int total = 0;
      unsigned int total_old = 0;
      XML_Char *new_contents = NULL;

      XML_Char const *contents = scew_element_contents (current);

      if (contents != NULL)
        {
          total_old = scew_strlen (contents);
        }

      total = (total_old + len + 1) * sizeof (XML_Char);

      new_contents = calloc (total, 1);
      scew_strncat (new_contents, s, len);

      scew_element_set_contents (current, new_contents);
    }
}

stack_element*
stack_push_ (stack_element **stack, scew_element *element)
{
  assert (element != NULL);

  stack_element *new_elem = calloc (1, sizeof (stack_element));

  if (new_elem != NULL)
    {
      new_elem->element = element;
      if (stack != NULL)
        {
	  new_elem->prev = *stack;
        }
      *stack = new_elem;
    }

  return new_elem;
}

scew_element*
stack_pop_ (stack_element **stack)
{
  assert (stack != NULL);

  scew_element *element = NULL;
  stack_element *sk_elem = *stack;
  if (sk_elem != NULL)
    {
      *stack = sk_elem->prev;
      element = sk_elem->element;
      free (sk_elem);
    }

  return element;
}
