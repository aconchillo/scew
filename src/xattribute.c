/**
 *
 * @file     xattribute.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Dec 02, 2002 23:03
 * @brief    SCEW private attribute type declaration
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

#include "xattribute.h"

#include "util.h"

#include <string.h>


scew_attribute*
attribute_create(XML_Char const* name, XML_Char const* value)
{
    scew_attribute* attribute = NULL;

    attribute = (scew_attribute*) calloc(1, sizeof(scew_attribute));
    if (attribute != NULL)
    {
        attribute->name = scew_strdup(name);
        attribute->value = scew_strdup(value);
    }

    return attribute;
}

void
attribute_free(scew_attribute* attribute)
{
    if (attribute != NULL)
    {
        free(attribute->name);
        free(attribute->value);
        free(attribute);
    }
}

void
attribute_node_free(attribute_node* node)
{
    if (node != NULL)
    {
        attribute_free(node->info);
        free(node);
    }
}

attribute_list*
attribute_list_create()
{
    return (attribute_list*) calloc(1, sizeof(attribute_list));
}

void
attribute_list_free(attribute_list* list)
{
    attribute_node* it = NULL;
    attribute_node* tmp = NULL;

    if (list == NULL)
    {
        return;
    }

    it = list->first;
    while (it != NULL)
    {
        tmp = it;
        it = it->next;
        attribute_node_free(tmp);
    }

    free(list);
}

scew_attribute*
attribute_list_add(attribute_list* list, scew_attribute* attribute)
{
    attribute_node* node = NULL;

    if (list == NULL)
    {
        return NULL;
    }

    node = attribute_node_by_name(list, attribute->name);
    if (node != NULL)
    {
        attribute_free(node->info);
        node->info = attribute;
        return node->info;
    }

    node = (attribute_node*) calloc(1, sizeof(attribute_node));
    if (node == NULL)
    {
        return NULL;
    }
    node->info = attribute;

    list->size++;
    if (list->first == NULL)
    {
        list->first = node;
    }
    else
    {
        list->last->next = node;
        node->prev = list->last;
    }
    list->last = node;

    return node->info;
}

void
attribute_list_del(attribute_list* list, XML_Char const* name)
{
    attribute_node* node = NULL;
    attribute_node* tmp_prev = NULL;
    attribute_node* tmp_next = NULL;

    if ((list == NULL) || (name == NULL))
    {
        return;
    }

    node = attribute_node_by_name(list, name);

    if (node != NULL)
    {
        tmp_prev = node->prev;
        tmp_next = node->next;
        if (tmp_prev != NULL)
        {
            tmp_prev->next = tmp_next;
        }
        if (tmp_next != NULL)
        {
            tmp_next->prev = tmp_prev;
        }

        if (node == list->first)
        {
            list->first = tmp_next;
        }

        if (node == list->last)
        {
            list->last = tmp_prev;
        }

        attribute_node_free(node);
        list->size--;
    }
}

attribute_node*
attribute_node_by_index(attribute_list* list, unsigned int idx)
{
    unsigned int i = 0;
    attribute_node* node = NULL;

    if ((list == NULL) || (idx >= list->size))
    {
        return NULL;
    }

    i = 0;
    node = list->first;
    while ((i < idx) && (node != NULL))
    {
        node = node->next;
        ++i;
    }

    return node;
}

attribute_node*
attribute_node_by_name(attribute_list* list, XML_Char const* name)
{
    unsigned int i = 0;
    attribute_node* node = NULL;

    if ((list == NULL) || (name == NULL))
    {
        return NULL;
    }

    for (i = 0; i < list->size; ++i)
    {
        node = attribute_node_by_index(list, i);
        if (!scew_strcmp(node->info->name, name))
        {
            break;
        }
    }

    if (i == list->size)
    {
        return NULL;
    }

    return node;
}

scew_attribute*
attribute_by_index(attribute_list* list, unsigned int idx)
{
    attribute_node* node = attribute_node_by_index(list, idx);

    if (node == NULL)
    {
        return NULL;
    }

    return node->info;
}

scew_attribute*
attribute_by_name(attribute_list* list, XML_Char const* name)
{
    attribute_node* node = attribute_node_by_name(list, name);

    if (node == NULL)
    {
        return NULL;
    }

    return node->info;
}
