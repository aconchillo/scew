/**
 *
 * @file     attribute.c
 * @author   Aleix Conchillo Flaque <aconchillo@acm.org>
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
    attribute_free(attribute);
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
    if (element == NULL)
    {
        return NULL;
    }

    return attribute_by_index(element->attributes, idx);
}

scew_attribute*
scew_attribute_by_name(scew_element const* element, XML_Char const* name)
{
    if (element == NULL)
    {
        return NULL;
    }

    return attribute_by_name(element->attributes, name);
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
