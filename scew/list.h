/**
 * @file     list.h
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Jul 12, 2007 20:09
 * @brief    General list implementation
 **/

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
