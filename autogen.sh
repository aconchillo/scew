#!/bin/sh
rm -f ltconfig ltmain.sh config.cache aclocal.m4
# remove the autoconf cache
rm -rf autom4te*.cache
set -e
echo "libtoolize... "
${LIBTOOLIZE:-libtoolize} --copy --force --automake >/dev/null
echo "aclocal... "
${ACLOCAL:-aclocal} -I etc/autoconf
echo "autoheader... "
${AUTOHEADER:-autoheader}
echo "autoconf... "
${AUTOCONF:-autoconf}
echo "automake... "
${AUTOMAKE:-automake} -a
echo okay.
# remove the autoconf cache
rm -rf autom4te*.cache
exit
