/**
 *
 * @file     xattribute.h
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 00:54
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


#ifndef XATTRIBUTE_H_ALEIX0211250054
#define XATTRIBUTE_H_ALEIX0211250054

#include "attribute.h"

#include <expat.h>


struct _scew_attribute
{
    XML_Char* name;
    XML_Char* value;
};

/* Doubly linked list node */
typedef struct _attr_node
{
    scew_attribute* info;
    struct _attr_node* prev;
    struct _attr_node* next;
} attribute_node;

/* Doubly linked list */
typedef struct
{
    unsigned int size;
    attribute_node* first;
    attribute_node* last;
} attribute_list;


/* Creates a duplicated attribute from the given one. */
scew_attribute*
attribute_create(XML_Char const* name, XML_Char const* value);

/* Frees an attribute structure. */
void
attribute_free(scew_attribute* attribute);

/* Frees an attribute node structure. */
void
attribute_node_free(attribute_node* node);

/* Creates a new attribute list. */
attribute_list*
attribute_list_create();

/* Frees an attribute list. */
void
attribute_list_free(attribute_list* list);

/* Adds a new element to the attribute list. */
scew_attribute*
attribute_list_add(attribute_list* list, scew_attribute* attribute);

/* Return the list node in position idx. */
attribute_node*
attribute_node_by_index(attribute_list* list, unsigned int idx);

/* Return the list node that matches name. */
attribute_node*
attribute_node_by_name(attribute_list* list, XML_Char const* name);

/* Return the attribute in position idx. */
scew_attribute*
attribute_by_index(attribute_list* list, unsigned int idx);

/* Return the attribute that matches name. */
scew_attribute*
attribute_by_name(attribute_list* list, XML_Char const* name);

#endif /* XATTRIBUTE_H_ALEIX0211250054 */
