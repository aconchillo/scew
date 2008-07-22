/**
 * @file     writer_buffer.c
 * @brief    writer.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Jul 21, 2008 23:40
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

#include "writer.h"

#include "xwriter.h"

#include <assert.h>


// Private

typedef struct
{
  scew_writer writer;
  XML_Char *buffer;
  unsigned int size;
  unsigned int current;
} scew_writer_buffer;


// Public

scew_writer*
scew_writer_buffer_create (XML_Char *buffer, unsigned int size)
{
  assert (buffer != NULL);
  assert (size > 0);

  return NULL;
}

