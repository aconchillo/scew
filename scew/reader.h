/**
 * @file     reader.h
 * @brief    SCEW reader functions
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Sun Nov 23, 2008 13:36
 * @ingroup  SCEWReader
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
 * @defgroup SCEWReader Readers
 * @ingroup SCEWIO
 */

#ifndef READER_H_0811231336
#define READER_H_0811231336

#include "export.h"

#include "bool.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct scew_reader scew_reader;

typedef struct
{
  size_t (*read) (scew_reader *, void *, size_t);
  scew_bool (*end) (scew_reader *);
  scew_bool (*error) (scew_reader *);
  scew_bool (*close) (scew_reader *);
  void (*free) (scew_reader *);
} scew_reader_hooks;

extern SCEW_API scew_reader*
scew_reader_create (scew_reader_hooks const *hooks, void *data);

extern SCEW_API void* scew_reader_data (scew_reader *reader);

extern SCEW_API size_t scew_reader_read (scew_reader *reader,
                                         void *buffer,
                                         size_t byte_no);

extern SCEW_API scew_bool scew_reader_end (scew_reader *reader);

extern SCEW_API scew_bool scew_reader_error (scew_reader *reader);

extern SCEW_API scew_bool scew_reader_close (scew_reader *reader);

extern SCEW_API void scew_reader_free (scew_reader *reader);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* READER_H_0811231336 */
