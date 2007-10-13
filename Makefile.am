#
# Author: Aleix Conchillo Flaque <aleix@member.fsf.org>
# Date:   Mon Nov 04, 2002 20:29
#
# Copyright (C) 2002, 2003, 2004, 2007 Aleix Conchillo Flaque
#

SUBDIRS = doc etc win32 scew tests

EXTRA_DIST = INSTALL.WIN32

.PHONY: doc examples

examples:
	($(MAKE) && cd examples && $(MAKE))

if DOC

doc:
	(cd doc && $(MAKE) doc)

else

doc:
	@echo "WARNING: Documentation generation not enabled or available";

endif
