/**
 *
 * @file     xparser.c
 * @author   Aleix Conchillo Flaque <aconchillo@acm.org>
 * @date     Tue Dec 03, 2002 00:21
 * @brief    SCEW private parser type declaration
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

#include "xparser.h"


void
stack_push(stack_element** stack, scew_element* element)
{
    stack_element* new_elem = (stack_element*) malloc(sizeof(stack_element));

    if (new_elem == NULL)
    {
        return;
    }
    else
    {
        new_elem->element = element;
        if (stack != NULL)
        {
            new_elem->prev = *stack;
        }
        *stack = new_elem;
    }
}

scew_element*
stack_pop(stack_element** stack)
{
    stack_element* aux = NULL;
    scew_element* elem = NULL;

    if (stack != NULL)
    {
        aux = *stack;
        if (aux != NULL)
        {
            *stack = aux->prev;
            elem = aux->element;
            free(aux);
        }
    }

    return elem;
}
