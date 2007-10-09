#
# Author: Aleix Conchillo Flaque <aleix@member.fsf.org>
# Date:   Thu Aug 02, 2007 14:20
#
# Copyright (C) 2007 Aleix Conchillo Flaque
#

INCLUDES = -I$(top_srcdir)

if CHECK_TESTS

COMMONSRC = main.c test.h

TESTS = check_element check_list

check_PROGRAMS = check_element check_list

check_element_SOURCES = $(COMMONSRC) check_element.c $(top_builddir)/scew/element.h
check_element_CFLAGS = @CHECK_CFLAGS@
check_element_LDADD = @CHECK_LIBS@ $(top_builddir)/scew/libscew.la

check_list_SOURCES = $(COMMONSRC) check_list.c $(top_builddir)/scew/list.h
check_list_CFLAGS = @CHECK_CFLAGS@
check_list_LDADD = @CHECK_LIBS@ $(top_builddir)/scew/libscew.la

else

check:
	@echo "WARNING: Check unit testing framework not available"

endif
