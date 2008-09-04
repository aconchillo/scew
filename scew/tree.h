/**
 * @file     tree.h
 * @brief    SCEW tree type declaration
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Feb 20, 2003 23:32
 * @ingroup  SCEWTree
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

/**
 * @defgroup SCEWTree Trees
 *
 * Tree related functions. SCEW provides functions to create new XML
 * trees. Trees are SCEW internal XML document representation. A tree
 * contains basic information, such as XML version and enconding, and
 * contains a root element which is the first XML node.
 */

#ifndef TREE_H_0302202332
#define TREE_H_0302202332

#include "element.h"

#include <expat.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum
  {
    scew_tree_standalone_unknown,
    scew_tree_standalone_no,
    scew_tree_standalone_yes
  } scew_tree_standalone;

/**
 * This is the type delcaration for XML trees.
 *
 * @ingroup SCEWTree
 */
typedef struct scew_tree scew_tree;

/**
 * Creates a new empty XML tree in memory. You can also have access to
 * the tree created by the parser when reading an XML file.
 *
 * By default, the XML version is set to 1.0, and the encoding to
 * UTF-8, also a standalone document is considered.
 *
 * @ingroup SCEWTree
 */
extern scew_tree* scew_tree_create (void);

/**
 * Frees a tree memory structure. Call this function when you are done
 * with your XML. You need to call this function with a #scew_tree
 * obtained via a #scew_parser, as #scew_parser_free does not delete
 * it.
 *
 * @param tree the tree to delete.
 *
 * @ingroup SCEWTree
 */
extern void scew_tree_free (scew_tree *tree);

/**
 * Returns the root element of the given @a tree.
 *
 * @pre tree != NULL
 *
 * @ingroup SCEWTree
 */
extern scew_element* scew_tree_root (scew_tree const *tree);

/**
 * Creates the first element (root) of an XML tree with the given
 * name.
 *
 * @pre tree != NULL
 * @pre name != NULL
 *
 * @ingroup SCEWTree
 */
extern scew_element* scew_tree_set_root (scew_tree *tree,
					 XML_Char const *name);

/**
 *
 *
 * @pre tree != NULL
 * @pre root != NULL
 *
 * @param tree
 * @param root
 *
 * @return
 *
 * @ingroup SCEWTree
 */
extern scew_element* scew_tree_set_root_element (scew_tree *tree,
                                                 scew_element *root);

/**
 * Returns the current XML version for the given @a tree. This is the
 * version specified in the "version" attribute in the main XML
 * element.
 *
 * @pre tree != NULL
 *
 * @param tree the tree to return its version for.
 *
 * @return a string representing the XML version.
 *
 * @ingroup SCEWTree
 */
extern XML_Char const* scew_tree_xml_version (scew_tree const *tree);

/**
 * Sets the XML version in the XML declaration. Currently there is one
 * XML version, so the value is always 1.0. If there were more XML
 * versions, this proerty tells the XML processor which one to use.
 *
 * @pre tree != NULL
 * @pre version != NULL
 *
 * @ingroup SCEWTree
 */
extern void scew_tree_set_xml_version (scew_tree *tree,
				       XML_Char const *version);

/**
 *
 *
 * @pre tree != NULL
 *
 * @param tree
 *
 * @return
 *
 * @ingroup SCEWTree
 */
extern XML_Char const* scew_tree_xml_encoding (scew_tree const *tree);

/**
 * Sets the character encoding used in the XML document. The default is
 * UTF-8.
 *
 * @pre tree != NULL
 * @pre encoding != NULL
 *
 * @ingroup SCEWTree
 */
extern void scew_tree_set_xml_encoding (scew_tree *tree,
					XML_Char const *encoding);

/**
 * Returns whether the given @a tree is an standalone document. The
 * standalone property tells the XML processor whether there are any
 * other extra files to load, such as external entities or DTDs.
 *
 * @pre tree != NULL
 *
 * @param tree the tree to check its standalone property for.
 *
 * @return true if the given tree is standalone, false otherwise.
 *
 * @ingroup SCEWTree
 */
extern scew_tree_standalone scew_tree_xml_standalone (scew_tree const *tree);

/**
 * The standalone property tells the XML processor whether there are
 * any other extra files to load, such as external entities or
 * DTDs. If the XML document can stand on its own, set it to
 * 'yes'.
 *
 * @pre tree != NULL
 *
 * @param tree the tree to set the option to.
 * @param standalone true to activate standalone property, false
 * otherwise.
 *
 * @ingroup SCEWTree
 */
extern void scew_tree_set_xml_standalone (scew_tree *tree,
                                          scew_tree_standalone standalone);

/**
 *
 *
 * @pre tree != NULL
 *
 * @param tree
 *
 * @return
 *
 * @ingroup SCEWTree
 */
extern XML_Char const* scew_tree_xml_preamble (scew_tree const *tree);

/**
 * Sets the preamble string for the XML document. Typically this
 * will contain a DOCTYPE declaration.
 *
 * @pre tree != NULL
 * @pre preamble != NULL
 *
 * @ingroup SCEWTree
 */
extern void scew_tree_set_xml_preamble (scew_tree *tree,
					XML_Char const *preamble);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // TREE_H_0302202332
