/**
 * @file     writer_file.c
 * @brief    writer_file.h implementation
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

#include "writer_file.h"

#include "str.h"

#include <assert.h>
#include <stdarg.h>


/* Private */

typedef struct
{
  FILE *file;
} scew_writer_fp;

static scew_bool file_printf_ (scew_writer *writer,
                               XML_Char const *format, ...);
static scew_bool file_close_ (scew_writer *writer);
static void file_free_ (scew_writer *writer);

static scew_writer_interface interface =
  {
    file_printf_,
    file_close_,
    file_free_
  };


/* Public */

scew_writer*
scew_writer_file_create (char const *file_name)
{
  FILE *file = NULL;
  scew_writer *writer = NULL;

  assert (file_name != NULL);

  file = fopen (file_name, "wb");

  if (file != NULL)
    {
      writer = scew_writer_fp_create (file);
    }

  return writer;
}

scew_writer*
scew_writer_fp_create (FILE *file)
{
  scew_writer *writer = NULL;
  scew_writer_fp *fp_writer = NULL;

  assert (file != NULL);

  fp_writer = calloc (1, sizeof (scew_writer_fp));

  if (fp_writer != NULL)
    {
      fp_writer->file = file;

      writer = scew_writer_create (&interface, fp_writer);
      if (writer == NULL)
        {
          free (fp_writer);
        }
    }

  return writer;
}


/* Private */

scew_bool
file_printf_ (scew_writer *writer, XML_Char const *format, ...)
{
  va_list args;
  int written = 0;
  scew_writer_fp *fp_writer = NULL;

  assert (writer != NULL);
  assert (format != NULL);

  va_start (args, format);

  fp_writer = scew_writer_interface_data (writer);
  written = scew_vfprintf (fp_writer->file, format, args);

  va_end (args);

  return (written > 0);
}

scew_bool
file_close_ (scew_writer *writer)
{
  scew_writer_fp *fp_writer = scew_writer_interface_data (writer);

  /* Do not close standard output and standard error streams. */
  if ((stdout == fp_writer->file) || (stderr == fp_writer->file))
    {
      return SCEW_TRUE;
    }

  int status = fclose (fp_writer->file);

  return (status == 0);
}

void
file_free_ (scew_writer *writer)
{
  scew_writer_fp *fp_writer = scew_writer_interface_data (writer);

  (void) file_close_ (writer);

  free (fp_writer);
}
