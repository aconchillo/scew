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

#ifdef XML_UNICODE_WCHAR_T
#include <wchar.h>
#endif

/* indentation size (in whitespaces) */
static int const indent_size = 3;

void
indent_print(FILE* out, unsigned int indent)
{
    unsigned int i = 0;

    for (i = 0; i < indent * indent_size; i++)
    {
#ifdef XML_UNICODE_WCHAR_T
        fwprintf(out, " ");
#else
        fprintf(out, " ");
#endif /* XML_UNICODE_WCHAR_T */
    }
}

void
tree_print(scew_tree const* tree, FILE* out)
{
    static XML_Char const* version = "1.0";
#ifdef XML_UNICODE_WCHAR_T
    static XML_Char const* encoding = "UTF-16";

    fwprintf(out,
             "<?xml version=\"%s\" encoding=\"%s\" standalone=\"%s\"?>\n\n",
             (tree->version == NULL ? version : tree->version),
             (tree->encoding == NULL ? encoding : tree->encoding),
             (tree->standalone > 0 ? "yes" : "no"));
#else
    static XML_Char const* encoding = "UTF-8";

    fprintf(out,
             "<?xml version=\"%s\" encoding=\"%s\" standalone=\"%s\"?>\n\n",
            (tree->version == NULL ? version : tree->version),
            (tree->encoding == NULL ? encoding : tree->encoding),
            (tree->standalone > 0 ? "yes" : "no"));
#endif /* XML_UNICODE_WCHAR_T */

    element_print(tree->root, out, 0);
}

void
element_print(scew_element const* element, FILE* out, unsigned int indent)
{
    unsigned int closed = 0;
    XML_Char const* contents;
    scew_element* child = NULL;
    scew_attribute* attribute = NULL;

    if (element == NULL)
    {
        return;
    }

    indent_print(out, indent);
#ifdef XML_UNICODE_WCHAR_T
    fwprintf(out, "<%s", scew_element_name(element));
#else
    fprintf(out, "<%s", scew_element_name(element));
#endif /* XML_UNICODE_WCHAR_T */
    attribute = NULL;
    while ((attribute = scew_attribute_next(element, attribute)) != NULL)
    {
        attribute_print(attribute, out);
    }

    contents = scew_element_contents(element);
    if ((contents == NULL) && (element->child == NULL)
        && (element->parent != NULL))
    {
#ifdef XML_UNICODE_WCHAR_T
        fwprintf(out, "/>\n");
#else
        fprintf(out, "/>\n");
#endif /* XML_UNICODE_WCHAR_T */
        closed = 1;
    }
    else
    {
#ifdef XML_UNICODE_WCHAR_T
        fwprintf(out, ">");
        if (contents == NULL)
        {
            fwprintf(out, "\n");
        }
#else
        fprintf(out, ">");
        if (contents == NULL)
        {
            fprintf(out, "\n");
        }
#endif /* XML_UNICODE_WCHAR_T */
    }

    child = NULL;
    while ((child = scew_element_next(element, child)) != NULL)
    {
        element_print(child, out, indent + 1);
    }

    if (contents != NULL)
    {
#ifdef XML_UNICODE_WCHAR_T
        fwprintf(out, "%s", contents);
#else
        fprintf(out, "%s", contents);
#endif /* XML_UNICODE_WCHAR_T */
    }
    else
    {
        indent_print(out, indent);
    }

    if (!closed)
    {
#ifdef XML_UNICODE_WCHAR_T
        fwprintf(out, "</%s>\n", scew_element_name(element));
#else
        fprintf(out, "</%s>\n", scew_element_name(element));
#endif /* XML_UNICODE_WCHAR_T */
    }
}

void
attribute_print(scew_attribute const* attribute, FILE* out)
{
    if (attribute == NULL)
    {
        return;
    }

#ifdef XML_UNICODE_WCHAR_T
    fwprintf(out, " %s=\"%s\"", attribute->name, attribute->value);
#else
    fprintf(out, " %s=\"%s\"", attribute->name, attribute->value);
#endif /* XML_UNICODE_WCHAR_T */
}
