#
# Author: Aleix Conchillo Flaque <aconchillo@gmail.com>
# Date:   Mon Nov 04, 2002 20:29
#
# Copyright (C) 2002-2013 Aleix Conchillo Flaque
#

SUBDIRS = doc etc scew examples tests win32

dist-hook:
	$(SHELL) $(top_srcdir)/ChangeLog > $(top_distdir)/ChangeLog

.PHONY: doc

if DOC

doc:
	(cd doc && $(MAKE) doc)

else

doc:
	@echo "WARNING: Documentation generation not enabled or available";

endif
