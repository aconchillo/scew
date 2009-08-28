/**
 * @file     check_reader_buffer.c
 * @brief    Unit testing for SCEW buffer reader
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Fri Aug 28, 2009 19:38
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

#include <scew/reader_buffer.h>

#include <check.h>


/* Unit tests */

/* Allocation */

START_TEST (test_alloc)
{
  static XML_Char const *BUFFER = "This is a buffer for the reader";

  scew_reader *reader = scew_reader_buffer_create (BUFFER,
                                                   scew_strlen (BUFFER));

  CHECK_PTR (reader, "Unable to create buffer reader");

  scew_reader_free (reader);
}
END_TEST


/* Suite */

static Suite*
reader_buffer_suite (void)
{
  Suite *s = suite_create ("SCEW buffer reader");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_alloc);
  suite_add_tcase (s, tc_core);

  return s;
}

void
run_tests (SRunner *sr)
{
  srunner_add_suite (sr, reader_buffer_suite ());
}
