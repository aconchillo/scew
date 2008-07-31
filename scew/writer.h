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

/**
 * @defgroup SCEWWriter Writer
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


/**
 * @defgroup SCEWWriterAlloc Allocation
 * @ingroup SCEWWriter
 */

/**
 * @ingroup SCEWWriterAlloc
 */
extern scew_writer* scew_writer_file_create (char const *file_name);

/**
 * @ingroup SCEWWriterAlloc
 */
extern scew_writer* scew_writer_fp_create (FILE *file);

/**
 * @ingroup SCEWWriterAlloc
 */
extern scew_writer* scew_writer_buffer_create (XML_Char *buffer,
                                               unsigned int size);

/**
 * @ingroup SCEWWriterAlloc
 */
extern bool scew_writer_close (scew_writer *writer);

/**
 * @ingroup SCEWWriterAlloc
 */
extern void scew_writer_free (scew_writer *writer);


/**
 * @defgroup SCEWWriterProp Properties
 * @ingroup SCEWWriter
 */

/**
 * @ingroup SCEWWriterProp
 */
extern void scew_writer_set_indented (scew_writer *writer, bool indented);

/**
 * @ingroup SCEWWriterProp
 */
extern void scew_writer_set_indent_spaces (scew_writer *writer,
                                           unsigned int spaces);


/**
 * @defgroup SCEWWriterOutput Output
 * @ingroup SCEWWriter
 */

/**
 *
 * @pre writer != NULL
 * @pre tree != NULL
 *
 * @ingroup SCEWWriterOutput
 */
extern bool scew_writer_print_tree (scew_writer *writer,
                                    scew_tree const *tree);

/**
 *
 * @pre writer != NULL
 * @pre element != NULL
 *
 * @ingroup SCEWWriterOutput
 */
extern bool scew_writer_print_element (scew_writer *writer,
                                       scew_element const *element);

/**
 *
 * @pre writer != NULL
 * @pre element != NULL
 *
 * @ingroup SCEWWriterOutput
 */
extern bool scew_writer_print_element_children (scew_writer *writer,
                                                scew_element const  *element);

/**
 *
 * @pre writer != NULL
 * @pre element != NULL
 *
 * @ingroup SCEWWriterOutput
 */
extern bool scew_writer_print_element_attributes (scew_writer *writer,
                                                  scew_element const *element);

/**
 *
 * @pre writer != NULL
 * @pre attribute != NULL
 *
 * @ingroup SCEWWriterOutput
 */
extern bool scew_writer_print_attribute (scew_writer *writer,
                                         scew_attribute const *attribute);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WRITER_H_0309110036 */
