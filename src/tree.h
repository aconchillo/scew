/**
 *
 * @file     tree.h
 * @author   Aleix Conchillo Flaque <aconchillo@acm.org>
 * @date     Thu Feb 20, 2003 23:32
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
 *
 * Tree related functions. SCEW provides functions to create new XML
 * trees.
 */


#ifndef TREE_H_ALEIX0302202332
#define TREE_H_ALEIX0302202332

#include "types.h"

#include <expat.h>


/**
 * Creates a new empty XML tree in memory. You can also have access to
 * the tree created by the parser when reading an XML file.
 *
 * @see parser.h
 */
extern scew_tree*
scew_tree_create();

/**
 * Frees a tree memory structure. Call this function when you are done
 * with your XML. Do not call this function with a
 * <code>scew_tree</code> obtained via a <code>scew_parser</code>,
 * because <code>scew_parser</code> will delete it automatically when
 * freed.
 */
extern void
scew_tree_free(scew_tree* tree);

/**
 * Saves an XML tree in to the specified file. If the file doesn't exist
 * it will create it, and if it exists it will overwrite it.
 */
extern unsigned int
scew_tree_save_file(scew_tree const* tree, char const *file_name);

/**
 * Returns the root element of the given tree.
 *
 * @see element.h
 */
extern scew_element*
scew_tree_root(scew_tree const* tree);

/**
 * Creates the first element (root) of an XML tree with the given name.
 *
 * @see element.h
 */
extern scew_element*
scew_tree_add_root(scew_tree* tree, XML_Char const* name);

#endif /* TREE_H_ALEIX0302202332 */
