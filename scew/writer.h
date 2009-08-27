/**
 * @file     writer.h
 * @brief    SCEW writer functions
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Sep 11, 2003 00:36
 * @ingroup  SCEWWriter
 *
 * @if copyright
 *
 * Copyright (C) 2008-2009 Aleix Conchillo Flaque
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
 * @defgroup SCEWWriter Writers
 * @ingroup SCEWIO
 */

#ifndef WRITER_H_0309110036
#define WRITER_H_0309110036

#include "tree.h"
#include "attribute.h"
#include "bool.h"

#include <expat.h>

#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef struct scew_writer scew_writer;

typedef struct
{
  size_t (*write) (scew_writer *, void const *, size_t);
  scew_bool (*eow) (scew_writer *);
  scew_bool (*error) (scew_writer *);
  scew_bool (*close) (scew_writer *);
  void (*free) (scew_writer *);
} scew_writer_hooks;



/**
 * @defgroup SCEWWriterAlloc Allocation
 * @ingroup SCEWWriter
 */

extern scew_writer* scew_writer_create (scew_writer_hooks const *hooks,
                                        void *data);

extern void* scew_writer_data (scew_writer *writer);

extern size_t scew_writer_write (scew_writer *writer,
                                 void const *buffer,
                                 size_t byte_no);

extern scew_bool scew_writer_eow (scew_writer *writer);

extern scew_bool scew_writer_error (scew_writer *writer);

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WRITER_H_0309110036 */
