/**
 * @file     str.h
 * @brief    SCEW string functions
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Sun Dec 01, 2002 13:05
 *
 * @if copyright
 *
 * Copyright (C) 2002-2009 Aleix Conchillo Flaque
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

#ifndef STR_H_0212011305
#define STR_H_0212011305

#include "bool.h"

#include "export.h"

#include <expat.h>

#include <string.h>

#define scew_memcpy(dst, src, n)  memcpy (dst, src, sizeof (XML_Char) * (n))
#define scew_memmove(dst, src, n) memmove (dst, src, sizeof (XML_Char) * (n))

#ifdef XML_UNICODE_WCHAR_T

#include <wchar.h>
#include <wctype.h>

#define _XT(str) L##str

#define scew_printf wprintf
#define scew_fprintf fwprintf
#define scew_vfprintf vfwprintf
#define scew_fputs fputws
#define scew_fgets fgetws
#define scew_fputc fputwc
#define scew_fgetc fgetwc

#define scew_strspn(wcs, accept) wcsspn (wcs, accept)
#define scew_strcpy(dest, src) wcscpy (dest, src)
#define scew_strcat(dest, src) wcscat (dest, src)
#define scew_strncpy(dest, src, n) wcsncpy (dest, src, n)
#define scew_strncat(dest, src, n) wcsncat (dest, src, n)
#define scew_strlen(s) wcslen (s)

#define scew_isalnum(c) iswalnum ((c))
#define scew_isalpha(c) iswalpha ((c))
#define scew_iscntrl(c) iswcntrl ((c))
#define scew_isdigit(c) iswdigit ((c))
#define scew_isxdigit(c) iswxdigit ((c))
#define scew_isgraph(c) iswgraph ((c))
#define scew_islower(c) iswlower ((c))
#define scew_isupper(c) iswupper ((c))
#define scew_isprint(c) iswprint ((c))
#define scew_ispunct(c) iswpunct ((c))
#define scew_isspace(c) iswspace ((c))

#else /* not XML_UNICODE_WCHAR_T */

#include <ctype.h>

#define _XT(str) str

#define scew_printf printf
#define scew_fprintf fprintf
#define scew_vfprintf vfprintf
#define scew_fputs fputs
#define scew_fgets fgets
#define scew_fputc fputc
#define scew_fgetc fgetc

#define scew_strspn(s, accept) strspn (s, accept)
#define scew_strcpy(dest, src) strcpy (dest, src)
#define scew_strcat(dest, src) strcat (dest, src)
#define scew_strncpy(dest, src, n) strncpy (dest, src, (n))
#define scew_strncat(dest, src, n) strncat (dest, src, (n))
#define scew_strlen(s) strlen (s)

#define scew_isalnum(c) isalnum ((unsigned char)(c))
#define scew_isalpha(c) isalpha ((unsigned char)(c))
#define scew_iscntrl(c) iscntrl ((unsigned char)(c))
#define scew_isdigit(c) isdigit ((unsigned char)(c))
#define scew_isxdigit(c) isxdigit ((unsigned char)(c))
#define scew_isgraph(c) isgraph ((unsigned char)(c))
#define scew_islower(c) islower ((unsigned char)(c))
#define scew_isupper(c) isupper ((unsigned char)(c))
#define scew_isprint(c) isprint ((unsigned char)(c))
#define scew_ispunct(c) ispunct ((unsigned char)(c))
#define scew_isspace(c) isspace ((unsigned char)(c))

#endif /* XML_UNICODE_WCHAR_T */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Compares the two given strings @a s1 and @a s2.
 *
 * @return 0 if the two strings are identical or NULL, less than zero
 * if @a s1 is less than @a s2 or greater than zero otherwise.
 */
extern SCEW_API int scew_strcmp (XML_Char const *a, XML_Char const *b);

/**
 * Creates a new copy of the given string.
 *
 * @param src the string to be duplicated (might be NULL).
 *
 * @return the duplicated string, or NULL if the given string is NULL.
 */
extern SCEW_API XML_Char* scew_strdup (XML_Char const *src);

/**
 * Trims off extra spaces from the beginning and end of a string. The
 * trimming is done in place.
 *
 * @param src the string to be trimmed off.
 */
extern SCEW_API void scew_strtrim (XML_Char *src);

extern SCEW_API scew_bool scew_isempty (XML_Char const *src);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STR_H_0212011305 */
