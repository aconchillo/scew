#
# Author: Aleix Conchillo Flaque <aleix@member.fsf.org>
# Date:   Wed Nov 06, 2002 00:55
#
# Copyright (C) 2002, 2003, 2004, 2005, 2007 Aleix Conchillo Flaque
#

includedir = $(prefix)/include/$(PACKAGE)

include_HEADERS = scew.h attribute.h element.h error.h parser.h str.h \
                  tree.h types.h writer.h

noinst_HEADERS = xerror.h xhandler.h xparser.h xprint.h

lib_LTLIBRARIES = libscew.la

libscew_la_SOURCES = attribute.c element.c error.c list.c parser.c str.c \
                     tree.c writer.c xerror.c xhandler.c xparser.c xprint.c
libscew_la_LDFLAGS = -version-info 1:0:1
