#!/bin/sh
rm -f ltconfig ltmain.sh config.cache aclocal.m4
# remove the autoconf cache
rm -rf autom4te*.cache
set -e
echo -n "libtoolize... "
${LIBTOOLIZE:-libtoolize} --copy --force --automake >/dev/null
echo -n "aclocal... "
${ACLOCAL:-aclocal} -I etc/autoconf
echo -n "autoheader... "
${AUTOHEADER:-autoheader}
echo -n "autoconf... "
${AUTOCONF:-autoconf}
echo -n "automake... "
${AUTOMAKE:-automake} -a
echo okay.
# remove the autoconf cache
rm -rf autom4te*.cache
exit
