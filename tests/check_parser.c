/**
 * @file     check_parser.c
 * @brief    Unit testing for SCEW parser
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Fri Oct 30, 2009 07:45
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

#include <scew/parser.h>

#include <check.h>


/* Unit tests */

/* Allocation */

START_TEST (test_alloc)
{
  scew_parser *parser = scew_parser_create ();

  CHECK_PTR (parser, "Unable to create parser");

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
  suite_add_tcase (s, tc_core);

  return s;
}

void
run_tests (SRunner *sr)
{
  srunner_add_suite (sr, parser_suite ());
}
