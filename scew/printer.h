/**
 * @file     printer.h
 * @brief    SCEW printer
 * @author   Aleix Conchillo Flaque <aleix@member.fsf.org>
 * @date     Fri Jan 16, 2009 22:34
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
 **/


#ifndef PRINTER_H_0901162234
#define PRINTER_H_0901162234

#include "writer.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef struct scew_printer scew_printer;

extern scew_printer* scew_printer_create (scew_writer *writer);

extern void scew_printer_free (scew_printer *printer);

extern scew_writer* scew_printer_set_writer (scew_printer *printer,
                                             scew_writer *writer);


/**
 * @defgroup SCEWPrinterProp Properties
 * @ingroup SCEWPrinter
 */

/**
 * Tells whether the output sent to the given SCEW @a printer should be
 * @a indented or not.
 *
 * @pre printer != NULL
 *
 * @param printer the SCEW printer to change its indentation for.
 * @param indented true if the output should be indented, false
 * otherwise.
 *
 * @ingroup SCEWPrinterProp
 */
extern void scew_printer_set_indented (scew_printer *printer,
                                       scew_bool indented);

/**
 * Sets the number of @a spaces to use when indenting output for the
 * given SCEW @a printer.
 *
 * @pre printer != NULL
 *
 * @param printer the SCEW printer to change its indentation spaces for.
 * @param spaces the number of spaces to use for indentation.
 *
 * @ingroup SCEWPrinterProp
 */
extern void scew_printer_set_indentation (scew_printer *printer,
                                          unsigned int spaces);


/**
 * @defgroup SCEWPrinterOutput Output
 * @ingroup SCEWPrinter
 */

/**
 * Prints the given SCEW @a tree to @a printer. This will print the XML
 * document prolog and the root element with all its children.
 *
 * @pre printer != NULL
 * @pre tree != NULL
 *
 * @param printer
 * @param tree
 *
 * @ingroup SCEWPrinterOutput
 */
extern scew_bool scew_printer_print_tree (scew_printer *printer,
                                          scew_tree const *tree);

/**
 *
 * @pre printer != NULL
 * @pre element != NULL
 *
 * @ingroup SCEWPrinterOutput
 */
extern scew_bool scew_printer_print_element (scew_printer *printer,
                                             scew_element const *element);

/**
 *
 * @pre printer != NULL
 * @pre element != NULL
 *
 * @ingroup SCEWPrinterOutput
 */
extern scew_bool
scew_printer_print_element_children (scew_printer *printer,
                                     scew_element const  *element);

/**
 *
 * @pre printer != NULL
 * @pre element != NULL
 *
 * @ingroup SCEWPrinterOutput
 */
extern scew_bool
scew_printer_print_element_attributes (scew_printer *printer,
                                       scew_element const *element);

/**
 *
 * @pre printer != NULL
 * @pre attribute != NULL
 *
 * @ingroup SCEWPrinterOutput
 */
extern scew_bool
scew_printer_print_attribute (scew_printer *printer,
                              scew_attribute const *attribute);

#endif /* PRINTER_H_0901162234 */
