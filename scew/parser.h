/**
 * @file     parser.h
 * @brief    SCEW parser type declaration
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 00:57
 * @ingroup  SCEWParser, SCEWParserAlloc, SCEWParserLoad, SCEWParserAcc
 *
 * @if copyright
 *
 * Copyright (C) 2002-2009 Aleix Conchillo Flaque
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
 *
 */

/**
 * @defgroup SCEWParser Parser
 *
 * These are the parser functions that allow to read an XML tree from a
 * file or a memory buffer.
 */

#ifndef PARSER_H_0211250057
#define PARSER_H_0211250057

#include "export.h"

#include "bool.h"
#include "reader.h"
#include "tree.h"

#include <expat.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * This is the type declaration of the SCEW parser.
 *
 * @ingroup SCEWParser
 */
typedef struct scew_parser scew_parser;

/**
 * Callback function type.
 *
 * @return true if callback call had no errors, false otherwise.
 *
 * @ingroup SCEWParserLoad
 */
typedef scew_bool (*scew_parser_load_hook) (scew_parser *, void *, void *);


/**
 * @defgroup SCEWParserAlloc Allocation
 * Allocate and free a parser.
 * @ingroup SCEWParser
 */

/**
 * Creates a new parser. A parser is necessary to load XML documents.
 *
 * @return a new parser, or NULL if parser is not successfully
 * created.
 *
 * @ingroup SCEWParserAlloc
 */
extern SCEW_API scew_parser* scew_parser_create (void);

/**
 * Creates a new parser with namespaces support. Note that Expat
 * expands the resulting elements and attributes, that is, they are
 * formed by the namespace URI, the given namespace @a separator and
 * the local part of the name.
 *
 * @param separator the character between namespace URI and
 * identifier. If 0 is given, no separation is performed.
 *
 * @return a new parser with namespace support, or NULL if parser is
 * not successfully created.
 *
 * @ingroup SCEWParserAlloc
 */
extern SCEW_API scew_parser* scew_parser_namespace_create (XML_Char separator);

/**
 * Frees a parser memory structure.
 *
 * @ingroup SCEWParserAlloc
 */
extern SCEW_API void scew_parser_free (scew_parser *parser);


/**
 * @defgroup SCEWParserLoad Load
 * Load XML documents from different sources.
 * @ingroup SCEWParser
 */

/**
 * Loads an XML tree from the specified file name using the given
 * parser.
 *
 * @param parser the SCEW parser.
 * @param reader the reader from where to load the XML.
 *
 * @return the XML parsed tree or NULL if an error was found.
 *
 * @ingroup SCEWParserLoad
 */
extern SCEW_API scew_tree* scew_parser_load (scew_parser *parser,
                                             scew_reader *reader);

extern SCEW_API scew_bool scew_parser_load_stream (scew_parser *parser,
                                                   scew_reader *reader);

extern SCEW_API void scew_parser_reset (scew_parser *parser);

extern SCEW_API void scew_parser_set_element_hook (scew_parser *parser,
                                                   scew_parser_load_hook hook,
                                                   void *user_data);

extern SCEW_API void scew_parser_set_tree_hook (scew_parser *parser,
                                                scew_parser_load_hook hook,
                                                void *user_data);

/**
 * Tells the parser how to treat white spaces. The default is to
 * ignore heading and trailing white spaces.
 *
 * There is a new section in XML specification which talks about how
 * to handle white spaces in XML. One can set an optional attribtue to
 * an element, this attribute is called 'xml:space', and it can be set
 * to 'default' or 'preserve', and it inherits its value from parent
 * elements. 'preserve' means to leave white spaces as their are
 * found, and 'default' means that white spaces are handled by the XML
 * processor (Expat in our case) the way it wants to.
 *
 * This function gives the possibility to change the XML processor
 * behaviour.
 *
 * @param parser the parser to set the option to.
 * @param ignore whether the parser should ignore white spaces, false
 * otherwise.
 *
 * @ingroup SCEWParserLoad
 */
extern SCEW_API void scew_parser_ignore_whitespaces (scew_parser *parser,
                                                     scew_bool ignore);


/**
 * @defgroup SCEWParserAcc Accessors
 * Obtain information from parser.
 * @ingroup SCEWParser
 */

/**
 * Returns the internal Expat parser. Probably some low-level Expat
 * functions need to be called. This function gives you access to the
 * Expat parser so you will be able to call those functions. If you
 * modify the Expat parser event handling routines, SCEW will not be
 * able to load the XML tree.
 *
 * @ingroup SCEWParserAcc
 */
extern SCEW_API XML_Parser scew_parser_expat (scew_parser *parser);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PARSER_H_0211250057 */
