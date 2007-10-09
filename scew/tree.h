/**
 *
 * @file     tree.h
 * @brief    SCEW tree type declaration
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Feb 20, 2003 23:32
 *
 * @if copyright
 *
 * Copyright (C) 2003, 2004, 2005, 2006, 2007 Aleix Conchillo Flaque
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
 *
 * Tree related functions. SCEW provides functions to create new XML
 * trees.
 */


#ifndef TREE_H_0302202332
#define TREE_H_0302202332

#include "element.h"

#include <expat.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * This is the type delcaration for XML trees.
 */
typedef struct scew_tree scew_tree;

/**
 * Creates a new empty XML tree in memory. You can also have access to
 * the tree created by the parser when reading an XML file.
 *
 * @see parser.h
 */
extern scew_tree* scew_tree_create (void);

/**
 * Frees a tree memory structure. Call this function when you are done
 * with your XML. You need to call this function with a
 * <code>scew_tree</code> obtained via a <code>scew_parser</code>,
 * as <code>scew_parser_free</code> does not delete it.
 */
extern void scew_tree_free (scew_tree *tree);

/**
 * Returns the root element of the given tree.
 *
 * @see element.h
 */
extern scew_element* scew_tree_root (scew_tree const *tree);

/**
 * Creates the first element (root) of an XML tree with the given name.
 *
 * @see element.h
 */
extern scew_element* scew_tree_set_root (scew_tree *tree,
					 XML_Char const *name);

/**
 *
 *
 * @param tree
 * @param root
 *
 * @return
 */
extern scew_element* scew_tree_set_root_element (scew_tree *tree,
                                                 scew_element *root);

/**
 *
 *
 * @param tree
 *
 * @return
 */
extern XML_Char const* scew_tree_xml_version (scew_tree const *tree);

/**
 *
 *
 * @param tree
 *
 * @return
 */
extern XML_Char const* scew_tree_xml_encoding (scew_tree const *tree);

/**
 *
 *
 * @param tree
 *
 * @return
 */
extern XML_Char const* scew_tree_xml_preamble (scew_tree const *tree);

/**
 *
 *
 * @param tree
 *
 * @return
 */
extern bool scew_tree_xml_standalone (scew_tree const *tree);

/**
 * Sets the XML version in the XML declaration. Currently there is one
 * XML version, so the value is always 1.0. If there were more XML
 * versions, this proerty tells the XML processor which one to use.
 */
extern void scew_tree_set_xml_version (scew_tree *tree,
				       XML_Char const *version);

/**
 * Sets the character encoding used in the XML document. The default is
 * UTF-8.
 */
extern void scew_tree_set_xml_encoding (scew_tree *tree,
					XML_Char const *encoding);

/**
 * Sets the preamble string for the XML document. Typically this
 * will contain a DOCTYPE declaration.
 */
extern void scew_tree_set_xml_preamble (scew_tree *tree,
					XML_Char const *preamble);

/**
 * The standalone property tells the XML processor whether there are
 * any other extra files to load, such as external entities or
 * DTDs. If the XML document can stand on its own, set it to
 * 'yes'. The default SCEW value is 'no', so the XML processor will
 * load what it needs to.
 *
 * @param tree the tree to set the option to.
 * @param standalone true to activate standalone property, false
 * otherwise.
 */
extern void scew_tree_set_xml_standalone (scew_tree *tree, bool standalone);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TREE_H_0302202332 */
