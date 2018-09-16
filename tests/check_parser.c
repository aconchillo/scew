/**
 * @file     check_parser.c
 * @brief    Unit testing for SCEW parser
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Fri Oct 30, 2009 07:45
 *
 * @if copyright
 *
 * Copyright (C) 2009-2018 Aleix Conchillo Flaque
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

#include <scew/error.h>
#include <scew/parser.h>
#include <scew/reader_buffer.h>

#include <check.h>


/* Unit tests */

static XML_Char const *TEST_XML =
  _XT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n"
      "<test>\n"
      "   <element>element contents</element>\n"
      "   <element attribute=\"value\"/>\n"
      "   <element attribute1=\"value1\" attribute2=\"value2\"/>\n"
      "   <element>\n"
      "      <subelement attribute=\"value\"/>\n"
      "      <subelement attribute1=\"value1\" attribute2=\"value2\">\n"
      "         <subsubelement>With accents: à é è í ó ú</subsubelement>\n"
      "      </subelement>\n"
      "   </element>\n"
      "</test>\n");

static XML_Char const *TEST_HOOKS_XML =
  _XT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n"
      "<test>\n"
      "   <element>element contents</element>\n"
      "   <element attribute=\"value\"/>\n"
      "   <element attribute1=\"value1\" attribute2=\"value2\"/>\n"
      "</test>\n");

static XML_Char const *TEST_WHITE_SPACE_XML =
  _XT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n"
      "<test>  <element> element contents </element>  </test>\n");

static XML_Char const *TEST_STREAM_XML =
  _XT("\n"
      "   <?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n"
      "<test>\n"
      "   <element>element contents</element>\n"
      "   <element attribute=\"value\"/>\n"
      "   <element attribute1=\"value1\" attribute2=\"value2\"/>\n"
      "</test>\n"
      "\n"
      "   <?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\n"
      "<test>\n"
      "   <element attribute=\"value\"/>\n"
      "   <element attribute1=\"value1\" attribute2=\"value2\"/>\n"
      "</test>\n");

static XML_Char const *TEST_STREAM_A_1_XML =
  _XT("<test>\n"
      "   <element>element contents</element>\n"
      "   <element");

static XML_Char const *TEST_STREAM_A_2_XML =
  _XT("\n"
      " attribute1=\"value1\" attribute2=\"value2\"/>\n"
      "</test>\n");

static XML_Char const *TEST_STREAM_B_1_XML =
  _XT("<element");

static XML_Char const *TEST_STREAM_B_2_XML =
  _XT(" attribute1=\"value1\" attribute2=\"value2\"/>\n");

static XML_Char const *TEST_INVALID_XML =
  _XT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n"
      "<test>\n"
      "   <element>element contents</element>\n"
      "   <element attribute=\"value\"/>\n"
      "   <element attribute1=\"value1\" attribute2=\"value2\"/>\n"
      "   <element>\n"
      "      <subelement attribute=\"value\"/>\n"
      "      <subelement attribute1=\"value1\" attribute2=\"value2\">\n"
      "   </element>\n"
      "</test>\n");

/* Allocation */

START_TEST (test_alloc)
{
  scew_parser *parser = scew_parser_create ();
  scew_parser *ns_parser = scew_parser_namespace_create (0);

  CHECK_PTR (parser, "Unable to create parser");
  CHECK_PTR (ns_parser, "Unable to create namespace parser");

  scew_parser_free (parser);
  scew_parser_free (ns_parser);
}
END_TEST

/* Load */

START_TEST (test_load)
{
  static unsigned int const N_CHILDREN = 4;
  static XML_Char const *CHILD_NAME = _XT("element");

  scew_parser *parser = scew_parser_create ();

  scew_reader *reader = scew_reader_buffer_create (TEST_XML,
                                                   scew_strlen (TEST_XML));

  scew_tree *tree = scew_parser_load (parser, reader);

  CHECK_PTR (tree, "Unable to parse test XML");

  CHECK_STR (scew_tree_xml_encoding (tree), _XT("UTF-8"),
             "Encoding does not match");
  CHECK_STR (scew_tree_xml_version (tree), _XT("1.0"),
             "Encoding does not match");

  scew_element *root = scew_tree_root (tree);

  CHECK_U_INT (scew_element_count (root), N_CHILDREN,
               "Number of children do not match");

  for (unsigned int i = 0; i < N_CHILDREN; ++i)
    {
      scew_element *child = scew_element_by_index (root, i);
      CHECK_STR (scew_element_name (child), CHILD_NAME,
                 "Child name do not match");
    }

  scew_tree_free (tree);
  scew_reader_free (reader);
  scew_parser_free (parser);
}
END_TEST


/* Load hooks */

static scew_bool
element_hook_ (scew_parser *parser, void *element, void *user_data)
{
  static XML_Char const *ROOT_NAME = _XT("test");
  static XML_Char const *CHILD_NAME = _XT("element");

  CHECK_STR (scew_element_name (element),
             (scew_element_parent (element) == NULL) ? ROOT_NAME : CHILD_NAME,
             "Child name do not match");

  return SCEW_TRUE;
}

static scew_bool
tree_hook_ (scew_parser *parser, void *tree, void *user_data)
{
  static unsigned int const N_CHILDREN = 3;

  CHECK_STR (scew_tree_xml_encoding (tree), _XT("UTF-8"),
             "Encoding does not match");
  CHECK_STR (scew_tree_xml_version (tree), _XT("1.0"),
             "Encoding does not match");

  scew_element *root = scew_tree_root (tree);

  CHECK_U_INT (scew_element_count (root), N_CHILDREN,
               "Number of children do not match");

  return SCEW_TRUE;
}

START_TEST (test_load_hooks)
{
  scew_parser *parser = scew_parser_create ();

  scew_reader *reader =
    scew_reader_buffer_create (TEST_HOOKS_XML, scew_strlen (TEST_HOOKS_XML));

  scew_parser_set_element_hook (parser, element_hook_, NULL);
  scew_parser_set_tree_hook (parser, tree_hook_, NULL);

  scew_tree *tree = scew_parser_load (parser, reader);

  scew_tree_free (tree);
  scew_reader_free (reader);
  scew_parser_free (parser);
}
END_TEST


/* Load stream */

static scew_bool
tree_stream_hook_ (scew_parser *parser, void *tree, void *user_data)
{
  static unsigned int const N_CHILDREN_0 = 3;
  static unsigned int const N_CHILDREN_1 = 2;

  static unsigned int counter = 0;

  CHECK_STR (scew_tree_xml_encoding (tree),
             (0 == counter) ? _XT("UTF-8") : _XT("ISO-8859-1"),
             "Encoding does not match");

  scew_element *root = scew_tree_root (tree);

  CHECK_U_INT (scew_element_count (root),
               (0 == counter) ? N_CHILDREN_0 : N_CHILDREN_1,
               "Number of children do not match");

  /* We can safely free the XML tree when loading streams. */
  scew_tree_free (tree);

  counter += 1;

  return SCEW_TRUE;
}

START_TEST (test_load_stream)
{
  scew_parser *parser = scew_parser_create ();

  scew_reader *reader =
    scew_reader_buffer_create (TEST_STREAM_XML, scew_strlen (TEST_STREAM_XML));

  scew_parser_set_element_hook (parser, element_hook_, NULL);
  scew_parser_set_tree_hook (parser, tree_stream_hook_, NULL);

  CHECK_BOOL (scew_parser_load_stream (parser, reader), SCEW_TRUE,
              "Unable to parse stream");

  scew_reader_free (reader);
  scew_parser_free (parser);
}
END_TEST

static scew_bool
tree_chunked_stream_a_hook_ (scew_parser *parser, void *tree, void *user_data)
{
  static unsigned int const N_CHILDREN = 2;

  scew_element *root = scew_tree_root (tree);

  CHECK_U_INT (scew_element_count (root), N_CHILDREN,
               "Number of children do not match");

  return SCEW_TRUE;
}

START_TEST (test_load_chunked_stream_a)
{
  scew_parser *parser = scew_parser_create ();

  scew_reader *reader_1 =
    scew_reader_buffer_create (TEST_STREAM_A_1_XML,
                               scew_strlen (TEST_STREAM_A_1_XML));

  scew_reader *reader_2 =
    scew_reader_buffer_create (TEST_STREAM_A_2_XML,
                               scew_strlen (TEST_STREAM_A_2_XML));

  scew_parser_set_element_hook (parser, element_hook_, NULL);
  scew_parser_set_tree_hook (parser, tree_chunked_stream_a_hook_, NULL);

  CHECK_BOOL (scew_parser_load_stream (parser, reader_1), SCEW_TRUE,
              "Unable to parse first stream");

  CHECK_BOOL (scew_parser_load_stream (parser, reader_2), SCEW_TRUE,
              "Unable to parse second stream");

  scew_reader_free (reader_1);
  scew_reader_free (reader_2);
  scew_parser_free (parser);
}
END_TEST

static scew_bool
tree_chunked_stream_b_hook_ (scew_parser *parser, void *tree, void *user_data)
{
  static unsigned int const N_CHILDREN = 0;
  static XML_Char const *ROOT_NAME = _XT("element");

  scew_element *root = scew_tree_root (tree);

  CHECK_U_INT (scew_element_count (root), N_CHILDREN,
               "Number of children do not match");

  CHECK_STR (scew_element_name (root), ROOT_NAME, "Child name do not match");

  return SCEW_TRUE;
}

START_TEST (test_load_chunked_stream_b)
{
  scew_parser *parser = scew_parser_create ();

  scew_reader *reader_1 =
    scew_reader_buffer_create (TEST_STREAM_B_1_XML,
                               scew_strlen (TEST_STREAM_B_1_XML));

  scew_reader *reader_2 =
    scew_reader_buffer_create (TEST_STREAM_B_2_XML,
                               scew_strlen (TEST_STREAM_B_2_XML));

  scew_parser_set_tree_hook (parser, tree_chunked_stream_b_hook_, NULL);

  CHECK_BOOL (scew_parser_load_stream (parser, reader_1), SCEW_TRUE,
              "Unable to parse first stream");

  CHECK_BOOL (scew_parser_load_stream (parser, reader_2), SCEW_TRUE,
              "Unable to parse second stream");

  scew_reader_free (reader_1);
  scew_reader_free (reader_2);
  scew_parser_free (parser);
}
END_TEST


/* Load invalid */

START_TEST (test_load_invalid)
{
  static int const ERROR_LINE = 10;

  scew_parser *parser = scew_parser_create ();

  scew_reader *reader =
    scew_reader_buffer_create (TEST_INVALID_XML,
                               scew_strlen (TEST_INVALID_XML));

  scew_tree *tree = scew_parser_load (parser, reader);

  CHECK_NULL_PTR (tree, "Invalid tree should not be parsed");

  CHECK_U_INT (scew_error_code (), scew_error_expat,
               "Internal Expat parser should occur");

  /* Expat errors */
  CHECK_U_INT (scew_error_expat_code (parser), XML_ERROR_TAG_MISMATCH,
               "Wrong internal Expat error code");
  CHECK_U_INT (scew_error_expat_line (parser), ERROR_LINE,
               "Wrong line number for missing element closing tag");

  scew_reader_free (reader);
  scew_parser_free (parser);
}
END_TEST


/* White spaces */

START_TEST (test_white_spaces)
{
  scew_parser *parser = scew_parser_create ();

  scew_reader *reader =
    scew_reader_buffer_create (TEST_WHITE_SPACE_XML, scew_strlen (TEST_WHITE_SPACE_XML));

  scew_tree *tree = scew_parser_load (parser, reader);

  scew_element *root = scew_tree_root (tree);
  CHECK_NULL_PTR (scew_element_contents (root),
                  "Root element shouldn't have any white spaces");

  scew_element *element = scew_element_by_name (root, "element");
  CHECK_STR (scew_element_contents (element), " element contents ",
             "Element contents should preserve white spaces");

  scew_tree_free (tree);
  scew_reader_free (reader);
  scew_parser_free (parser);
}
END_TEST

START_TEST (test_ignore_white_spaces)
{
  scew_parser *parser = scew_parser_create ();
  scew_parser_ignore_whitespaces (parser, SCEW_FALSE);

  scew_reader *reader =
    scew_reader_buffer_create (TEST_WHITE_SPACE_XML, scew_strlen (TEST_WHITE_SPACE_XML));

  scew_tree *tree = scew_parser_load (parser, reader);

  scew_element *root = scew_tree_root (tree);
  CHECK_PTR (scew_element_contents (root),
             "Root element should preserve white spaces");

  scew_element *element = scew_element_by_name (root, "element");
  CHECK_STR (scew_element_contents (element), " element contents ",
                  "Element contents should preserve white spaces");

  scew_tree_free (tree);
  scew_reader_free (reader);
  scew_parser_free (parser);
}
END_TEST


/* Suite */

static Suite*
parser_suite (void)
{
  Suite *s = suite_create ("SCEW parser");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_alloc);
  tcase_add_test (tc_core, test_load);
  tcase_add_test (tc_core, test_load_hooks);
  tcase_add_test (tc_core, test_load_stream);
  tcase_add_test (tc_core, test_load_chunked_stream_a);
  tcase_add_test (tc_core, test_load_chunked_stream_b);
  tcase_add_test (tc_core, test_load_invalid);
  tcase_add_test (tc_core, test_white_spaces);
  tcase_add_test (tc_core, test_ignore_white_spaces);
  suite_add_tcase (s, tc_core);

  return s;
}

void
run_tests (SRunner *sr)
{
  srunner_add_suite (sr, parser_suite ());
}
