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
#include "xerror.h"

#include "str.h"

#include <assert.h>
#include <stdarg.h>


/* Private */

typedef struct
{
  scew_writer writer;
  XML_Char *buffer;
  XML_Char *temp_buffer;
  unsigned int size;
  unsigned int current;
} scew_writer_buffer;

static scew_bool buffer_close_ (scew_writer *writer);
static scew_bool buffer_printf_ (scew_writer *writer,
                                 XML_Char const *format, ...);


/* Public */

scew_writer*
scew_writer_buffer_create (XML_Char *buffer, unsigned int size)
{
  scew_writer_buffer *buf_writer = NULL;

  assert (buffer != NULL);
  assert (size > 0);

  buf_writer = calloc (1, sizeof (scew_writer_buffer));

  if (buf_writer != NULL)
    {
      buf_writer->temp_buffer = calloc (1, sizeof (XML_Char) * size);

      if (buf_writer != NULL)
        {
          scew_writer *writer = (scew_writer *) buf_writer;

          buffer[0] = '\0';
          buf_writer->buffer = buffer;
          buf_writer->size = size;
          buf_writer->current = 0;

          writer->close = buffer_close_;
          writer->printf = buffer_printf_;

          scew_writer_set_indented (writer, SCEW_TRUE);
          scew_writer_set_indent_spaces (writer, DEFAULT_INDENT_SPACES_);
        }
      else
        {
          free (buf_writer);
          scew_error_set_last_error_ (scew_error_no_memory);
        }
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return (scew_writer *) buf_writer;
}


/* Private */

scew_bool
buffer_close_ (scew_writer *writer)
{
  scew_writer_buffer *buf_writer = (scew_writer_buffer *) writer;

  if (buf_writer->temp_buffer != NULL)
    {
      free (buf_writer->temp_buffer);
    }

  return SCEW_TRUE;
}

scew_bool
buffer_printf_ (scew_writer *writer, XML_Char const *format, ...)
{
  va_list args;
  int written = 0;
  size_t maxlen = 0;
  scew_writer_buffer *buf_writer = NULL;
  scew_bool result = SCEW_TRUE;

  assert (writer != NULL);
  assert (format != NULL);

  va_start (args, format);

  buf_writer = (scew_writer_buffer *) writer;

  maxlen = buf_writer->size - buf_writer->current;

#ifdef XML_UNICODE_WCHAR_T
  written = vswprintf (buf_writer->temp_buffer, maxlen, format, args);
#else
  written = vsprintf (buf_writer->temp_buffer, format, args);
#endif

  result = (written != -1) && (written <= maxlen);

  if (result)
    {
      scew_strcat (buf_writer->buffer, buf_writer->temp_buffer);
      buf_writer->current += written;
    }

  va_end (args);

  return result;
}
