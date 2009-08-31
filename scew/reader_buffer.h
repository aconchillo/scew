/**
 * @file     reader_buffer.h
 * @brief    SCEW reader buffer related functions
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Tue Aug 25, 2009 02:02
 * @ingroup  SCEWReader
 *
 * @if copyright
 *
 * Copyright (C) 2009 Aleix Conchillo Flaque
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

#ifndef READER_BUFFER_H_0908250202
#define READER_BUFFER_H_0908250202

#include "reader.h"

#include <expat.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern scew_reader* scew_reader_buffer_create (XML_Char const *buffer,
                                               size_t size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // READER_BUFFER_H_0908250202