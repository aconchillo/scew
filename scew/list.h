/**
 * @file     list.h
 * @brief    SCEW general list implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Jul 12, 2007 20:09
 *
 * @if copyright
 *
 * Copyright (C) 2007-2008 Aleix Conchillo Flaque
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
 **/

/**
 * @defgroup SCEWList Lists
 *
 * These are the parser functions that allow to read an XML tree from a
 * file or a memory buffer.
 */

#ifndef LIST_H_0707122009
#define LIST_H_0707122009

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct scew_list scew_list;

typedef void (*scew_list_function) (scew_list *, void *);

typedef bool (*scew_cmp_function) (void const *, void const *);


/**
 * @name Allocation
 */

extern scew_list* scew_list_create (void *data);

extern void scew_list_free (scew_list *list);


/**
 * @name Accessors
 */

extern void* scew_list_data (scew_list *list);

extern unsigned int scew_list_size (scew_list *list);


/**
 * @name Modifiers
 */

extern scew_list* scew_list_append (scew_list *list, void *data);

extern scew_list* scew_list_prepend (scew_list *list, void *data);

extern scew_list* scew_list_delete (scew_list *list, void *data);

extern scew_list* scew_list_delete_item (scew_list *list,
                                         scew_list *item);


/**
 * @name Traverse
 */

extern scew_list* scew_list_first (scew_list *list);

extern scew_list* scew_list_last (scew_list *list);

extern scew_list* scew_list_next (scew_list *list);

extern scew_list* scew_list_previous (scew_list *list);

extern void scew_list_foreach (scew_list *list,
                               scew_list_function func,
                               void *user_data);

/**
 * @name Search
 */

extern scew_list* scew_list_find (scew_list *list, void *data);

extern scew_list* scew_list_find_custom (scew_list *list,
                                         void const *data,
                                         scew_cmp_function func);

extern scew_list* scew_list_by_index (scew_list *list,
                                      unsigned int idx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIST_H_0707122009 */
