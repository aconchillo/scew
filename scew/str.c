/**
 * @file     str.c
 * @brief    str.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 23:32
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

#include "str.h"

#include "xerror.h"
#include "str.h"

#include <assert.h>

int
scew_strcmp (XML_Char const *s1, XML_Char const *s2)
{
  int result = ((s1 == NULL) && (s2 == NULL)) ? 0 : 1;

  if (result != 0)
    {
      /* We don't know if s1 or s2 are NULL. */
      result = 0;

      if (s1 == NULL)
        {
          /* s1 is lesser than s2. */
          result = -1;
        }
      if (s2 == NULL)
        {
          /* s1 is greater than s2. */
          result = 1;
        }

      /* s1 and s2 are *not* NULL, so we need to compare them. */
      if (result == 0)
        {
#ifdef XML_UNICODE_WCHAR_T
          result = wcscmp (s1, s2);
#else
          result = strcmp (s1, s2);
#endif
        }
    }

  return result;
}

XML_Char*
scew_strdup (XML_Char const *src)
{
  XML_Char *out = NULL;

  if (src != NULL)
    {
      size_t len = scew_strlen (src);
      out = calloc (len + 1, sizeof (XML_Char));
      scew_strcpy (out, src);
    }

  return out;
}

void
scew_strtrim (XML_Char *src)
{
  size_t start = 0;
  size_t end = 0;
  size_t total = 0;

  assert (src != NULL);

  end = scew_strlen (src);

  /* Strip trailing whitespace. */
  while (end > 0 && scew_isspace (src[end - 1]))
    {
      src[--end] = _XT('\0');
    }

  /* Strip leading whitespace. */
  start = scew_strspn (src, _XT(" \n\r\t\v"));
  total = end - start;
  scew_memmove (src, &src[start], total);
  src[total] = _XT('\0');
}

scew_bool
scew_isempty (XML_Char const *src)
{
  scew_bool empty = SCEW_TRUE;
  XML_Char *p = (XML_Char *) src;

  assert (src != NULL);

  while (empty && (*p != _XT('\0')))
    {
      empty = (scew_isspace (*p) != 0);
      p += 1;
    }

  return empty;
}
