/**
 *
 * @file     tree.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Feb 20, 2003 23:45
 * @brief    SCEW tree type declaration
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

#include "tree.h"

#include "xtree.h"

//#include "element.h"

#include <string.h>


scew_tree*
scew_tree_create()
{
    scew_tree* tree = (scew_tree*) malloc(sizeof(scew_tree));

    if (tree != NULL)
    {
        bzero(tree, sizeof(tree));
    }

    return tree;
}

void
scew_tree_free(scew_tree* tree)
{
    scew_element_free(tree->root);
    free(tree);
}

scew_element*
scew_tree_root(scew_tree const* tree)
{
    return tree->root;
}

scew_element*
scew_tree_add_root(scew_tree* tree, XML_Char const* name)
{
    scew_element* root = NULL;

    if (tree != NULL)
    {
        root = scew_element_create(name);
        tree->root = root;
    }

    return root;
}
