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

#include "xattribute.h"

#include "xelement.h"

#include "util.h"


unsigned int
scew_get_attribute_count(scew_element const* element)
{
    if (element == NULL)
    {
        return 0;
    }

    return element->n_attr;
}

scew_attribute const*
scew_get_attribute(scew_element const* element, unsigned int idx)
{
    if ((element == NULL) || (idx >= element->n_attr))
    {
        return NULL;
    }

    return &element->attributes[idx];
}

scew_attribute const*
scew_get_attribute_by_name(scew_element const* element, XML_Char const* name)
{
    int i = 0;
    scew_attribute* attribute = NULL;

    if (element == NULL)
    {
        return NULL;
    }

    for (i = 0; i < element->n_attr; ++i)
    {
        attribute = &element->attributes[i];
        if (!scew_strcmp(attribute->name, name))
        {
            break;
        }
    }

    if (i == element->n_attr)
    {
        return NULL;
    }

    return attribute;
}

XML_Char const*
scew_get_attribute_name(scew_attribute const* attribute)
{
    if (attribute == NULL)
    {
        return NULL;
    }

    return attribute->name;
}

XML_Char const*
scew_get_attribute_value(scew_attribute const* attribute)
{
    if (attribute == NULL)
    {
        return NULL;
    }

    return attribute->value;
}
