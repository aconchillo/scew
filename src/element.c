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

#include "xerror.h"

#include "util.h"

#include <assert.h>
#include <string.h>


scew_element*
scew_element_create(XML_Char const* name)
{
    assert(name != NULL);

    scew_element* element = NULL;

    element = (scew_element*) calloc(1, sizeof(scew_element));
    if (element != NULL)
    {
        element->name = scew_strdup(name);
        element->attributes = attribute_list_create();
    }
    else
    {
        set_last_error(scew_error_no_memory);
    }

    return element;
}

void
scew_element_free(scew_element* element)
{
    scew_element* left = NULL;
    scew_element* right = NULL;

    if (element == NULL)
    {
        return;
    }

    left = element->left;
    right = element->right;
    if (left != NULL)
    {
        left->right = right;
    }
    if (right != NULL)
    {
        right->left = left;
    }

    free(element->name);
    free(element->contents);
    attribute_list_free(element->attributes);

    if (element->parent != NULL)
    {
 	if (element->parent->child == element)
	{
            element->parent->child = element->right;
	}
 	if (element->parent->last_child == element)
	{
            element->parent->last_child = element->left;
	}
        element->parent->n_children--;
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
    assert(parent != NULL);

    return parent->n_children;
}

scew_element*
scew_element_next(scew_element const* parent, scew_element const* element)
{
    scew_element *next_element;

    if (element == NULL)
    {
	if (parent == NULL)
    	{
            return NULL;
	}
	next_element = parent->child;
    }
    else
    {
	next_element = element->right;
    }

    return next_element;
}

scew_element*
scew_element_by_index(scew_element const* parent, unsigned int idx)
{
    assert(parent != NULL);
    assert(idx < parent->n_children);

    unsigned int i = 0;
    scew_element* element = NULL;

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
scew_element_by_name(scew_element const* parent, XML_Char const* name)
{
    assert(parent != NULL);

    unsigned int i = 0;
    scew_element* element = NULL;

    if (name != NULL)
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

scew_element**
scew_element_list(scew_element const* parent, XML_Char const* name,
                  unsigned int* count)
{
    assert(parent != NULL);
    assert(name != NULL);
    assert(count != NULL);

    unsigned int i = 0;
    unsigned int j = 0;
    scew_element** list = NULL;
    scew_element* element = NULL;

    for (i = 0; i < parent->n_children; ++i)
    {
        element = scew_element_by_index(parent, i);
        if (!scew_strcmp(element->name, name))
        {
            j++;
            list = (scew_element**) realloc(list, sizeof(scew_element*) * j);
            if (list == NULL)
            {
                set_last_error(scew_error_no_memory);
                return NULL;
            }
            list[j - 1] = element;
        }
    }

    *count = j;

    return list;
}

void
scew_element_list_free(scew_element** list)
{
    free(list);
}

XML_Char const*
scew_element_name(scew_element const* element)
{
    assert(element != NULL);

    return element->name;
}

XML_Char const*
scew_element_contents(scew_element const* element)
{
    assert(element != NULL);

    return element->contents;
}

XML_Char const*
scew_element_set_name(scew_element* element, XML_Char const* name)
{
    assert(element != NULL);
    assert(name != NULL);

    free(element->name);
    element->name = scew_strdup(name);

    return element->name;
}

XML_Char const*
scew_element_set_contents(scew_element* element, XML_Char const* data)
{
    assert(element != NULL);
    assert(data != NULL);

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
    assert(element != NULL);
    assert(new_elem != NULL);

    scew_element* current = NULL;

    element->n_children++;

    new_elem->parent = element;
    if (element->child == NULL)
    {
        element->child = new_elem;
    }
    else
    {
        current = element->last_child;
        current->right = new_elem;
        new_elem->left = current;
    }
    element->last_child = new_elem;

    return new_elem;
}

void
scew_element_del(scew_element* element)
{
    scew_element_free(element);
}

void
scew_element_del_by_name(scew_element* element, XML_Char const* name)
{
    scew_element_free(scew_element_by_name(element, name));
}

void
scew_element_del_by_index(scew_element* element, unsigned int idx)
{
    scew_element_free(scew_element_by_index(element, idx));
}

void
scew_element_list_del(scew_element* element, XML_Char const* name)
{
    unsigned int i = 0;
    unsigned int count = 0;
    scew_element** list = NULL;

    if ((element == NULL) || (name == NULL))
    {
        return;
    }

    list = scew_element_list(element, name, &count);
    if (list == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        scew_element_free(list[i]);
    }
    scew_element_list_free(list);
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

void
scew_element_del_attr(scew_element* element, XML_Char const* name)
{
    attribute_list_del(element->attributes, name);
}
