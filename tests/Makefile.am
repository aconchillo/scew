#
# Author: Aleix Conchillo Flaque <aleix@member.fsf.org>
# Date:   Thu Aug 02, 2007 14:20
#
# Copyright (C) 2007-2009 Aleix Conchillo Flaque
#

INCLUDES = -I$(top_srcdir)

if CHECK_TESTS

COMMON = main.c test.h

TESTS = check_attribute check_element check_list check_tree

check_PROGRAMS = check_attribute check_element check_list check_tree

# Attributes
check_attribute_SOURCES = $(COMMON) check_attribute.c \
	$(top_builddir)/scew/attribute.h $(top_builddir)/scew/element.h
check_attribute_CFLAGS = @CHECK_CFLAGS@
check_attribute_LDADD = @CHECK_LIBS@ $(top_builddir)/scew/libscew.la

# Elements
check_element_SOURCES = $(COMMON) check_element.c \
	$(top_builddir)/scew/attribute.h $(top_builddir)/scew/element.h \
	$(top_builddir)/scew/list.h
check_element_CFLAGS = @CHECK_CFLAGS@
check_element_LDADD = @CHECK_LIBS@ $(top_builddir)/scew/libscew.la

# Lists
check_list_SOURCES = $(COMMON) check_list.c $(top_builddir)/scew/list.h
check_list_CFLAGS = @CHECK_CFLAGS@
check_list_LDADD = @CHECK_LIBS@ $(top_builddir)/scew/libscew.la

# Trees
check_tree_SOURCES = $(COMMON) check_tree.c \
	$(top_builddir)/scew/element.h $(top_builddir)/scew/tree.h
check_tree_CFLAGS = @CHECK_CFLAGS@
check_tree_LDADD = @CHECK_LIBS@ $(top_builddir)/scew/libscew.la

else

check:
	@echo "WARNING: Check unit testing framework not available"

endif
