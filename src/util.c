/**
 *
 * @file     util.c
 * @author   Aleix Conchillo Flaque <aconchillo@acm.org>
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

#include "util.h"

#ifdef XML_UNICODE_WCHAR_T
#include <wchar.h>
#else
#include <string.h>
#endif /* XML_UNICODE_WCHAR_T */

XML_Char*
scew_strcpy(XML_Char* dst, XML_Char const* src)
{
    if ((dst == NULL) || (src == NULL))
    {
        return NULL;
    }
    else
    {
#ifdef XML_UNICODE_WCHAR_T
        return wcscpy(dst, src);
#else
        return strcpy(dst, src);
#endif /* XML_UNICODE_WCHAR_T */
    }
}

XML_Char*
scew_strcat(XML_Char* dst, XML_Char const* src)
{
    if ((dst == NULL) || (src == NULL))
    {
        return NULL;
    }
    else
    {
#ifdef XML_UNICODE_WCHAR_T
        return wcscat(dst, src);
#else
        return strcat(dst, src);
#endif /* XML_UNICODE_WCHAR_T */
    }
}

XML_Char*
scew_strncpy(XML_Char* dst, XML_Char const* src, size_t len)
{
    if ((dst == NULL) || (src == NULL))
    {
        return NULL;
    }
    else
    {
#ifdef XML_UNICODE_WCHAR_T
        return wcsncpy(dst, src, len);
#else
        return strncpy(dst, src, len);
#endif /* XML_UNICODE_WCHAR_T */
    }
}

XML_Char*
scew_strncat(XML_Char* dst, XML_Char const* src, size_t len)
{
    if ((dst == NULL) || (src == NULL))
    {
        return NULL;
    }
    else
    {
#ifdef XML_UNICODE_WCHAR_T
        return wcsncat(dst, src, len);
#else
        return strncat(dst, src, len);
#endif /* XML_UNICODE_WCHAR_T */
    }
}

XML_Char*
scew_strdup(XML_Char const* src)
{
    if (src == NULL)
    {
        return NULL;
    }
    else
    {
#ifdef XML_UNICODE_WCHAR_T
        XML_Char* dst = NULL;
        size_t len = scew_strlen(src) + 1;

        dst = (XML_Char*) malloc(sizeof(XML_Char*) * len);

        return wmemcpy(dst, src, len);
#else
        return strdup(src);
#endif /* XML_UNICODE_WCHAR_T */
    }
}

size_t
scew_strlen(XML_Char const* src)
{
    if (src == NULL)
    {
        return 0;
    }
    else
    {
#ifdef XML_UNICODE_WCHAR_T
        return wcslen(src);
#else
        return strlen(src);
#endif /* XML_UNICODE_WCHAR_T */
    }
}

int
scew_strcmp(XML_Char const* s1, XML_Char const* s2)
{
    if ((s1 == NULL) || (s2 == NULL))
    {
        return 0;
    }
    else
    {
#ifdef XML_UNICODE_WCHAR_T
        return wcscmp(s1, s2);
#else
        return strcmp(s1, s2);
#endif /* XML_UNICODE_WCHAR_T */
    }
}
