/**
 * @file     xwriter.h
 * @brief    Declaration of internal SCEW writer type
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Tue Jul 22, 2008 22:05
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
 **/

#ifndef XWRITER_H_0807222205
#define XWRITER_H_0807222205

#include "writer.h"


/* Constants */

enum
  {
    DEFAULT_INDENT_SPACES_ = 3  /**< Default number of indent spaces */
  };


/* Types */

typedef scew_bool (*scew_writer_close_callback) (scew_writer *);

typedef scew_bool (*scew_writer_printf_callback) (scew_writer *,
                                                  XML_Char const *, ...);

struct scew_writer
{
  scew_writer_close_callback close;
  scew_writer_printf_callback printf;
  scew_bool indented;
  unsigned int indent;
  unsigned int spaces;
};

#endif /* XWRITER_H_0807222205 */
