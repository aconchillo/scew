/**
 * @file     writer.h
 * @brief    SCEW writer functions
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Sep 11, 2003 00:36
 *
 * @if copyright
 *
 * Copyright (C) 2003-2008 Aleix Conchillo Flaque
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


#ifndef WRITER_H_0309110036
#define WRITER_H_0309110036

#include "tree.h"
#include "attribute.h"

#include <expat.h>

#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct scew_writer scew_writer;

extern scew_writer* scew_writer_file_create (char const *file_name);

extern scew_writer* scew_writer_fp_create (FILE *file);

extern scew_writer* scew_writer_buffer_create (XML_Char *buffer,
                                               unsigned int size);

extern void scew_writer_set_indented (scew_writer *writer, bool indented);

extern void scew_writer_set_indent_spaces (scew_writer *writer,
                                           unsigned int spaces);

extern bool scew_writer_close (scew_writer *writer);

extern void scew_writer_free (scew_writer *writer);

extern void scew_writer_print_tree (scew_writer *writer,
                                    scew_tree const *tree);

extern void scew_writer_print_element (scew_writer *writer,
                                       scew_element const *element);

extern void scew_writer_print_element_children (scew_writer *writer,
                                                scew_element const  *element);

extern void scew_writer_print_element_attributes (scew_writer *writer,
                                                  scew_element const *element);

extern void scew_writer_print_attribute (scew_writer *writer,
                                         scew_attribute const *attribute);

/**
 * Saves an XML tree to the specified file. If the file doesn't exist it
 * will create it, and if it exists it will overwrite it.
 *
 * @return true if tree was successfully saved, false otherwise.
 */
/* extern bool scew_writer_tree_file (scew_tree const *tree, */
/*                                    char const *file_name); */

/**
 * Saves an XML tree to the already created file pointer.
 *
 * @return true if tree was successfully saved, false otherwise.
 */
/* extern bool scew_writer_tree_fp (scew_tree const *tree, FILE *out); */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WRITER_H_0309110036 */
