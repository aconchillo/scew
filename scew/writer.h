/**
 * @file     writer.h
 * @brief    SCEW writer functions
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Sep 11, 2003 00:36
 *
 * @if copyright
 *
 * Copyright (C) 2008 Aleix Conchillo Flaque
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
#include "bool.h"

#include <expat.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef struct scew_writer scew_writer;

typedef struct
{
  scew_bool (*printf) (scew_writer *, XML_Char const *, ...);
  scew_bool (*close) (scew_writer *);
  void (*free) (scew_writer *);
} scew_writer_hooks;



/**
 * @defgroup SCEWWriterAlloc Allocation
 * @ingroup SCEWWriter
 */

extern scew_writer* scew_writer_create (scew_writer_hooks *hooks);

extern void* scew_writer_interface (scew_writer *writer);

/**
 * Closes the given SCEW @a writer. This function will have different
 * effects depending on the SCEW writer type (e.g. it will close the
 * file for file streams). After calling this function, none of the
 * SCEW writer functions should be used, otherwise undefined behavior
 * is expected.
 *
 * @pre writer != NULL
 *
 * @param writer the SCEW writer to close.
 *
 * @return true if the writer could be successfully closed, false
 * otherwise.
 *
 * @ingroup SCEWWriterAlloc
 */
extern scew_bool scew_writer_close (scew_writer *writer);

/**
 * Frees the memory allocated by the given SCEW @a writer. This
 * function will automatically close the SCEW writer.
 *
 * @pre writer != NULL
 *
 * @param writer the SCEW writer to free.
 *
 * @ingroup SCEWWriterAlloc
 */
extern void scew_writer_free (scew_writer *writer);


/**
 * @defgroup SCEWWriterProp Properties
 * @ingroup SCEWWriter
 */

/**
 * Tells whether the output sent to the given SCEW @a writer should be
 * @a indented or not.
 *
 * @pre writer != NULL
 *
 * @param writer the SCEW writer to change its indentation for.
 * @param indented true if the output should be indented, false
 * otherwise.
 *
 * @ingroup SCEWWriterProp
 */
extern void scew_writer_set_indented (scew_writer *writer, scew_bool indented);

/**
 * Sets the number of @a spaces to use when indenting output for the
 * given SCEW @a writer.
 *
 * @pre writer != NULL
 *
 * @param writer the SCEW writer to change its indentation spaces for.
 * @param spaces the number of spaces to use for indentation.
 *
 * @ingroup SCEWWriterProp
 */
extern void scew_writer_set_indent_spaces (scew_writer *writer,
                                           unsigned int spaces);


/**
 * @defgroup SCEWWriterOutput Output
 * @ingroup SCEWWriter
 */

/**
 * Prints the given SCEW @a tree to @a writer. This will print the XML
 * document prolog and the root element with all its children.
 *
 * @pre writer != NULL
 * @pre tree != NULL
 *
 * @param writer
 * @param tree
 *
 * @ingroup SCEWWriterOutput
 */
extern scew_bool scew_writer_print_tree (scew_writer *writer,
                                         scew_tree const *tree);

/**
 *
 * @pre writer != NULL
 * @pre element != NULL
 *
 * @ingroup SCEWWriterOutput
 */
extern scew_bool scew_writer_print_element (scew_writer *writer,
                                            scew_element const *element);

/**
 *
 * @pre writer != NULL
 * @pre element != NULL
 *
 * @ingroup SCEWWriterOutput
 */
extern scew_bool
scew_writer_print_element_children (scew_writer *writer,
                                    scew_element const  *element);

/**
 *
 * @pre writer != NULL
 * @pre element != NULL
 *
 * @ingroup SCEWWriterOutput
 */
extern scew_bool
scew_writer_print_element_attributes (scew_writer *writer,
                                      scew_element const *element);

/**
 *
 * @pre writer != NULL
 * @pre attribute != NULL
 *
 * @ingroup SCEWWriterOutput
 */
extern scew_bool
scew_writer_print_attribute (scew_writer *writer,
                             scew_attribute const *attribute);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WRITER_H_0309110036 */
