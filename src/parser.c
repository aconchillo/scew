/**
 *
 * @file     parser.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 00:58
 * @brief    SCEW parser type implementation
 *
 * $Id$
 *
 * @if copyright
 *
 * Copyright (C) 2002, 2003 Aleix Conchillo Flaque
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

#include "parser.h"

#include "tree.h"

#include "xerror.h"
#include "xparser.h"
#include "xhandler.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>


scew_parser*
scew_parser_create()
{
    scew_parser* parser = NULL;

    parser = (scew_parser*) calloc(1, sizeof(scew_parser));
    if (parser == NULL)
    {
        set_last_error(scew_error_no_memory);
        return NULL;
    }

    parser->parser = XML_ParserCreate(NULL);
    if (parser->parser == NULL)
    {
        set_last_error(scew_error_no_memory);
        return NULL;
    }

    XML_SetXmlDeclHandler(parser->parser, xmldecl_handler);
    XML_SetElementHandler(parser->parser, start_handler, end_handler);
    XML_SetCharacterDataHandler(parser->parser, char_handler);
    XML_SetUserData(parser->parser, parser);

    /* ignore white spaces by default */
    parser->ignore_whitespaces = 1;

    return parser;
}

void
scew_parser_free(scew_parser* parser)
{
    if (parser != NULL)
    {
        XML_ParserFree(parser->parser);
        free(parser);
    }
}

unsigned int
scew_parser_load_file(scew_parser* parser, char const* file_name)
{
    FILE* in = NULL;
    long file_size = 0;
    char* buffer = NULL;
    unsigned int result = 0;

    assert(parser != NULL);
    assert(file_name != NULL);

    in = fopen(file_name, "r");
    if (in == NULL)
    {
        set_last_error(scew_error_io);
        return 0;
    }

    fseek(in, 0, SEEK_END);
    file_size = ftell(in);
    fseek(in, 0, SEEK_SET);

    buffer = (char*) malloc(file_size);
    if (buffer == NULL)
    {
        set_last_error(scew_error_no_memory);
        fclose(in);
        return 0;
    }

    if (fread(buffer, file_size, 1, in) != 1)
    {
        set_last_error(scew_error_io);
        fclose(in);
        free(buffer);
        return 0;
    }
    fclose(in);

    result = scew_parser_load_buffer(parser, buffer, file_size);

    free(buffer);

    return result;
}

unsigned int
scew_parser_load_buffer(scew_parser* parser, char const* buffer,
                        unsigned int size)
{
    assert(parser != NULL);
    assert(buffer != NULL);

    if (!XML_Parse(parser->parser, buffer, size, 1))
    {
        set_last_error(scew_error_expat);
        return 0;
    }

    return 1;
}

scew_tree*
scew_parser_tree(scew_parser const* parser)
{
    assert(parser != NULL);

    return parser->tree;
}

XML_Parser
scew_parser_expat(scew_parser* parser)
{
    assert(parser != NULL);

    return parser->parser;
}

void
scew_parser_ignore_whitespaces(scew_parser* parser, int ignore)
{
    assert(parser != NULL);

    parser->ignore_whitespaces = ignore;
}
