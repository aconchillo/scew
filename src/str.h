/**
 *
 * @file     str.h
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Sun Dec 01, 2002 13:05
 * @brief    SCEW string functions
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


#ifndef STR_H_ALEIX0212011305
#define STR_H_ALEIX0212011305

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

/**
 * Calculates the length of the initial segment of <code>s</code> which
 * consists entirely of characters in <code>accept</code>.
 */
extern size_t
scew_strspn(XML_Char const* s, XML_Char const* accept);

/**
 * Trims off extra spaces from the beginning and end of a string.
 */
extern void
scew_strtrim(XML_Char* src);

/**
 * Checks for an alphanumeric character; it is equivalent to
 * (scew_isalpha(c) || scew_isdigit(c)).
 */
extern int
scew_isalnum(XML_Char c);

/**
 * Checks for an alphabetic character; in the standard "C" locale, it is
 * equivalent to (scew_isupper(c) || scew_islower(c)). In some locales,
 * there may be additional characters for which scew_isalpha() is
 * true--letters which are neither upper case nor lower case.
 */
extern int
scew_isalpha(XML_Char c);

/**
 * Checks for a control character.
 */
extern int
scew_iscntrl(XML_Char c);

/**
 * Checks for a digit (0 through 9).
 */
extern int
scew_isdigit(XML_Char c);

/**
 * Checks for any printable character except space.
 */
extern int
scew_isgraph(XML_Char c);

/**
 * Checks for a lower-case character.
 */
extern int
scew_islower(XML_Char c);

/**
 * Checks for any printable character including space.
 */
extern int
scew_isprint(XML_Char c);

/**
 * Checks for any printable character which is not a space or an
 * alphanumeric character.
 */
extern int
scew_ispunct(XML_Char c);

/**
 * Checks for white-space characters. In the "C" and "POSIX" locales,
 * these are: space, form-feed, newline, carriage return, horizontal
 * tab, and vertical tab.
 */
extern int
scew_isspace(XML_Char c);

/**
 * Checks for an uppercase letter.
 */
extern int
scew_isupper(XML_Char c);

/**
 * Checks for a hexadecimal digits, i.e. one of <b>0 1 2 3 4 5 6 7 8 9 a
 * b c d e f A B C D E F</b>.
 */
extern int
scew_isxdigit(XML_Char c);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STR_H_ALEIX0212011305 */
