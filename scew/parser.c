/**
 * @file     parser.c
 * @brief    parser.h implementation
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Mon Nov 25, 2002 00:58
 *
 * @if copyright
 *
 * Copyright (C) 2002-2008 Aleix Conchillo Flaque
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

#include "parser.h"

#include "xparser.h"
#include "xerror.h"

#include "tree.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>



/* Public */

scew_parser*
scew_parser_create (void)
{
  scew_parser *parser = calloc (1, sizeof (scew_parser));

  if (parser == NULL)
    {
      scew_error_set_last_error_ (scew_error_no_memory);
      return NULL;
    }

  if (!scew_parser_expat_init_ (parser))
    {
      scew_parser_free (parser);
      return NULL;
    }

  /* Ignore white spaces by default. */
  parser->ignore_whitespaces = SCEW_TRUE;

  /* No load hook by default. */
  parser->load_hook = NULL;

  return parser;
}

void
scew_parser_free (scew_parser *parser)
{
  if (parser != NULL)
    {
      if (parser->parser)
        {
          XML_ParserFree (parser->parser);
        }
      free (parser);
    }
}

scew_bool
scew_parser_load (scew_parser *parser, scew_reader *reader)
{
  scew_bool done = SCEW_FALSE;
  scew_bool result = SCEW_TRUE;

  assert (parser != NULL);
  assert (in != NULL);

  while (!done && result)
    {
      enum { MAX_BUFFER = 1024 };
      char buffer[MAX_BUFFER];

      /* Read files in small chunks. */
      int len = scew_reader_read (reader, buffer, MAX_BUFFER);
      if (scew_reader_error (reader))
        {
	  scew_error_set_last_error_ (scew_error_io);
	  result = SCEW_FALSE;
        }
      else
        {
          /* Parse read data. */
          done = scew_reader_eor (reader);
          if (done && !XML_Parse (parser->parser, buffer, len, done))
            {
              scew_error_set_last_error_ (scew_error_expat);
              result = SCEW_FALSE;
            }
        }
    }

  if (!result)
    {
      scew_parser_stack_free_ (parser);
    }

  return result;
}

/* scew_bool */
/* scew_parser_load_stream (scew_parser *parser, */
/*                          char const *buffer, */
/* 			 unsigned int size, */
/*                          scew_bool is_final) */
/* { */
/*   scew_bool result = SCEW_TRUE; */
/*   enum XML_Status status = XML_STATUS_OK; */

/*   assert (parser != NULL); */
/*   assert (buffer != NULL); */
/*   assert (size > 0); */

/*   parser->is_stream = SCEW_TRUE; */

/*   status = XML_Parse (parser->parser, buffer, size, is_final); */

/*   result = (XML_STATUS_OK == status); */

/*   printf ("\n----------\n%c - status: %d - is_final: %d - error: %s\n", */
/*           buffer[0], status, is_final, XML_ErrorString (XML_GetErrorCode (parser->parser))); */
/*   if (result) */
/*     { */
/*       XML_ParsingStatus parsing_status; */
/*       XML_GetParsingStatus(parser->parser, &parsing_status); */

/*       if (XML_FINISHED == parsing_status.parsing) */
/*         { */
/*           printf ("document finished!\n"); */
/*           XML_ParserReset (parser->parser, NULL); */
/*           scew_parser_expat_install_handlers_ (parser); */
/*         } */
/*     } */

/*   return result; */
/* } */

void
scew_parser_set_load_hook (scew_parser *parser, scew_parser_load_hook hook)
{
  assert (parser != NULL);

  parser->load_hook = hook;
}

scew_tree*
scew_parser_tree (scew_parser const *parser)
{
  assert (parser != NULL);

  return parser->tree;
}

XML_Parser
scew_parser_expat (scew_parser *parser)
{
  assert (parser != NULL);

  return parser->parser;
}

void
scew_parser_ignore_whitespaces (scew_parser *parser, scew_bool ignore)
{
  assert (parser != NULL);

  parser->ignore_whitespaces = ignore;
}
