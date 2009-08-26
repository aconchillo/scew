/**
 * @file     element.c
 * @brief    SCEW private element type declaration
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Aug 27, 2009 01:47
 *
 * @if copyright
 *
 * Copyright (C) 2002-2009 Aleix Conchillo Flaque
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

#ifndef XELEMENT_H_0908270147
#define XELEMENT_H_0908270147

#include "element.h"

#include "list.h"

#include <expat.h>


/* Types */

struct scew_element
{
  XML_Char *name;
  XML_Char *contents;

  scew_element *parent;
  scew_list *myself;            /**< Pointer to parent's children list
                                   (performance) */

  unsigned int n_children;
  scew_list *children;
  scew_list *last_child;        /**< Pointer to last child (performance) */

  unsigned int n_attributes;
  scew_list *attributes;
  scew_list *last_attribute;    /**< Pointer to last attribute (performance) */
};

#endif // XELEMENT_H_0908270147
