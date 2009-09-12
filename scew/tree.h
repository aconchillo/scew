/**
 * @file     tree.h
 * @brief    SCEW tree type declaration
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Feb 20, 2003 23:32
 * @ingroup  SCEWTree, SCEWTreeAlloc, SCEWTreeProp, SCEWTreeContent
 *
 * @if copyright
 *
 * Copyright (C) 2003-2009 Aleix Conchillo Flaque
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

#include "export.h"

#include "element.h"

#include <expat.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * The standalone attribute in an XML declaration defines whether the
 * XML document is self consistent or not, that is, whether it needs
 * to load any extra files.
 *
 * @ingroup SCEWTreeProp
 */
typedef enum
  {
    scew_tree_standalone_unknown, /**< Standalone attribute not defined. */
    scew_tree_standalone_no,    /**< Extra files are necessary. */
    scew_tree_standalone_yes    /**< Document stands on its own. */
  } scew_tree_standalone;

/**
 * This is the type delcaration for XML trees.
 *
 * @ingroup SCEWTree
 */
typedef struct scew_tree scew_tree;


/**
 * @defgroup SCEWTreeAlloc Allocation
 * Allocate and free XML trees.
 * @ingroup SCEWTree
 */

/**
 * Creates a new empty XML tree in memory. You can also have access to
 * the tree created by the parser when reading an XML file.
 *
 * By default, the XML version is set to 1.0, and the encoding to
 * UTF-8, also a standalone document is considered.
 *
 * @ingroup SCEWTreeAlloc
 */
extern SCEW_API scew_tree* scew_tree_create (void);

/**
 * Makes a deep copy of the given @a tree. It also copies XML
 * encoding, version and standalone attributes.
 *
 * @param tree the tree to be duplicated.
 *
 * @return a new tree, or NULL if the copy failed.
 *
 * @ingroup SCEWTreeAlloc
 */
extern SCEW_API scew_tree* scew_tree_copy (scew_tree const *tree);

/**
 * Frees a tree memory structure. Call this function when you are done
 * with your XML document. This will also free the root element
 * recursively.
 *
 * @param tree the tree to delete.
 *
 * @ingroup SCEWTreeAlloc
 */
extern SCEW_API void scew_tree_free (scew_tree *tree);


/**
 * @defgroup SCEWTreeCompare Comparison
 * Tree comparison routines.
 * @ingroup SCEWTree
 */

/**
 * Performs a deep comparison of the given tree. That is, it compares
 * that both trees have the same XML attributes and root element.
 *
 * @pre a != NULL
 * @pre b != NULL
 *
 * @return true if trees are equal, false otherwise.
 *
 * @ingroup SCEWTreeCompare
 */
extern SCEW_API scew_bool scew_tree_compare (scew_tree const *a,
                                             scew_tree const *b);


/**
 * @defgroup SCEWTreeProp Properties
 * Handle XML trees properties.
 * @ingroup SCEWTree
 */

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
 * @ingroup SCEWTreeProp
 */
extern SCEW_API XML_Char const*
scew_tree_xml_version (scew_tree const *tree);

/**
 * Sets the XML version in the XML declaration. Currently there is one
 * XML version, so the value is always 1.0. If there were more XML
 * versions, this proerty tells the XML processor which one to use.
 *
 * @pre tree != NULL
 * @pre version != NULL
 *
 * @ingroup SCEWTreeProp
 */
extern SCEW_API void scew_tree_set_xml_version (scew_tree *tree,
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
 * @ingroup SCEWTreeProp
 */
extern SCEW_API XML_Char const* scew_tree_xml_encoding (scew_tree const *tree);

/**
 * Sets the character encoding used in the XML document. The default is
 * UTF-8.
 *
 * @pre tree != NULL
 * @pre encoding != NULL
 *
 * @ingroup SCEWTreeProp
 */
extern SCEW_API void scew_tree_set_xml_encoding (scew_tree *tree,
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
 * @ingroup SCEWTreeProp
 */
extern SCEW_API scew_tree_standalone
scew_tree_xml_standalone (scew_tree const *tree);

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
 * @ingroup SCEWTreeProp
 */
extern SCEW_API void
scew_tree_set_xml_standalone (scew_tree *tree,
                              scew_tree_standalone standalone);


/**
 * @defgroup SCEWTreeContent Contents
 * Accessors for XML root elements and preambles.
 * @ingroup SCEWTree
 */

/**
 * Returns the root element of the given @a tree.
 *
 * @pre tree != NULL
 *
 * @return the tree's root element, or NULL if the tree does not have
 * a root element yet.
 *
 * @ingroup SCEWTreeContent
 */
extern SCEW_API scew_element* scew_tree_root (scew_tree const *tree);

/**
 * Creates the root element of an XML @a tree with the given @a
 * name. Note that if the tree already had a root element, it will be
 * overwritten, possibly causing a memory leak, as the old root
 * element is *not* automatically freed. So, if you plan to set a new
 * root element, remember to free the old one first.
 *
 * @pre tree != NULL
 * @pre name != NULL
 *
 * @return the tree's root element, or NULL if the element could not
 * be created.
 *
 * @ingroup SCEWTreeContent
 */
extern SCEW_API scew_element* scew_tree_set_root (scew_tree *tree,
                                                  XML_Char const *name);

/**
 * Sets the root element of an XML @a tree with the given @a
 * root. Note that if the tree already had a root element, it will be
 * overwritten, possibly causing a memory leak, as the old root
 * element is *not* automatically freed. So, if you plan to set a new
 * root element, remember to free the old one first.
 *
 * @pre tree != NULL
 * @pre root != NULL
 *
 * @return the tree's root element, or NULL if the element could not
 * be created.
 *
 * @ingroup SCEWTreeContent
 */
extern SCEW_API scew_element* scew_tree_set_root_element (scew_tree *tree,
                                                          scew_element *root);
/**
 *
 *
 * @pre tree != NULL
 *
 * @param tree
 *
 * @return
 *
 * @ingroup SCEWTreeContent
 */
extern SCEW_API XML_Char const* scew_tree_xml_preamble (scew_tree const *tree);

/**
 * Sets the preamble string for the XML document. Typically this
 * will contain a DOCTYPE declaration.
 *
 * @pre tree != NULL
 * @pre preamble != NULL
 *
 * @ingroup SCEWTreeContent
 */
extern SCEW_API void scew_tree_set_xml_preamble (scew_tree *tree,
                                                 XML_Char const *preamble);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TREE_H_0302202332 */
