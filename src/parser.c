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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
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

/* This code does not compile under VC .NET */
/* static int const  MAX_BUFFER_SIZE = 5000; */
#define MAX_BUFFER_SIZE 5000

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
    unsigned int res = 0;

    assert(parser != NULL);
    assert(file_name != NULL);

    in = fopen(file_name, "rb");
    if (in == NULL)
    {
        set_last_error(scew_error_io);
        return 0;
    }

    res = scew_parser_load_file_fp(parser, in);
    fclose(in);

    return res;
}

unsigned int
scew_parser_load_file_fp(scew_parser* parser, FILE* in)
{
    int len = 0;
    int done = 0;
    char buffer[MAX_BUFFER_SIZE];

    assert(parser != NULL);
    assert(in != NULL);

    while (!done)
    {
        len = fread(buffer, 1, MAX_BUFFER_SIZE, in);
        if (ferror(in))
        {
            set_last_error(scew_error_io);
            return 0;
        }

        done = feof(in);
        if (!XML_Parse(parser->parser, buffer, len, done))
        {
            set_last_error(scew_error_expat);
            return 0;
        }
    }

    return 1;
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
