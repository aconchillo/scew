#
# $Id$
#
# Author: Aleix Conchillo Flaque<aconchillo@acm.org>
# Date:   Wed Nov 06, 2002 00:55
#
# Copyright (C) 2002 Aleix Conchillo Flaque
#

INCLUDES = -I/usr/local/include

includedir = $(prefix)/include/$(PACKAGE)

include_HEADERS = scew.h attribute.h element.h parser.h util.h

noinst_HEADERS = handler.h xattribute.h xelement.h xparser.h

lib_LIBRARIES = libscew.a

libscew_a_SOURCES = handler.c attribute.c element.c parser.c util.c \
                    xattribute.c xelement.c xparser.c
