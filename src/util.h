/**
 *
 * @file     util.h
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Sun Dec 01, 2002 13:05
 * @brief    SCEW util functions
 *
 * $Id$
 *
 * @if copyright
 *
 * Copyright (C) 2002, 2003 Aleix Conchillo Flaque
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * @endif
 */


#ifndef UTIL_H_ALEIX0212011305
#define UTIL_H_ALEIX0212011305

#include <expat.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Copies an XML_Char string from source to destination.
 */
extern XML_Char*
scew_strcpy(XML_Char* dst, XML_Char const* src);

/**
 * Concatenates source string to destination string. Destination string
 * must have enough space.
 */
extern XML_Char*
scew_strcat(XML_Char* dst, XML_Char const* src);

/**
 * Copies not more than <code>len</code> characters from source to
 * destination.
 */
extern XML_Char*
scew_strncpy(XML_Char* dst, XML_Char const* src, size_t len);

/**
 * Concatenates not more than <code>len</code> characters from source
 * string to destination string. Destination string must have enough
 * space.
 */
extern XML_Char*
scew_strncat(XML_Char* dst, XML_Char const* src, size_t len);

/**
 * Creates a new copy of the given string. Client must free it.
 */
extern XML_Char*
scew_strdup(XML_Char const* src);

/**
 * Returns the length in characeters of the given string.
 */
extern size_t
scew_strlen(XML_Char const* src);

/**
 * Compares two strings. Returns an integer greater than, equal to, or
 * less than 0, according as the string <code>s1</code> is greater than,
 * equal to, or less than the string <code>s2</code>.
 */
extern int
scew_strcmp(XML_Char const* s1, XML_Char const* s2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UTIL_H_ALEIX0212011305 */
