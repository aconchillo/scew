/**
 *
 * @file     parser.c
 * @author   Aleix Conchillo Flaque <aconchillo@acm.org>
 * @date     Mon Nov 25, 2002 00:58
 * @brief    SCEW parser type implementation
 *
 * $Id$
 *
 * @if copyright
 *
 * Copyright (C) 2002 Aleix Conchillo Flaque
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

#include "xparser.h"

#include "xelement.h"

#include "handler.h"

#include <stdio.h>
#include <string.h>


scew_parser*
scew_parser_create()
{
    scew_parser* parser;

    parser = (scew_parser*) malloc(sizeof(scew_parser));
    bzero(parser, sizeof(scew_parser));
    if (parser == NULL)
    {
        return NULL;
    }

    parser->parser = XML_ParserCreate(NULL);
    if (parser->parser == NULL)
    {
        return NULL;
    }

    XML_SetElementHandler(parser->parser, start_handler, end_handler);
    XML_SetCharacterDataHandler(parser->parser, char_handler);
    XML_SetUserData(parser->parser, parser);

    return parser;
}

XML_Parser
scew_parser_expat(scew_parser* parser)
{
    if (parser == NULL)
    {
        return NULL;
    }

    return parser->parser;
}

void
scew_parser_free(scew_parser* parser)
{
    if (parser == NULL)
    {
        return;
    }

    XML_ParserFree(parser->parser);

    free_element(parser->root);
    free(parser->root);
    free(parser);
}

unsigned int
scew_load_file(scew_parser* parser, char const* file_name)
{
    FILE* in;
    long file_size;
    unsigned int result;
    unsigned char* buffer;

    if (parser == NULL)
    {
        return 0;
    }

    in = fopen(file_name, "r");
    if (in == NULL)
    {
        return 0;
    }

    fseek(in, 0, SEEK_END);
    file_size = ftell(in);
    fseek(in, 0, SEEK_SET);

    buffer = (unsigned char*) malloc(file_size);
    if (buffer == NULL)
    {
        fclose(in);
        return 0;
    }

    if (fread(buffer, file_size, 1, in) != 1)
    {
        fclose(in);
        free(buffer);
        return 0;
    }
    fclose(in);

    result = scew_load_buffer(parser, buffer, file_size);

    free(buffer);

    return result;
}

unsigned int
scew_load_buffer(scew_parser* parser, unsigned char const* buffer,
                 unsigned int size)
{
    if (parser == NULL)
    {
        return 0;
    }

    if (!XML_Parse(parser->parser, buffer, size, 1))
    {
        return 0;
    }

    return 1;
}
