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

#include "xelement.h"

#include "util.h"

#include <string.h>


scew_element*
scew_element_create(XML_Char const* name)
{
    scew_element* element = NULL;

    element = (scew_element*) calloc(1, sizeof(scew_element));
    if (element != NULL)
    {
        element->name = scew_strdup(name);
        element->attributes = attribute_list_create();
    }

    return element;
}

void
scew_element_free(scew_element* element)
{
    if (element == NULL)
    {
        return;
    }

    free(element->name);
    free(element->contents);
    attribute_list_free(element->attributes);

    if ((element->parent != NULL) && (element->parent->child == element))
    {
        element->parent->child = element->right;
    }

    while (element->child != NULL)
    {
        scew_element_free(element->child);
    }

    free(element);
}

unsigned int
scew_element_count(scew_element const* parent)
{
    if (parent == NULL)
    {
        return 0;
    }

    return parent->n_children;
}

scew_element*
scew_element_by_index(scew_element const* parent, unsigned int idx)
{
    int i = 0;
    scew_element* element = NULL;

    if ((parent == NULL) || (idx >= parent->n_children))
    {
        return NULL;
    }

    i = 0;
    element = parent->child;
    while ((i < idx) && (element != NULL))
    {
        element = element->right;
        ++i;
    }

    return element;
}

scew_element*
scew_element_by_name(scew_element const* parent, char const* name)
{
    int i = 0;
    scew_element* element = NULL;

    if (parent == NULL)
    {
        return NULL;
    }

    for (i = 0; i < parent->n_children; ++i)
    {
        element = scew_element_by_index(parent, i);
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

XML_Char const*
scew_element_name(scew_element const* element)
{
    if (element == NULL)
    {
        return NULL;
    }

    return element->name;
}

XML_Char const*
scew_element_contents(scew_element const* element)
{
    if (element == NULL)
    {
        return NULL;
    }

    return element->contents;
}

XML_Char const*
scew_element_set_name(scew_element* element, XML_Char const* name)
{
    if (element == NULL)
    {
        return NULL;
    }

    free(element->name);
    element->name = scew_strdup(name);

    return element->name;
}

XML_Char const*
scew_element_set_contents(scew_element* element, XML_Char const* data)
{
    if (element == NULL)
    {
        return NULL;
    }

    free(element->contents);
    element->contents = scew_strdup(data);

    return element->contents;
}

scew_element*
scew_element_add(scew_element* element, XML_Char const* name)
{
    scew_element* new_elem = scew_element_create(name);

    return scew_element_add_elem(element, new_elem);
}

scew_element*
scew_element_add_elem(scew_element* element, scew_element* new_elem)
{
    scew_element* current = NULL;

    if (element == NULL)
    {
        return NULL;
    }
    element->n_children++;

    new_elem->parent = element;
    if (element->child == NULL)
    {
        element->child = new_elem;
    }
    else
    {
        current = element->child;
        while (current->right != NULL)
        {
            current = current->right;
        }
        current->right = new_elem;
    }

    return new_elem;
}

scew_attribute*
scew_element_add_attr(scew_element* element, scew_attribute* attribute)
{
    return attribute_list_add(element->attributes, attribute);
}

scew_attribute*
scew_element_add_attr_pair(scew_element* element, XML_Char const* name,
                           XML_Char const* value)
{
    scew_attribute* attribute = scew_attribute_create(name, value);

    return attribute_list_add(element->attributes, attribute);
}
