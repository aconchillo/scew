/**
 *
 * @file     attribute.h
 * @brief    Attribute's handling routines
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 00:39
 * @ingroup  SCEWAttributeAlloc, SCEWAttributeAcc
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 * @endif
 */

/**
 * @defgroup SCEWAttribute Attributes
 *
 * Attribute related functions. SCEW provides functions to access and
 * manipulate the attributes of all the elements in a tree. XML
 * element attributes are basically a name-value pair.
 */

#ifndef ATTRIBUTE_H_0211250039
#define ATTRIBUTE_H_0211250039

#include <expat.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * This is the type declaration for element attributes.
 *
 * @ingroup SCEWAttribute
 */
typedef struct scew_attribute scew_attribute;


/**
 * @defgroup SCEWAttributeAlloc Allocation
 * Allocate and free attributes.
 * @ingroup SCEWAttribute
 */

/**
 * Creates a new attribute with the given pair (@a name, @a value).
 *
 * @pre name != NULL
 * @pre value != NULL
 *
 * @param name the attribute's name.
 * @param value the attribute's value.
 *
 * @return the created attribute, or NULL if an error is found.
 *
 * @ingroup SCEWAttributeAlloc
 */
extern scew_attribute* scew_attribute_create (XML_Char const *name,
					      XML_Char const *value);

/**
 * Makes a copy of the given @a attribute.
 *
 * @param attribute the attribute to be copied.
 *
 * @return a new attribute, or NULL if the copy failed.
 *
 * @ingroup SCEWAttributeAlloc
 */
extern scew_attribute* scew_attribute_copy (scew_attribute const *attribute);

/**
 * Frees an @a attribute. That is, its name and value. You should not
 * call this function with an attribute obtained from an element, but
 * created with #scew_attribute_create. If a NULL @a attribute is
 * given, this function does not have any effect.
 *
 * @param attribute the attribute to be freed.
 *
 * @ingroup SCEWAttributeAlloc
 */
extern void scew_attribute_free (scew_attribute *attribute);


/**
 * @defgroup SCEWAttributeCompare Comparisson
 * Attribute comparisson routines.
 * @ingroup SCEWAttribute
 */

/**
 *
 *
 * @param a
 * @param b
 *
 * @return
 *
 * @ingroup SCEWAttributeCompare
 */
extern bool scew_attribute_compare (scew_attribute const *a,
                                    scew_attribute const *b);


/**
 * @defgroup SCEWAttributeAcc Accessors
 * Access attribute's data, such as name and value.
 * @ingroup SCEWAttribute
 */

/**
 * Returns the @a attribute's name.
 *
 * @pre attribute != NULL
 *
 * @ingroup SCEWAttributeAcc
 */
extern XML_Char const* scew_attribute_name (scew_attribute const *attribute);

/**
 * Returns the @a attribute's value.
 *
 * @pre attribute != NULL
 *
 * @ingroup SCEWAttributeAcc
 */
extern XML_Char const* scew_attribute_value (scew_attribute const *attribute);

/**
 * Sets a new @a name to the given @a attribute and frees the old
 * one. If an error is found, the old name is not freed.
 *
 * @pre attribute != NULL
 * @pre name != NULL
 *
 * @return the new attribute's name, or NULL if the new name can not
 * be set.
 *
 * @ingroup SCEWAttributeAcc
 */
extern XML_Char const* scew_attribute_set_name (scew_attribute *attribute,
						XML_Char const *name);

/**
 * Sets a new @a value to the given @a attribute and frees the old
 * one. If an error is found, the old value is not freed.
 *
 * @pre attribute != NULL
 * @pre name != NULL
 *
 * @return the new attribute's value, or NULL if the new value could
 * not be set.
 *
 * @ingroup SCEWAttributeAcc
 */
extern XML_Char const* scew_attribute_set_value (scew_attribute *attribute,
						 XML_Char const *value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ATTRIBUTE_H_0211250039 */
