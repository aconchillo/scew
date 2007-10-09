/**
 *
 * @file     xattribute.c
 * @brief    SCEW private attribute type declaration
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Dec 02, 2002 23:03
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

#include "xattribute.h"

#include "xerror.h"

#include "str.h"

#include <assert.h>

attribute_list*
attribute_list_create_ (void)
{
}

void
attribute_list_free_ (attribute_list *list)
{
}

scew_attribute*
attribute_list_add_ (attribute_list *list, scew_attribute *attribute)
{
}

void
attribute_list_delete_ (attribute_list *list, XML_Char const *name)
{
  scew_attribute* attribute = NULL;

  assert (list != NULL);
  assert (name != NULL);

  attribute = attribute_by_name_ (list, name);

  if (attribute != NULL)
    {
      scew_attribute *tmp_prev = attribute->prev;
      scew_attribute *tmp_next = attribute->next;

      if (tmp_prev != NULL)
        {
	  tmp_prev->next = tmp_next;
        }
      if (tmp_next != NULL)
        {
	  tmp_next->prev = tmp_prev;
        }

      if (attribute == list->first)
        {
	  list->first = tmp_next;
        }

      if (attribute == list->last)
        {
	  list->last = tmp_prev;
        }

      scew_attribute_free (attribute);
      list->size = list->size - 1;
    }
}

scew_attribute*
attribute_by_index_ (attribute_list *list, unsigned int idx)
{
  unsigned int i = 0;
  scew_attribute* attribute = NULL;

  assert (list != NULL);
  assert (idx < list->size);

  attribute = list->first;
  for (i = 0; (i < idx) && (attribute != NULL); ++i)
    {
      attribute = attribute->next;
    }

  return attribute;
}

scew_attribute*
attribute_by_name_ (attribute_list *list, XML_Char const *name)
{
  scew_attribute* attribute = NULL;

  assert (list != NULL);
  assert (name != NULL);

  attribute = list->first;
  while ((attribute != NULL) && scew_strcmp (attribute->name, name))
    {
      attribute = attribute->next;
    }

  return attribute;
}
