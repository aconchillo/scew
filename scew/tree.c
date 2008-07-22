/**
 * @file     tree.c
 * @brief    tree.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Feb 20, 2003 23:45
 *
 * @if copyright
 *
 * Copyright (C) 2003-2008 Aleix Conchillo Flaque
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

#include "tree.h"

#include "xerror.h"

#include "element.h"
#include "str.h"

#include <assert.h>


// Private

struct scew_tree
{
  XML_Char *version;
  XML_Char *encoding;
  XML_Char *preamble;
  bool standalone;
  scew_element *root;
};

static XML_Char const *DEFAULT_XML_VERSION_ = "1.0";
static XML_Char const *DEFAULT_ENCODING_ = "UTF-8";


// Public

scew_tree*
scew_tree_create (void)
{
  scew_tree *tree = calloc (1, sizeof (scew_tree));

  if (tree != NULL)
    {
      tree->version = scew_strdup (DEFAULT_XML_VERSION_);
      tree->encoding = scew_strdup (DEFAULT_ENCODING_);
      tree->standalone = true;
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return tree;
}

void
scew_tree_free (scew_tree *tree)
{
  if (tree != NULL)
    {
      free (tree->version);
      free (tree->encoding);
      free (tree->preamble);
      scew_element_free (tree->root);
      free (tree);
    }
}

scew_element*
scew_tree_root (scew_tree const *tree)
{
  assert (tree != NULL);

  return tree->root;
}

scew_element*
scew_tree_set_root (scew_tree *tree, XML_Char const *name)
{
  assert (tree != NULL);
  assert (name != NULL);

  scew_element *new_root = NULL;

  scew_element *root = scew_element_create (name);

  if (root != NULL)
    {
      new_root = scew_tree_set_root_element (tree, root);
    }
  else
    {
      scew_error_set_last_error_ (scew_error_no_memory);
    }

  return new_root;
}

scew_element*
scew_tree_set_root_element (scew_tree *tree, scew_element *root)
{
  assert (tree != NULL);
  assert (root != NULL);

  tree->root = root;

  return root;
}

XML_Char const*
scew_tree_xml_version (scew_tree const *tree)
{
  assert(tree != NULL);

  return tree->version;
}

XML_Char const*
scew_tree_xml_encoding (scew_tree const *tree)
{
  assert(tree != NULL);

  return tree->encoding;
}

XML_Char const*
scew_tree_xml_preamble (scew_tree const *tree)
{
  assert (tree != NULL);

  return tree->preamble;
}

bool
scew_tree_xml_standalone (scew_tree const *tree)
{
  assert (tree != NULL);

  return tree->standalone;
}

void
scew_tree_set_xml_version(scew_tree *tree, XML_Char const *version)
{
  assert (tree != NULL);
  assert (version != NULL);

  if (tree->version != NULL)
    {
      free (tree->version);
    }
  tree->version = scew_strdup (version);
}

void
scew_tree_set_xml_encoding (scew_tree *tree, XML_Char const *encoding)
{
  assert (tree != NULL);
  assert (encoding != NULL);

  if (tree->encoding != NULL)
    {
      free (tree->encoding);
    }
  tree->encoding = scew_strdup (encoding);
}

void
scew_tree_set_xml_preamble (scew_tree *tree, XML_Char const *preamble)
{
  assert (tree != NULL);
  assert (preamble != NULL);

  if (tree->preamble != NULL)
    {
      free (tree->preamble);
    }
  tree->preamble = scew_strdup (preamble);
}

void
scew_tree_set_xml_standalone (scew_tree *tree, bool standalone)
{
  assert(tree != NULL);

  tree->standalone = standalone;
}
