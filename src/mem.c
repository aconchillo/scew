/**
 *
 * @file     mem.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Wed Jul 09, 2003 23:32
 * @brief    SCEW memory functions
 *
 * $Id$
 *
 * @if copyright
 *
 * Copyright (C) 2003 Aleix Conchillo Flaque
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

#include "mem.h"

#ifdef XML_UNICODE_WCHAR_T
#include <wchar.h>
#else
#include <string.h>
#endif /* XML_UNICODE_WCHAR_T */

void*
scew_memcpy(XML_Char* dst, XML_Char* src, size_t n)
{
#ifdef XML_UNICODE_WCHAR_T
    return wmemcpy(dst, src, n);
#else
    return memcpy(dst, src, n);
#endif /* XML_UNICODE_WCHAR_T */
}

void*
scew_memmove(XML_Char* dst, XML_Char* src, size_t n)
{
#ifdef XML_UNICODE_WCHAR_T
    return wmemmove(dst, src, n);
#else
    return memmove(dst, src, n);
#endif /* XML_UNICODE_WCHAR_T */
}
