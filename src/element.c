/**
 *
 * @file     element.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 00:48
 * @brief    SCEW element type implementation
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

#include "xelement.h"

#include "xparser.h"

#include "util.h"


scew_element const*
scew_get_root(scew_parser const* parser)
{
    if (parser == NULL)
    {
        return NULL;
    }

    return parser->root;
}

unsigned int
scew_get_element_count(scew_element const* element)
{
    if (element == NULL)
    {
        return 0;
    }

    return element->n_children;
}

scew_element const*
scew_get_element(scew_element const* parent, unsigned int idx)
{
    if ((parent == NULL) || (idx >= parent->n_children))
    {
        return NULL;
    }

    return &parent->children[idx];
}

scew_element const*
scew_get_element_by_name(scew_element const* parent, char const* name)
{
    int i = 0;
    scew_element* element = NULL;

    if (parent == NULL)
    {
        return NULL;
    }

    if (!scew_strcmp(parent->name, name))
    {
        return (scew_element*) parent;
    }

    for (i = 0; i < parent->n_children; ++i)
    {
        element = &parent->children[i];
        if (!scew_strcmp(element->name, name))
        {
            break;
        }
    }

    if (i == parent->n_children)
    {
        return NULL;
    }

    return element;
}

scew_element**
scew_get_elements_list(scew_element const* parent, XML_Char const* name,
                       unsigned int* count)
{
    int i = 0;
    int j = 0;
    scew_element** list = NULL;
    scew_element* element = NULL;

    if (parent == NULL)
    {
        return NULL;
    }

    for (i = 0; i < parent->n_children; ++i)
    {
        element = &parent->children[i];
        if (!scew_strcmp(element->name, name))
        {
            j++;
            list = (scew_element**) realloc(list, sizeof(scew_element*) * j);
            list[j - 1] = element;
        }
    }

    *count = j;

    return list;
}

void
scew_elements_list_free(scew_element** list)
{
    if (list == NULL)
    {
        return;
    }

    free(list);
}

XML_Char const*
scew_get_element_name(scew_element const* element)
{
    if (element == NULL)
    {
        return NULL;
    }

    return element->name;
}

XML_Char const*
scew_get_element_contents(scew_element const* element)
{
    if (element == NULL)
    {
        return NULL;
    }

    return element->contents;
}
