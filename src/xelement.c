/**
 *
 * @file     xelement.c
 * @author   Aleix Conchillo Flaque <aconchillo@acm.org>
 * @date     Mon Nov 25, 2002 01:25
 * @brief    SCEW private element type implementation
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

#include "xattribute.h"


void
free_element(scew_element* element)
{
    int i = 0;

    if (element == NULL)
    {
        return;
    }

    free(element->name);
    free(element->contents);

    for (i = 0; i < element->n_attr; ++i)
    {
        free_attribute(&element->attributes[i]);

    }
    free(element->attributes);

    for (i = 0; i < element->n_children; ++i)
    {
        free_element(&element->children[i]);
    }
    free(element->children);
}
