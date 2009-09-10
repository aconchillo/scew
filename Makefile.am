#
# Author: Aleix Conchillo Flaque <aleix@member.fsf.org>
# Date:   Mon Nov 04, 2002 20:29
#
# Copyright (C) 2002-2009 Aleix Conchillo Flaque
#

SUBDIRS = doc etc scew examples tests win32

.PHONY: doc

if DOC

doc:
	(cd doc && $(MAKE) doc)

else

doc:
	@echo "WARNING: Documentation generation not enabled or available";

endif
