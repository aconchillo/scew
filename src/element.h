/**
 *
 * @file     element.h
 * @author   Aleix Conchillo Flaque <aconchillo@acm.org>
 * @date     Mon Nov 25, 2002 00:48
 * @brief    SCEW element type declaration
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
 *
 * Element related functions. SCEW provides functions to access the XML
 * tree previously loaded by the parser.
 */


#ifndef ELEMENT_H_ALEIX0211250048
#define ELEMENT_H_ALEIX0211250048

#include "parser.h"

/**
 * This is the type delcaration for elements.
 */
typedef struct _scew_element scew_element;


/**
 * Returns the root element of the XML tree read by the parser.
 */
extern scew_element const*
scew_get_root(scew_parser const* parser);

/**
 * Returns the number of children of the specified element. An element
 * can have zero or more children.
 */
extern unsigned int
scew_get_element_count(scew_element const* element);

/**
 * Returns the element child on the specified position. Positions are
 * zero based.
 *
 * @return the element on the specified position, NULL if there is no
 * element in the position.
 */
extern scew_element const*
scew_get_element(scew_element const* parent, unsigned int idx);

/**
 * Returns the element child with the specified name. Remember that XML
 * names are case-sensitive.
 *
 * @return the element in the specified position, NULL if not found.
 */
extern scew_element const*
scew_get_element_by_name(scew_element const* parent, XML_Char const* name);

/**
 * Returns a list of elements with the same specified name. The number
 * of elements is returned in <code>count</code>
 *
 * @param parent the parent element.
 * @param name the name that the elements must match.
 * @param count the number of elements found with the same name.
 *
 * @return an element list.
 */
extern scew_element**
scew_get_elements_list(scew_element const* parent, XML_Char const* name,
                       unsigned int* count);

/**
 * Frees an elements list.
 */
extern void
scew_elements_list_free(scew_element** list);

/**
 * Returns the element name or NULL if the element does not exist.
 */
extern XML_Char const*
scew_get_element_name(scew_element const* element);

/**
 * Returns the element contents value. That is the contents between the
 * start and end element tags. Returns NULL if element has no contents.
 */
extern XML_Char const*
scew_get_element_contents(scew_element const* element);


#endif /* ELEMENT_H_ALEIX0211250048 */
