/**
 * @file     check_tree.c
 * @brief    Unit testing for SCEW trees
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Thu Aug 27, 2009 23:56
 *
 * @if copyright
 *
 * Copyright (C) 2009 Aleix Conchillo Flaque
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

#include "test.h"

#include <scew/tree.h>

#include <check.h>


/* Unit tests */

/* Allocation */

START_TEST (test_alloc)
{
  scew_tree *tree = scew_tree_create ();

  CHECK_PTR (tree, "Unable to create tree");

  scew_tree_free (tree);
}
END_TEST

/* Tree properties (version, encoding...) */

START_TEST (test_properties)
{
  static XML_Char const *DEF_VERSION = "1.0";
  static XML_Char const *DEF_ENCODING = "UTF-8";
  static scew_tree_standalone DEF_STANDALONE = scew_tree_standalone_unknown;

  static XML_Char const *NEW_VERSION = "1.1";
  static XML_Char const *NEW_ENCODING = "UTF-16";
  static scew_tree_standalone NEW_STANDALONE = scew_tree_standalone_yes;

  scew_tree *tree = scew_tree_create ();

  CHECK_PTR (tree, "Unable to create tree");

  /* Check defaults */
  CHECK_STR (scew_tree_xml_version (tree), DEF_VERSION,
             "Wrong default XML version");
  CHECK_STR (scew_tree_xml_encoding (tree), DEF_ENCODING,
             "Wrong default XML encoding");
  CHECK_U_INT (scew_tree_xml_standalone (tree), DEF_STANDALONE,
               "Wrong default XML standalone attribute");

  /* Set new properties and check again */
  scew_tree_set_xml_version (tree, NEW_VERSION);
  scew_tree_set_xml_encoding (tree, NEW_ENCODING);
  scew_tree_set_xml_standalone (tree, NEW_STANDALONE);
  CHECK_STR (scew_tree_xml_version (tree), NEW_VERSION,
             "Wrong new XML version");
  CHECK_STR (scew_tree_xml_encoding (tree), NEW_ENCODING,
             "Wrong new XML encoding");
  CHECK_U_INT (scew_tree_xml_standalone (tree), NEW_STANDALONE,
               "Wrong new XML standalone attribute");

  scew_tree_free (tree);
}
END_TEST

/* Tree contents */

START_TEST (test_contents)
{
  static XML_Char const *NAME = "root";
  static XML_Char const *PREAMBLE = "Completly wrong dummy preamble";

  scew_tree *tree = scew_tree_create ();

  CHECK_PTR (tree, "Unable to create tree");

  CHECK_NULL_PTR (scew_tree_root (tree), "No root tree added yet");

  /* Add root element by name */
  scew_element *root = scew_tree_set_root (tree, NAME);
  CHECK_BOOL ((scew_tree_root (tree) == root), SCEW_TRUE,
              "Returned root element does not match tree root");
  scew_element_free (root);

  /* Create element and add root */
  root = scew_element_create (NAME);
  scew_tree_set_root_element (tree, root);
  CHECK_BOOL ((scew_tree_root (tree) == root), SCEW_TRUE,
              "Returned root element does not match tree root");

  /* Set XML preamble */
  CHECK_NULL_PTR (scew_tree_xml_preamble (tree),
                  "Default preamble should be NULL");
  scew_tree_set_xml_preamble (tree, PREAMBLE);
  CHECK_STR (scew_tree_xml_preamble (tree), PREAMBLE,
             "Set XML preamble do not match");

  scew_tree_free (tree);
}
END_TEST


/* Suite */

static Suite*
tree_suite (void)
{
  Suite *s = suite_create ("SCEW trees");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_alloc);
  tcase_add_test (tc_core, test_properties);
  tcase_add_test (tc_core, test_contents);
  suite_add_tcase (s, tc_core);

  return s;
}

void
run_tests (SRunner *sr)
{
  srunner_add_suite (sr, tree_suite ());
}
