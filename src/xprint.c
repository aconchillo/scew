/**
 *
 * @file     xtree.c
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Sun Mar 30, 2003 13:23
 * @brief    SCEW private tree type declaration
 *
 * $Id$
 *
 * @if copyright
 *
 * Copyright (C) 2003 Aleix Conchillo Flaque
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
 */

#include "xprint.h"

/* indentation size (in whitespaces) */
int const indent_size = 3;


void
indent_print(FILE* out, unsigned int indent)
{
    int i = 0;

    for (i = 0; i < indent * indent_size; i++)
    {
        fprintf(out, " ");
    }
}

void
tree_print(scew_tree const* tree, FILE* out)
{
    element_print(tree->root, out, 0);
}

void
element_print(scew_element const* element, FILE* out, unsigned int indent)
{
    int i = 0;
    int closed = 0;
    XML_Char const* contents;

    if (element != NULL)
    {
        indent_print(out, indent);
        fprintf(out, "<%s", scew_element_name(element));
        for (i = 0; i < scew_attribute_count(element); i++)
        {
            attribute_print(scew_attribute_by_index(element, i), out);
        }

        contents = scew_element_contents(element);
        if ((contents == NULL) && (element->child == NULL)
            && (element->parent != NULL))
        {
            fprintf(out, "/>\n");
            closed = 1;
        }
        else
        {
            fprintf(out, ">\n");
        }

        for (i = 0; i < scew_element_count(element); i++)
        {
            element_print(scew_element_by_index(element, i), out, indent + 1);
        }

        if (contents != NULL)
        {
            indent_print(out, indent);
            fprintf(out, "%s\n", contents);
        }

        if (!closed)
        {
            indent_print(out, indent);
            fprintf(out, "</%s>\n", scew_element_name(element));
        }
    }
}

void
attribute_print(scew_attribute const* attribute, FILE* out)
{
    fprintf(out, " %s=\"%s\"", attribute->name, attribute->value);
}
