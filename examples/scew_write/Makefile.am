#
# Author: Aleix Conchillo Flaque <aconchillo@gmail.com>
# Date:   Sun Mar 30, 2003 12:23
#
# Copyright (C) 2002-2016 Aleix Conchillo Flaque
#

AM_CPPFLAGS = -I$(top_srcdir)

noinst_PROGRAMS = scew_write

scew_write_SOURCES = scew_write.c

if SCEW_UNICODE_WCHAR_T
scew_write_LDADD = $(top_builddir)/scew/libsceww.la
else
scew_write_LDADD = $(top_builddir)/scew/libscew.la
endif
