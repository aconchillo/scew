/**
 * @file     writer_file.c
 * @brief    writer_file.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Jul 21, 2008 23:36
 *
 * @if copyright
 *
 * Copyright (C) 2008, 2009 Aleix Conchillo Flaque
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

#include <assert.h>


/* Private */

typedef struct
{
  FILE *file;
} scew_writer_fp;

static size_t file_write_ (scew_writer *writer,
                           void const *buffer,
                           size_t byte_no);
static scew_bool file_eow_ (scew_writer *reader);
static scew_bool file_error_ (scew_writer *reader);
static scew_bool file_close_ (scew_writer *writer);
static void file_free_ (scew_writer *writer);

static scew_writer_hooks const file_hooks_ =
  {
    file_write_,
    file_eow_,
    file_error_,
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

      /* Create writer */
      writer = scew_writer_create (&file_hooks_, fp_writer);
      if (writer == NULL)
        {
          free (fp_writer);
        }
    }

  return writer;
}


/* Private */

size_t
file_write_ (scew_writer *writer, void const *buffer, size_t byte_no)
{
  size_t written_no = 0;
  scew_writer_fp *fp_writer = NULL;

  assert (writer != NULL);
  assert (buffer != NULL);

  fp_writer = scew_writer_data (writer);
  written_no = fwrite (buffer, 1, byte_no, fp_writer->file);

  return written_no;
}

scew_bool
file_eow_ (scew_writer *writer)
{
  scew_writer_fp *fp_writer = NULL;

  assert (writer != NULL);

  fp_writer = scew_writer_data (writer);

  return (feof (fp_writer->file) != 0);
}

scew_bool
file_error_ (scew_writer *writer)
{
  scew_writer_fp *fp_writer = NULL;

  assert (writer != NULL);

  fp_writer = scew_writer_data (writer);

  return (ferror (fp_writer->file) != 0);
}

scew_bool
file_close_ (scew_writer *writer)
{
  int status = 0;
  scew_writer_fp *fp_writer = NULL;

  assert (writer != NULL);

  fp_writer = scew_writer_data (writer);

  /* Do not close standard output and standard error streams. */
  if ((stdout == fp_writer->file) || (stderr == fp_writer->file))
    {
      return SCEW_TRUE;
    }

  status = fclose (fp_writer->file);

  return (status == 0);
}

void
file_free_ (scew_writer *writer)
{
  scew_writer_fp *fp_writer = NULL;

  assert (writer != NULL);

  /* Close the file before freeing the writer. */
  (void) file_close_ (writer);

  fp_writer = scew_writer_data (writer);
  free (fp_writer);
}
