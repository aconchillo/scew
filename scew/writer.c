/**
 *
 * @file     writer.c
 * @brief    SCEW writer functions
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Sep 11, 2003 00:39
 *
 * @if copyright
 *
 * Copyright (C) 2003, 2004, 2005, 2007 Aleix Conchillo Flaque
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * @endif
 */

#include "writer.h"

#include "str.h"

#include "xerror.h"
#include "xprint.h"

#include <assert.h>

bool
scew_writer_tree_file (scew_tree const *tree, char const *file_name)
{
  assert(tree != NULL);
  assert(file_name != NULL);

  FILE *out = fopen (file_name, "w");

  if (out == NULL)
    {
      set_last_error (scew_error_io);
      return 0;
    }

  scew_writer_tree_fp (tree, out);

  fclose(out);

  return true;
}

bool
scew_writer_tree_fp(scew_tree const* tree, FILE* out)
{
  assert (tree != NULL);
  assert (out != NULL);

  tree_print (tree, out);

  return true;
}
