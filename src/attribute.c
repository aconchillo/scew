/**
 *
 * @file     attribute.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 00:41
 * @brief    SCEW attribute type implementation
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

#include "xelement.h"

#include "util.h"

#include <string.h>


scew_attribute*
scew_attribute_create(XML_Char const* name, XML_Char const* value)
{
    return attribute_create(name, value);
}

void
scew_attribute_free(scew_attribute* attribute)
{
    if (attribute == NULL)
    {
        return;
    }

    free(attribute->name);
    free(attribute->value);
    free(attribute);
}

unsigned int
scew_attribute_count(scew_element const* element)
{
    if (element == NULL)
    {
        return 0;
    }

    return element->attributes->size;
}

scew_attribute*
scew_attribute_by_index(scew_element const* element, unsigned int idx)
{
    int i = 0;
    attribute_node* node = NULL;

    if ((element == NULL) || (idx >= element->attributes->size))
    {
        return NULL;
    }

    i = 0;
    node = element->attributes->first;
    while ((i < idx) && (node != NULL))
    {
        node = node->next;
        ++i;
    }

    return node->info;
}

scew_attribute*
scew_attribute_by_name(scew_element const* element, XML_Char const* name)
{
    int i = 0;
    scew_attribute* attribute = NULL;

    if (element == NULL)
    {
        return NULL;
    }

    for (i = 0; i < element->attributes->size; ++i)
    {
        attribute = scew_attribute_by_index(element, i);
        if (!scew_strcmp(attribute->name, name))
        {
            break;
        }
    }

    if (i == element->attributes->size)
    {
        return NULL;
    }

    return attribute;
}

XML_Char const*
scew_attribute_name(scew_attribute const* attribute)
{
    if (attribute == NULL)
    {
        return NULL;
    }

    return attribute->name;
}

XML_Char const*
scew_attribute_value(scew_attribute const* attribute)
{
    if (attribute == NULL)
    {
        return NULL;
    }

    return attribute->value;
}

XML_Char const*
scew_attribute_set_name(scew_attribute* attribute, XML_Char const* name)
{
    if (attribute == NULL)
    {
        return NULL;
    }

    free(attribute->name);
    attribute->name = scew_strdup(name);

    return attribute->name;
}

XML_Char const*
scew_attribute_set_value(scew_attribute* attribute, XML_Char const* value)
{
    if (attribute == NULL)
    {
        return NULL;
    }

    free(attribute->value);
    attribute->value = scew_strdup(value);

    return attribute->value;
}
