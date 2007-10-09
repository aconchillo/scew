/**
 * @file     element.h
 * @brief    Element's handling routines
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 00:48
 * @ingroup  SCEWElementAcc, SCEWElementAttr, SCEWElementHier
 * @ingroup  SCEWElementAlloc, SCEWElementSearch
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
 * @defgroup SCEWElement Elements
 *
 * Element related functions. SCEW provides functions to access and
 * manipulate the elements of an XML tree.
 */

#ifndef ELEMENT_H_0211250048
#define ELEMENT_H_0211250048

#include "attribute.h"
#include "list.h"

#include <expat.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * This is the type delcaration for elements.
 */
typedef struct scew_element scew_element;


/**
 * @defgroup SCEWElementAlloc Allocation
 * Allocate and free elements.
 * @ingroup SCEWElement
 */

/**
 * Creates a new element with the given @a name. This element is not
 * yet related to any XML tree.
 *
 * @pre name != NULL
 *
 * @param name the name of the new element.
 *
 * @return the created element, or NULL if an error is found.
 *
 * @ingroup SCEWElementAlloc
 */
extern scew_element* scew_element_create (XML_Char const *name);

/**
 * Makes a deep copy of the given @a element.
 *
 * @param element the element to be copied.
 *
 * @return a new element, or NULL if the copy failed.
 *
 * @ingroup SCEWElementAlloc
 */
extern scew_element* scew_element_copy (scew_element const *element);

/**
 * Frees the given @a element recursively. That is, it frees all its
 * children and attributes. If the @a element has a parent, it is also
 * detached from it. If a NULL @a element is given, this function does
 * not have any effect.
 *
 * @param element the element to be freed.
 *
 * @ingroup SCEWElementAlloc
 */
extern void scew_element_free (scew_element *element);


/**
 * @defgroup SCEWElementSearch Search and iteration
 * Iterate and search for elements.
 * @ingroup SCEWElement
 */

/**
 * Returns the first element child that matches the given @a
 * name. Remember that XML names are case-sensitive.
 *
 * @pre element != NULL
 * @pre name != NULL
 *
 * @param element the element whose children must be looked up.
 * @param name the string to be found representing the element's name.
 *
 * @return the first element that matches the given @a name, or NULL
 * if not found.
 *
 * @ingroup SCEWElementSearch
 */
extern scew_element* scew_element_by_name (scew_element const *element,
					   XML_Char const *name);

/**
 * Returns a list of elements that matches the @a name specified. This
 * list must be freed after using it via #scew_list_free (the elements
 * will not be freed).
 *
 * @pre element != NULL
 * @pre name != NULL
 *
 * @param element the element whose children must be looked up.
 * @param name the string to be found representing the elements' name.
 *
 * @return a list of elements that matches the @a name specified, or
 * NULL if no element is found.
 *
 * @ingroup SCEWElementSearch
 */
extern scew_list* scew_element_list_by_name (scew_element const *element,
                                             XML_Char const *name);


/**
 * @defgroup SCEWElementCompare Comparisson
 * Element comparisson routines.
 * @ingroup SCEWElement
 */

/**
 *
 *
 * @param a
 * @param b
 *
 * @return
 *
 * @ingroup SCEWElementCompare
 */
extern bool scew_element_compare (scew_element const *a,
                                  scew_element const *b);


/**
 * @defgroup SCEWElementAcc Accessors
 * Access element's data, such as name and contents.
 * @ingroup SCEWElement
 */

/**
 * Returns the given @a element's name.
 *
 * @pre element != NULL
 *
 * @ingroup SCEWElementAcc
 */
extern XML_Char const* scew_element_name (scew_element const *element);

/**
 * Returns the given @a element's value. That is, the contents between
 * the start and end element tags.
 *
 * @pre element != NULL
 *
 * @return the element's value or NULL if the element has no value.
 *
 * @ingroup SCEWElementAcc
 */
extern XML_Char const* scew_element_contents (scew_element const *element);

/**
 * Sets a new name to the given @a element and frees the old one. If
 * the new name can not be set, the old one is not freed.
 *
 * @pre element != NULL
 * @pre name != NULL
 *
 * @return the new element's name or NULL if the name can not be set.
 *
 * @ingroup SCEWElementAcc
 */
extern XML_Char const* scew_element_set_name (scew_element *element,
					      XML_Char const *name);

/**
 * Sets a new contents to the given element and frees the old one. If
 * the new contents can not be set, the old one is not freed.
 *
 * @pre element != NULL
 *
 * @return the new element's contents or NULL if the contents can not
 * be set.
 *
 * @ingroup SCEWElementAcc
 */
extern XML_Char const* scew_element_set_contents (scew_element *element,
						  XML_Char const *contents);

extern void scew_element_free_contents (scew_element *element);


/**
 * @defgroup SCEWElementHier Hierarchy
 * Handle element's hierarchy (parent, children).
 * @ingroup SCEWElement
 */

/**
 * Returns the number of children of the specified @a element. An
 * element can have zero or more children.
 *
 * @pre element != NULL
 *
 * @ingroup SCEWElementHier
 */
extern unsigned int scew_element_count (scew_element const *element);

/**
 * Returns the parent of the given @a element.
 *
 * @pre element != NULL
 *
 * @return the element's parent or NULL if the given @a element is the
 * root element.
 *
 * @ingroup SCEWElementHier
 */
extern scew_element* scew_element_parent (scew_element const *element);

extern scew_list* scew_element_children (scew_element const *element);

/**
 * Creates and adds, as a child of @a element, a new element with the
 * given @a name.
 *
 * @pre element != NULL
 * @pre name != NULL
 *
 * @return the new created element or NULL if an error is found.
 *
 * @ingroup SCEWElementHier
 */
extern scew_element* scew_element_add (scew_element *element,
				       XML_Char const *name);

/**
 * Adds a new child to the given @a element with the specified @a name
 * and @a contents.
 *
 * @pre element != NULL
 * @pre name != NULL
 *
 * @param element
 * @param name
 * @param contents
 *
 * @return the new created element or NULL if an error is found.
 *
 * @ingroup SCEWElementHier
 */
extern scew_element* scew_element_add_new_element (scew_element *element,
                                                   XML_Char const *name,
                                                   XML_Char const *contents);

/**
 * Adds a @a child to given @a element. Note that the element being
 * added should be a clean element, that is, an element created with
 * #scew_element_create, and not an element from another XML tree.
 *
 * @pre element != NULL
 * @pre child != NULL
 * @pre #scew_element_parent (child) == NULL
 * @pre #scew_element_count (child) == 0
 *
 * @return the element being added.
 *
 * @ingroup SCEWElementHier
 */
extern scew_element* scew_element_add_element (scew_element *element,
					       scew_element *child);

/**
 *
 *
 * @param element
 */
extern void scew_element_delete_all (scew_element *element);

/**
 * Deletes the first child of the given @a element that matches @a
 * name.
 *
 * @pre element != NULL
 * @pre name != NULL
 *
 * @ingroup SCEWElementHier
 */
extern void scew_element_delete_by_name (scew_element *element,
					 XML_Char const *name);

/**
 * Deletes the child of the given @a element at the specified
 * position.
 *
 * @pre element != NULL
 * @pre idx < #scew_element_count
 *
 * @ingroup SCEWElementHier
 */
extern void scew_element_delete_by_index (scew_element *element,
					  unsigned int idx);

/**
 * Deletes all children elements of the given @a element that match @a
 * name. This function will internally get an element list created by
 * #scew_element_list and will free all the elements in it. Note that
 * this function is not equivalent to #scew_element_list_free.
 *
 * @pre element != NULL
 * @pre name != NULL
 *
 * @ingroup SCEWElementHier
 */
extern void scew_element_detach (scew_element *element);


/**
 * @defgroup SCEWElementAttr Attributes
 * Handle element's attributes.
 * @ingroup SCEWElement
 */

/**
 * Returns the number of attributes of the specified element. An element
 * can have zero or more attributes.
 *
 * @pre element != NULL
 *
 * @ingroup SCEWElementAttr
 */
extern unsigned int scew_element_attribute_count (scew_element const *element);

/**
 * Iterate through the @a element's attributes.
 *
 * Call this function a first time with <code>attribute</code> to NULL
 * and the first attribute will be returned. In the subsequent calls you
 * just need to provide the attribute returned and its contiguous
 * attribute will be returned.
 *
 * @pre element != NULL
 *
 * @see SCEWAttribute
 *
 * @return the first attribute of an element or a contiguous
 * attribute. NULL if there are no more attributes.
 *
 * @ingroup SCEWElementAttr
 */
extern scew_list* scew_element_attributes (scew_element const *element);

/**
 * Returns the element attribute with the specified name. Remember that
 * XML names are case-sensitive.
 *
 * @pre element != NULL
 * @pre name != NULL
 *
 * @see SCEWAttribute
 *
 * @return the attribute with the given name, NULL if not found.
 *
 * @ingroup SCEWElementAttr
 */
extern scew_attribute*
scew_element_attribute_by_name (scew_element const *element,
				XML_Char const *name);

/**
 * Returns the element attribute with the specified name. Remember that
 * XML names are case-sensitive.
 *
 * @pre element != NULL
 * @pre name != NULL
 *
 * @see SCEWAttribute
 *
 * @return the attribute with the given name, NULL if not found.
 *
 * @ingroup SCEWElementAttr
 */
extern scew_attribute*
scew_element_attribute_by_index (scew_element const *element,
                                 unsigned int idx);

/**
 * Adds an existent @a attribute to the given @a element. If the @a
 * attribute already exists, the old value will be overwritten. It is
 * important to note that the given attribute given will be part of
 * the element's attributes (ownership is lost), so it should not be
 * freed, and it should not be part of another attribute element list.
 *
 * @pre element != NULL
 * @pre attribute != NULL
 *
 * @see SCEWAttribute
 *
 * @return the new attribute added to the element.
 *
 * @ingroup SCEWElementAttr
 */
extern scew_attribute* scew_element_add_attribute (scew_element *element,
						   scew_attribute *attribute);

/**
 * Creates and adds a new attribute to the given @a element. An
 * attribute is formed by a pair (name, value). If the attribute
 * already exists, the old value will be overwritten.
 *
 * @pre element != NULL
 * @pre name != NULL
 * @pre value != NULL
 *
 * @see SCEWAttribute
 *
 * @return the new attribute added to the element.
 *
 * @ingroup SCEWElementAttr
 */
extern scew_attribute* scew_element_add_new_attribute (scew_element *element,
                                                       XML_Char const *name,
                                                       XML_Char const *value);

extern void scew_element_delete_attribute_all (scew_element *element);

/**
 * Deletes an attribute from an element.
 *
 * @pre element != NULL
 * @pre name != NULL
 *
 * @ingroup SCEWElementAttr
 */
extern void scew_element_delete_attribute (scew_element *element,
                                           scew_attribute *attribute);

extern void scew_element_delete_attribute_by_name (scew_element *element,
                                                   XML_Char const* name);

extern void scew_element_delete_attribute_by_index (scew_element *element,
                                                    unsigned int idx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ELEMENT_H_0211250048 */
