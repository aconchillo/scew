/**
 *
 * @file     handler.c
 * @author   Aleix Conchillo Flaque <aconchillo@acm.org>
 * @date     Mon Nov 25, 2002 00:21
 * @brief    SCEW Expat handlers
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

#include "handler.h"

#include "xattribute.h"
#include "xelement.h"
#include "xparser.h"

#include "util.h"

#include <string.h>


void
start_handler(void* data, XML_Char const* elem, XML_Char const** attr)
{
    int i = 0;
    scew_parser* parser = (scew_parser*) data;
    scew_element* current = NULL;
    scew_attribute* attribute = NULL;

    if (parser == NULL)
    {
        return;
    }

    if (parser->root == NULL)
    {
        parser->root = (scew_element*) malloc(sizeof(scew_element));
        parser->current = parser->root;
    }
    else
    {
        parser->current->n_children++;
        parser->current->children = (scew_element*) realloc(
            parser->current->children,
            sizeof(scew_element) * parser->current->n_children);

        stack_push(&parser->stack, parser->current);
        parser->current =
            &(parser->current->children[parser->current->n_children - 1]);
    }
    current = parser->current;
    bzero(current, sizeof(scew_element));

    current->name = scew_strdup(elem);

    for (i = 0; attr[i]; i += 2)
    {
        current->n_attr++;
        current->attributes = (scew_attribute*) realloc(
            current->attributes, sizeof(scew_attribute) * current->n_attr);

        attribute = &current->attributes[current->n_attr - 1];

        attribute->name  = scew_strdup(attr[i]);
        attribute->value = scew_strdup(attr[i + 1]);
    }
}

void
end_handler(void* data, XML_Char const* elem)
{
    scew_parser* parser = (scew_parser*) data;

    if (parser == NULL)
    {
        return;
    }

    parser->current = stack_pop(&parser->stack);
}

void
char_handler(void* data, XML_Char const* s, int len)
{
    int start = 0;
    int total = 0;
    int total_new = 0;
    int total_old = 0;
    scew_element* current = NULL;
    scew_parser* parser = (scew_parser*) data;

    if (is_empty_char(s, len))
    {
        return;
    }

    if (parser == NULL)
    {
        return;
    }

    current = parser->current;

    if (current == NULL)
    {
        return;
    }

    start = skip_white_space(s, len);
    total_new = len - start;
    total_old = scew_strlen(current->contents);
    total = (total_old + total_new + 2) * sizeof(XML_Char);
    current->contents = (XML_Char*) realloc(current->contents, total);

    if (total_old == 0)
    {
        current->contents[0] = '\0';
    }
    else
    {
        scew_strcat(current->contents, " ");
    }

    scew_strncat(current->contents, &s[start], total_new);
}

int
skip_white_space(XML_Char const* s, int len)
{
    int i = 0;

    if ((s == NULL) || (len == 0))
    {
        return 0;
    }

    while (((s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r'))
           && (i < len))
    {
        i++;
    }

    return i;
}

int
is_empty_char(XML_Char const* s, int len)
{
    int i = 0;
    int last = len - 1;

    if ((s == NULL) || (len == 0))
    {
        return 1;
    }

    if (((len == 1) && ((s[0] == '\n') || (s[1] == '\r'))) ||
        ((len == 2) && ((s[0] == '\r') && (s[1] == '\n'))))
    {
        return 1;
    }

    if (s[last] == ' ')
    {
        for (i = 0; i < last; i++)
        {
            if (s[i] != ' ')
            {
                break;
            }
        }
        if (i == last)
        {
            return 1;
        }
    }

    return 0;
}
