/**
 *
 * @file     error.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon May 05, 2003 10:35
 * @brief    SCEW error handling
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

#include "error.h"

#include "xerror.h"
#include "xparser.h"

scew_error
scew_error_code()
{
    return get_last_error();
}

XML_Char const*
scew_error_string(scew_error code)
{
    return "";
}

enum XML_Error
scew_error_expat_code(scew_parser* parser)
{
    return XML_GetErrorCode(parser->parser);
}

XML_Char const*
scew_error_expat_string(enum XML_Error code)
{
    return XML_ErrorString(code);
}

