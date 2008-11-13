#
# Author: Aleix Conchillo Flaque <aleix@member.fsf.org>
# Date:   Wed Nov 06, 2002 00:55
#
# Copyright (C) 2002-2008 Aleix Conchillo Flaque
#

includedir = $(prefix)/include/$(PACKAGE)

include_HEADERS = attribute.h bool.h element.h error.h list.h parser.h \
                  scew.h str.h tree.h writer.h writer_buffer.h writer_file.h

noinst_HEADERS = xerror.h xparser.h

lib_LTLIBRARIES = libscew.la

libscew_la_SOURCES = attribute.c element.c error.c list.c parser.c str.c \
                     tree.c writer.c writer_buffer.c writer_file.c \
                     xerror.c xparser.c
libscew_la_LDFLAGS = -version-info 1:0:1
