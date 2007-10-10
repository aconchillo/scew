/**
 * @file     xparser.c
 * @brief    xparser.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Tue Dec 03, 2002 00:21
 *
 * @if copyright
 *
 * Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007 Aleix Conchillo Flaque
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * @endif
 */

#include "xparser.h"

#include <assert.h>


// Protected

stack_element*
stack_push_ (stack_element **stack, scew_element *element)
{
  assert (element != NULL);

  stack_element *new_elem = calloc (1, sizeof (stack_element));

  if (new_elem != NULL)
    {
      new_elem->element = element;
      if (stack != NULL)
        {
	  new_elem->prev = *stack;
        }
      *stack = new_elem;
    }

  return new_elem;
}

scew_element*
stack_pop_ (stack_element **stack)
{
  assert (stack != NULL);

  scew_element *element = NULL;
  stack_element *sk_elem = *stack;
  if (sk_elem != NULL)
    {
      *stack = sk_elem->prev;
      element = sk_elem->element;
      free (sk_elem);
    }

  return element;
}
