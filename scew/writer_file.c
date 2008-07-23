/**
 * @file     writer_file.c
 * @brief    writer.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Jul 21, 2008 23:36
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

#include "str.h"

#include "xerror.h"

#include <assert.h>
#include <stdarg.h>


// Private

typedef struct
{
  scew_writer writer;
  FILE *file;
} scew_writer_fp;

static bool file_close_ (scew_writer *writer);
static bool file_printf_ (scew_writer *writer, XML_Char const *format, ...);


// Public

scew_writer*
scew_writer_file_create (char const *file_name)
{
  assert (file_name != NULL);

  scew_writer_fp *fp_writer  = calloc (1, sizeof (scew_writer_fp));

  if (fp_writer != NULL)
    {
      FILE *file = fopen (file_name, "wb");

      if (file != NULL)
        {
          fp_writer->file = file;

          scew_writer *writer = (scew_writer *) fp_writer;
          writer->close = file_close_;
          writer->printf = file_printf_;

          scew_writer_set_indented (writer, true);
          scew_writer_set_indent_spaces (writer, DEFAULT_INDENT_SPACES_);
        }
      else
        {
          scew_error_set_last_error_ (scew_error_io);
        }
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return (scew_writer *) fp_writer;
}


// Private

bool
file_close_ (scew_writer *writer)
{
  scew_writer_fp *fp_writer = (scew_writer_fp *) writer;

  int status = fclose (fp_writer->file);
  bool result = (status == 0);

  if (!result)
    {
      scew_error_set_last_error_ (scew_error_io);
    }

  return result;
}

bool
file_printf_ (scew_writer *writer, XML_Char const *format, ...)
{
  assert (writer != NULL);
  assert (format != NULL);

  va_list args;

  va_start (args, format);

  scew_writer_fp *fp_writer = (scew_writer_fp *) writer;
  int written = scew_vfprintf (fp_writer->file, format, args);

  va_end (args);

  return (written < 0);
}
