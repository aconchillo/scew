#!/bin/sh
rm -f config.cache
rm -f acconfig.h
aclocal -I ./etc/autoconf
autoconf
autoheader
automake -a
exit
