/**
 *
 * @file     scew_print.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Wed Dec 04, 2002 01:11
 * @brief    SCEW usage example
 *
 * $Id$
 *
 * @if copyright
 *
 * Copyright (C) 2002, 2003 Aleix Conchillo Flaque
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

#include <stdio.h>


/* indentation size (in whitespaces) */
static int const indent_size = 4;

void
print_indent(unsigned int indent)
{
    printf("%*s", indent * indent_size, " ");
}

void
print_attributes(scew_element* element)
{
    int i = 0;
    scew_attribute* attribute = NULL;

    if (element != NULL)
    {
        /**
         * Iterates through the element's attribute list, printing the
         * pair name-value.
         */
        for (i = 0; i < scew_attribute_count(element); i++)
        {
            attribute = scew_attribute_by_index(element, i);
            printf(" %s=\"%s\"", scew_attribute_name(attribute),
                   scew_attribute_value(attribute));
        }
    }
}

void
print_element(scew_element* element, unsigned int indent)
{
    int i = 0;
    XML_Char const* contents;

    if (element != NULL)
    {
        /**
         * Prints the starting element tag with its attributes.
         */
        print_indent(indent);
        printf("<%s", scew_element_name(element));
        print_attributes(element);
        printf(">\n");

        /**
         * Call print_element function again for each child of the
         * current element.
         */
        for (i = 0; i < scew_element_count(element); i++)
        {
            print_element(scew_element_by_index(element, i), indent + 1);
        }

        /* Prints element's content. */
        contents = scew_element_contents(element);
        if (contents != NULL)
        {
            print_indent(indent);
            printf("%s\n", contents);
        }

        /**
         * Prints the closing element tag.
         */
        print_indent(indent);
        printf("</%s>\n", scew_element_name(element));
    }
}

int
main(int argc, char** argv)
{
    scew_tree* tree;
    scew_parser* parser;

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
    if (!scew_parser_load_file(parser, argv[1]))
    {
        printf("unable to open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    tree = scew_parser_tree(parser);
    print_element(scew_tree_root(tree), 0);

    /* Remember to free tree (scew_parser_free does not free it) */
    scew_tree_free(tree);

    /* Frees the SCEW parser */
    scew_parser_free(parser);

    return 0;
}
