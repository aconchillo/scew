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

    attribute = (scew_attribute*) malloc(sizeof(scew_attribute));
    if (attribute != NULL)
    {
        bzero(attribute, sizeof(scew_attribute));
        attribute->name = scew_strdup(name);
        attribute->value = scew_strdup(value);
    }

    return attribute;
}

scew_attribute*
attribute_duplicate(scew_attribute const* attribute)
{
    scew_attribute* new_attr = NULL;

    new_attr = (scew_attribute*) malloc(sizeof(scew_attribute));
    if (new_attr != NULL)
    {
        bzero(new_attr, sizeof(scew_attribute));
        new_attr->name = scew_strdup(attribute->name);
        new_attr->value = scew_strdup(attribute->value);
    }

    return new_attr;
}

attribute_list*
attribute_list_create()
{
    attribute_list* list = NULL;

    list = (attribute_list*) malloc(sizeof(attribute_list));
    if (list != NULL)
    {
        bzero(list, sizeof(attribute_list));
    }

    return list;
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
        free(tmp);
    }

    free(list);
}

scew_attribute*
attribute_list_add(attribute_list* list, scew_attribute const* attribute)
{
    attribute_node* node = NULL;

    if (list == NULL)
    {
        return NULL;
    }

    node = (attribute_node*) malloc(sizeof(attribute_node));
    if (node == NULL)
    {
        return NULL;
    }
    bzero(node, sizeof(attribute_node));
    node->info = attribute_duplicate(attribute);

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
