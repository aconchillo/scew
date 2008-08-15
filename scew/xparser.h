/**
 * @file     xparser.h
 * @brief    SCEW private parser type declaration
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 00:57
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


#ifndef XPARSER_H_0211250057
#define XPARSER_H_0211250057

#include "parser.h"


// Types

// Stack to keep previous parsed elements
typedef struct stack_element stack_element;

struct scew_parser
{
  XML_Parser parser;		/**< Expat parser */
  scew_tree* tree;		/**< XML document tree */
  scew_element* current;	/**< Current parsed element */
  stack_element* stack;		/**< Current parsed element stack */
  bool ignore_whitespaces;	/**< Whether to ignore white spaces */
  scew_parser_callback stream_callback; /**< Callback to use while
                                           reading streams */
};


// Functions

/* Expat callback for XML declaration. */
extern void scew_parser_xmldecl_handler_ (void *data,
                                          XML_Char const *version,
                                          XML_Char const *encoding,
                                          int standalone);

/* Expat callback for starting elements. */
extern void scew_parser_start_handler_ (void *data,
                                        XML_Char const *elem,
                                        XML_Char const **attr);

/* Expat callback for ending elements. */
extern void scew_parser_end_handler_ (void *data, XML_Char const *elem);

/* Expat callback for element contents. */
extern void scew_parser_char_handler_ (void *data, XML_Char const *s, int len);

#endif /* XPARSER_H_0211250057 */
