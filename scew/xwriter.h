/**
 * @file
 * @author   Aleix Conchillo Flaque <aconchillo@ieec.cat>
 * @date     Tue Jul 22, 2008 22:05
 * @brief    SCEW
 **/

#ifndef XWRITER_H_0807222205
#define XWRITER_H_0807222205

#include "writer.h"


// Constants

enum
  {
    DEFAULT_INDENT_SPACES_ = 3  /**< Default number of indent spaces */
  };


// Types

typedef bool (*scew_writer_close_hook) (scew_writer *);

typedef bool (*scew_writer_printf_hook) (scew_writer *, XML_Char const *, ...);

struct scew_writer
{
  scew_writer_close_hook close;
  scew_writer_printf_hook printf;
  bool indented;
  unsigned int indent;
  unsigned int spaces;
};

#endif // XWRITER_H_0807222205
