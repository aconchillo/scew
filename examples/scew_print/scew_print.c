/**
 *
 * @file     scew_print.c
 * @author   Aleix Conchillo Flaque <aconchillo@acm.org>
 * @date     Wed Dec 04, 2002 01:11
 * @brief    SCEW usage example
 *
 * $Id$
 *
 * @if copyright
 *
 * Copyright (C) 2002 Aleix Conchillo Flaque
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
 * This example shows the usage of the API provided by SCEW. It will
 * print an XML file given as the first program parameter.
 */

#include <scew/scew.h>

/* indentation size (in whitespaces) */
static int const indent_size = 4;

void
print_justify(unsigned int indent)
{
    int i = 0;

    for (i = 0; i < indent * indent_size; i++)
    {
        printf(" ");
    }
}

void
print_attributes(scew_element const* element)
{
    int i = 0;
    scew_attribute const* attribute = NULL;

    if (element != NULL)
    {
        /**
         * Iterates through the element's attribute list, printing the
         * pair name-value.
         */
        for (i = 0; i < scew_get_attribute_count(element); i++)
        {
            attribute = scew_get_attribute(element, i);
            printf(" %s=\"%s\"", scew_get_attribute_name(attribute),
                   scew_get_attribute_value(attribute));
        }
    }
}

void
print_element(scew_element const* element, unsigned int indent)
{
    int i = 0;
    XML_Char const* contents;

    if (element != NULL)
    {
        /**
         * Prints the starting element tag with its attributes.
         */
        print_justify(indent);
        printf("<%s", scew_get_element_name(element));
        print_attributes(element);
        printf(">\n");

        /**
         * Call print_element function again for each child of the
         * current element.
         */
        for (i = 0; i < scew_get_element_count(element); i++)
        {
            print_element(scew_get_element(element, i), indent + 1);
        }

        /* Prints element's content. */
        contents = scew_get_element_contents(element);
        if (contents != NULL)
        {
            print_justify(indent);
            printf("%s\n", contents);
        }

        /**
         * Prints the closing element tag.
         */
        print_justify(indent);
        printf("</%s>\n", scew_get_element_name(element));
    }
}

int
main(int argc, char** argv)
{
    int i = 0;
    int count = 0;
    scew_parser* parser;
    scew_element** list;

    if (argc < 2)
    {
        printf("usage: scew_print file.xml\n");
        return EXIT_FAILURE;
    }

    /**
     * Creates an SCEW parser. This is the first function to call.
     */
    parser = scew_parser_create();

    /* Loads an XML file */
    if (!scew_load_file(parser, argv[1]))
    {
        printf("unable to open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    print_element(scew_get_root(parser), 0);

    /* Frees the SCEW parser */
    scew_parser_free(parser);
}
