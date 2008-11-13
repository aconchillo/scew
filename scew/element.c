/**
 * @file     element.c
 * @brief    element.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 00:48
 *
 * @if copyright
 *
 * Copyright (C) 2002-2008 Aleix Conchillo Flaque
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

#include "element.h"

#include "attribute.h"
#include "list.h"
#include "str.h"

#include "xerror.h"

#include <assert.h>



/* Private */

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

static scew_bool cmp_name_ (void const *element, void const *name);
static scew_bool cmp_attr_name_ (void const *attribute, void const *name);

static scew_bool copy_children_ (scew_element *new_element,
                                 scew_element const *element);
static scew_bool copy_attributes_ (scew_element *new_element,
                                   scew_element const *element);
static scew_bool compare_children_ (scew_element const *a,
                                    scew_element const *b);
static scew_bool compare_attributes_ (scew_element const *a,
                                      scew_element const *b);


/* Public */


/* Allocation */

scew_element*
scew_element_create (XML_Char const *name)
{
  scew_element *element = NULL;

  assert (name != NULL);

  element = calloc (1, sizeof (scew_element));

  if (element != NULL)
    {
      scew_element_set_name (element, name);
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return element;
}

scew_element*
scew_element_copy (scew_element const *element)
{
  scew_element *new_elem = calloc (1, sizeof (scew_element));

  if (new_elem != NULL)
    {
      scew_bool copied =
        ((element->contents == NULL)
         || (scew_element_set_contents (new_elem, element->contents) != NULL));

      copied = copied
        && (scew_element_set_name (new_elem, element->name) != NULL)
        && copy_children_ (new_elem, element)
        && copy_attributes_ (new_elem, element);

      if (!copied)
        {
          scew_element_free (new_elem);
          new_elem = NULL;
        }
    }

  return new_elem;
}

void
scew_element_free (scew_element *element)
{
  if (element != NULL)
    {
      scew_element_delete_all (element);
      scew_element_delete_attribute_all (element);
      scew_element_detach (element);

      free (element->name);
      if (element->contents != NULL)
        {
          free (element->contents);
        }
      free (element);
    }
}


/* Searching */

scew_element*
scew_element_by_name (scew_element const *element, XML_Char const *name)
{
  scew_list *item = NULL;

  assert (element != NULL);
  assert (name != NULL);

  if (element->children != NULL)
    {
      item = scew_list_find_custom (element->children, name, cmp_name_);
    }

  return (item == NULL) ? NULL : (scew_element *) scew_list_data (item);
}

scew_element*
scew_element_by_index (scew_element const *element, unsigned int idx)
{
  scew_list *item = NULL;

  assert (element != NULL);
  assert (idx < element->n_children);

  item = scew_list_index (element->children, idx);

  return (item == NULL) ? NULL : (scew_element *) scew_list_data (item);
}

scew_list*
scew_element_list_by_name (scew_element const *element, XML_Char const *name)
{
  scew_list *list = NULL;
  scew_list *last = NULL;
  scew_list *item = NULL;

  assert (element != NULL);
  assert (name != NULL);

  item = element->children;
  while (item != NULL)
    {
      item = scew_list_find_custom (item, name, cmp_name_);
      if (item != NULL)
        {
          last = scew_list_append (last, item);
          if (list == NULL)
            {
              list = last;
            }
        }
      item = scew_list_next (item);
    }

  return list;
}


/* Comparisson */

scew_bool
scew_element_compare (scew_element const *a, scew_element const *b)
{
  scew_bool equal = SCEW_TRUE;

  assert (a != NULL);
  assert (b != NULL);

  if ((a->contents != NULL) && (b->contents != NULL))
    {
      equal = (scew_strcmp (a->contents, b->contents) == 0);
    }

  equal = equal
    && (scew_strcmp (a->name, b->name) == 0)
    && compare_children_ (a, b)
    && compare_attributes_ (a, b);

  return equal;
}


/* Accessors */

XML_Char const*
scew_element_name (scew_element const *element)
{
  assert (element != NULL);

  return element->name;
}

XML_Char const*
scew_element_contents (scew_element const *element)
{
  assert (element != NULL);

  return element->contents;
}

XML_Char const*
scew_element_set_name (scew_element *element, XML_Char const *name)
{
  XML_Char *new_name = NULL;

  assert (element != NULL);
  assert (name != NULL);

  new_name = scew_strdup (name);
  if (new_name != NULL)
    {
      free (element->name);
      element->name = new_name;
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return new_name;
}

XML_Char const*
scew_element_set_contents (scew_element *element, XML_Char const *contents)
{
  XML_Char *new_contents = NULL;

  assert (element != NULL);
  assert (contents != NULL);

  new_contents = scew_strdup (contents);

  if (new_contents != NULL)
    {
      if (element->contents != NULL)
        {
          free (element->contents);
        }
      element->contents = new_contents;
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return new_contents;
}

void
scew_element_free_contents (scew_element *element)
{
  assert (element != NULL);

  if (element->contents != NULL)
    {
      free (element->contents);
      element->contents = NULL;
    }
}


/* Hierarchy */

unsigned int
scew_element_count (scew_element const *element)
{
  assert (element != NULL);

  return element->n_children;
}

scew_element*
scew_element_parent (scew_element const *element)
{
  assert (element != NULL);

  return element->parent;
}

scew_list*
scew_element_children (scew_element const *element)
{
  assert (element != NULL);

  return element->children;
}

scew_element*
scew_element_add (scew_element *element, XML_Char const *name)
{
  scew_element *add_elem = NULL;
  scew_element *new_elem = NULL;

  assert (element != NULL);
  assert (name != NULL);

  new_elem = scew_element_create (name);

  if (new_elem != NULL)
    {
      add_elem = scew_element_add_element (element, new_elem);

      /* Delete element if it can not be added */
      if (add_elem == NULL)
        {
          scew_element_free (new_elem);
        }
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return add_elem;
}

scew_element*
scew_element_add_pair (scew_element *element,
                       XML_Char const *name,
                       XML_Char const *contents)
{
  scew_element *add_elem = NULL;
  scew_element *new_elem = NULL;

  assert (element != NULL);
  assert (name != NULL);
  assert (contents != NULL);

  add_elem = NULL;
  new_elem = scew_element_create (name);

  if (new_elem != NULL)
    {
      XML_Char const *add_contents = scew_element_set_contents (new_elem,
                                                                contents);

      /**
       * If contents could not be created does not affect adding an
       * element (we will treat the error below).
       */
      add_elem = scew_element_add_element (element, new_elem);

      /**
       * Delete element if unable t add contents or new element can
       * not be added.
       */
      if ((add_contents == NULL) || (NULL == add_elem))
        {
          scew_element_free (new_elem);
        }
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return add_elem;
}

scew_element*
scew_element_add_element (scew_element *element, scew_element *child)
{
  scew_list *item = NULL;

  assert (element != NULL);
  assert (child != NULL);
  assert (scew_element_parent (child) == NULL);

  item = scew_list_append (element->last_child, child);

  if (item != NULL)
    {
      if (element->children == NULL)
        {
          element->children = item;
        }
      child->parent = element;
      child->myself = item;

      element->last_child = item;
      ++element->n_children;
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
      child = NULL;
    }

  return child;
}

void
scew_element_delete_all (scew_element *element)
{
  scew_list *list = NULL;

  assert (element != NULL);

  list = element->children;
  while (list != NULL)
    {
      scew_element *aux = scew_list_data (list);
      list = scew_list_next (list);
      scew_element_free (aux);
    }

  /* Do not free element->children as childs are already detached. */

  element->children = NULL;
  element->last_child = NULL;
  element->n_children = 0;
}

void
scew_element_delete_all_by_name (scew_element *element, XML_Char const *name)
{
  scew_element *child = NULL;

  assert (element != NULL);
  assert (name != NULL);

  child = scew_element_by_name (element, name);
  while (child != NULL)
    {
      scew_element_free (child);

      child = scew_element_by_name (element, name);
    }
}

void
scew_element_delete_by_name (scew_element *element, XML_Char const *name)
{
  assert (element != NULL);
  assert (name != NULL);

  scew_element_free (scew_element_by_name (element, name));
}

void
scew_element_delete_by_index (scew_element *element, unsigned int idx)
{
  assert (element != NULL);
  assert (idx < element->n_children);

  scew_element_free (scew_element_by_index (element, idx));
}

void
scew_element_detach (scew_element *element)
{
  scew_element *parent = NULL;

  assert (element != NULL);

  parent = element->parent;

  if (parent != NULL)
    {
      if (parent->last_child == element->myself)
        {
          parent->last_child = scew_list_previous (element->myself);
        }

      parent->children = scew_list_delete_item (parent->children,
                                                element->myself);

      --parent->n_children;
      if (parent->n_children == 0)
        {
          parent->children = NULL;
          parent->last_child = NULL;
        }

      element->parent = NULL;
      element->myself = NULL;
    }
}


/* Attributes */

unsigned int
scew_element_attribute_count (scew_element const *element)
{
  assert (element != NULL);

  return element->n_attributes;
}

scew_list*
scew_element_attributes (scew_element const *element)
{
  assert (element != NULL);

  return element->attributes;
}

scew_attribute*
scew_element_attribute_by_name (scew_element const *element,
				XML_Char const *name)
{
  scew_list *item = NULL;

  assert (element != NULL);
  assert (name != NULL);

  if (element->attributes != NULL)
    {
      item = scew_list_find_custom (element->attributes, name, cmp_attr_name_);
    }

  return (item == NULL) ? NULL : (scew_attribute *) scew_list_data (item);
}

scew_attribute*
scew_element_attribute_by_index (scew_element const *element, unsigned int idx)
{
  scew_list *item = NULL;

  assert (element != NULL);
  assert (idx < element->n_attributes);

  if (element->attributes != NULL)
    {
      item = scew_list_index (element->attributes, idx);
    }

  return (item == NULL) ? NULL : (scew_attribute *) scew_list_data (item);
}

scew_attribute*
scew_element_add_attribute (scew_element *element, scew_attribute *attribute)
{
  scew_attribute *old_attribute = NULL;

  assert (element != NULL);
  assert (attribute != NULL);

  old_attribute =
    scew_element_attribute_by_name (element, scew_attribute_name (attribute));

  /* If attribute is not in the element, append to its attributes. */
  if (old_attribute == NULL)
    {
      scew_list *item = NULL;

      /* Detach given attribute from its old element. */
      scew_attribute_detach (attribute);

      item = scew_list_append (element->last_attribute, attribute);

      if (item != NULL)
        {
          if (element->attributes == NULL)
            {
              element->attributes = item;
            }
          scew_attribute_set_parent (attribute, element);
          element->last_attribute = item;
          ++element->n_attributes;

          /* This is the return value. */
          old_attribute = attribute;
        }
      else
        {
          scew_error_set_last_error_ (scew_error_no_memory);
        }
    }
  else
    {
      /* Assign new attribute value. */
      (void) scew_attribute_set_value (old_attribute,
                                       scew_attribute_value (attribute));
    }

  return old_attribute;
}

scew_attribute*
scew_element_add_attribute_pair (scew_element *element,
                                 XML_Char const *name,
                                 XML_Char const *value)
{
  scew_attribute *add_attr = NULL;
  scew_attribute *attribute = NULL;

  assert (element != NULL);
  assert (name != NULL);
  assert (value != NULL);

  attribute = scew_attribute_create (name, value);

  if (attribute != NULL)
    {
      add_attr = scew_element_add_attribute (element, attribute);
      if (add_attr == NULL)
        {
          scew_attribute_free (attribute);
        }
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return add_attr;
}

void
scew_element_delete_attribute (scew_element *element,
                               scew_attribute *attribute)
{
  assert (element != NULL);
  assert (attribute != NULL);

  element->attributes = scew_list_delete (element->attributes, attribute);
}

void
scew_element_delete_attribute_all (scew_element *element)
{
  scew_list *list = NULL;

  assert (element != NULL);

  list = element->attributes;
  while (list != NULL)
    {
      scew_attribute *aux = scew_list_data (list);
      list = scew_list_next (list);
      scew_attribute_free (aux);
    }
  scew_list_free (element->attributes);

  element->attributes = NULL;
  element->last_attribute = NULL;
  element->n_attributes = 0;
}

void
scew_element_delete_attribute_by_name (scew_element *element,
                                       XML_Char const* name)
{
  assert (element != NULL);
  assert (name != NULL);

  if (element->attributes != NULL)
    {
      scew_list *item =
        scew_list_find_custom (element->attributes, name, cmp_attr_name_);

      if (item != NULL)
        {
          element->attributes =
            scew_list_delete_item (element->attributes, item);
        }
    }
}

void
scew_element_delete_attribute_by_index (scew_element *element,
                                        unsigned int idx)
{
  assert (element != NULL);
  assert (idx < element->n_attributes);

  if (element->attributes != NULL)
    {
      scew_list *item = scew_list_index (element->attributes, idx);

      if (item != NULL)
        {
          element->attributes =
            scew_list_delete_item (element->attributes, item);
        }
    }
}


/* Private */

scew_bool
cmp_name_ (void const *element, void const *name)
{
  return (scew_strcmp (((scew_element *) element)->name,
                       (XML_Char *) name) == 0);
}

scew_bool
cmp_attr_name_ (void const *attribute, void const *name)
{
  return (scew_strcmp (scew_attribute_name ((scew_attribute *) attribute),
                       (XML_Char *) name) == 0);
}

scew_bool
copy_children_ (scew_element *new_element, scew_element const *element)
{
  scew_bool copied = SCEW_TRUE;
  scew_list *list = NULL;

  assert (new_element != NULL);
  assert (element != NULL);

  list = element->children;
  while (copied && (list != NULL))
    {
      scew_element *child = scew_list_data (list);
      scew_element *new_child = scew_element_copy (child);
      copied =
        ((new_child != NULL)
         && (scew_element_add_element (new_element, new_child) != NULL));
      list = scew_list_next (list);
    }

  return copied;
}

scew_bool
copy_attributes_ (scew_element *new_element, scew_element const *element)
{
  scew_bool copied = SCEW_TRUE;
  scew_list *list = NULL;

  assert (new_element != NULL);
  assert (element != NULL);

  list = element->attributes;
  while (copied && (list != NULL))
    {
      scew_attribute *attr = scew_list_data (list);
      scew_attribute *new_attr = scew_attribute_copy (attr);
      copied =
        ((new_attr != NULL)
         && (scew_element_add_attribute (new_element, new_attr) != NULL));
      list = scew_list_next (list);
    }

  return copied;
}

scew_bool
compare_children_ (scew_element const *a, scew_element const *b)
{
  scew_bool equal = SCEW_TRUE;
  scew_list *list_a = NULL;
  scew_list *list_b = NULL;

  assert (a != NULL);
  assert (b != NULL);

  equal = (a->n_children == b->n_children);

  list_a = a->children;
  list_b = b->children;
  while (equal && (list_a != NULL) && (list_b != NULL))
    {
      scew_element *child_a = scew_list_data (list_a);
      scew_element *child_b = scew_list_data (list_b);
      equal = scew_element_compare (child_a, child_b);
      list_a = scew_list_next (list_a);
      list_b = scew_list_next (list_b);
    }

  return equal;
}

scew_bool
compare_attributes_ (scew_element const *a, scew_element const *b)
{
  scew_bool equal = SCEW_TRUE;
  scew_list *list_a = NULL;
  scew_list *list_b = NULL;

  assert (a != NULL);
  assert (b != NULL);

  equal = (a->n_attributes == b->n_attributes);

  list_a = a->attributes;
  list_b = b->attributes;
  while (equal && (list_a != NULL) && (list_b != NULL))
    {
      scew_attribute *attr_a = scew_list_data (list_a);
      scew_attribute *attr_b = scew_list_data (list_b);
      equal = scew_attribute_compare (attr_a, attr_b);
      list_a = scew_list_next (list_a);
      list_b = scew_list_next (list_b);
    }

  return equal;
}
