/**
 *
 * @file     str.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 23:32
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

#include "str.h"

#include "mem.h"

#include "xerror.h"

#include <assert.h>

#ifdef XML_UNICODE_WCHAR_T
#include <wchar.h>
#include <wctype.h>
#else
#include <string.h>
#include <ctype.h>
#endif /* XML_UNICODE_WCHAR_T */

XML_Char*
scew_strcpy(XML_Char* dst, XML_Char const* src)
{
    assert(dst != NULL);
    assert(src != NULL);

#ifdef XML_UNICODE_WCHAR_T
    return wcscpy(dst, src);
#else
    return strcpy(dst, src);
#endif /* XML_UNICODE_WCHAR_T */
}

XML_Char*
scew_strcat(XML_Char* dst, XML_Char const* src)
{
    assert(dst != NULL);
    assert(src != NULL);

#ifdef XML_UNICODE_WCHAR_T
    return wcscat(dst, src);
#else
    return strcat(dst, src);
#endif /* XML_UNICODE_WCHAR_T */
}

XML_Char*
scew_strncpy(XML_Char* dst, XML_Char const* src, size_t len)
{
    assert(dst != NULL);
    assert(src != NULL);

#ifdef XML_UNICODE_WCHAR_T
    return wcsncpy(dst, src, len);
#else
    return strncpy(dst, src, len);
#endif /* XML_UNICODE_WCHAR_T */
}

XML_Char*
scew_strncat(XML_Char* dst, XML_Char const* src, size_t len)
{
    assert(dst != NULL);
    assert(src != NULL);

#ifdef XML_UNICODE_WCHAR_T
    return wcsncat(dst, src, len);
#else
    return strncat(dst, src, len);
#endif /* XML_UNICODE_WCHAR_T */
}

XML_Char*
scew_strdup(XML_Char const* src)
{
    unsigned int len = 0;
    XML_Char* out = NULL;

    assert(src != NULL);

    len = scew_strlen(src);
    out = (XML_Char*) calloc(len + 1, sizeof(XML_Char));
    return (XML_Char*) scew_memcpy(out, (XML_Char*) src, len);
}

size_t
scew_strlen(XML_Char const* src)
{
    assert(src != NULL);

#ifdef XML_UNICODE_WCHAR_T
    return wcslen(src);
#else
    return strlen(src);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_strcmp(XML_Char const* s1, XML_Char const* s2)
{
    assert(s1 != NULL);
    assert(s2 != NULL);

#ifdef XML_UNICODE_WCHAR_T
    return wcscmp(s1, s2);
#else
    return strcmp(s1, s2);
#endif /* XML_UNICODE_WCHAR_T */
}

size_t
scew_strspn(XML_Char const* s, XML_Char const* accept)
{
    assert(s != NULL);
    assert(accept != NULL);

#ifdef XML_UNICODE_WCHAR_T
    return wcsspn(s, accept);
#else
    return strspn(s, accept);
#endif /* XML_UNICODE_WCHAR_T */
}

void
scew_strtrim(XML_Char* src)
{
    int start = 0;
    int end = 0;
    int total = 0;

    assert(src != NULL);

    end = scew_strlen(src);

    /* strip trailing whitespace */
    while (end > 0 && scew_isspace(src[end-1]))
    {
        src[--end] = '\0';
    }

    /* strip leading whitespace */
    start = scew_strspn(src, " \n\r\t\v");
    total = end - start;
    scew_memmove(src, &src[start], total);
    src[total] = '\0';
}

int
scew_isalnum(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswalnum(c);
#else
    return isalnum((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_isalpha(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswalpha(c);
#else
    return isalpha((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_iscntrl(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswcntrl(c);
#else
    return iscntrl((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_isdigit(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswdigit(c);
#else
    return isdigit((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_isgraph(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswgraph(c);
#else
    return isgraph((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_islower(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswlower(c);
#else
    return islower((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_isprint(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswprint(c);
#else
    return isprint((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_ispunct(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswpunct(c);
#else
    return ispunct((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_isspace(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswspace(c);
#else
    return isspace((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_isupper(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswupper(c);
#else
    return isupper((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}

int
scew_isxdigit(XML_Char c)
{
#ifdef XML_UNICODE_WCHAR_T
    return iswxdigit(c);
#else
    return isxdigit((unsigned char) c);
#endif /* XML_UNICODE_WCHAR_T */
}
