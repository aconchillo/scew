#
# $Id$
#
# Author: Aleix Conchillo Flaque<aleix@member.fsf.org>
# Date:   Wed Nov 06, 2002 00:55
#
# Copyright (C) 2002, 2003 Aleix Conchillo Flaque
#

includedir = $(prefix)/include/$(PACKAGE)

include_HEADERS = scew.h attribute.h element.h parser.h tree.h types.h util.h

noinst_HEADERS = xattribute.h xelement.h xhandler.h xparser.h xtree.h

lib_LIBRARIES = libscew.a

libscew_a_SOURCES = attribute.c element.c parser.c tree.c util.c \
                    xattribute.c xhandler.c xparser.c
