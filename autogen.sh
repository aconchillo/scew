#!/bin/sh

rm -f ltconfig ltmain.sh config.cache aclocal.m4

#
# Remove the autoconf cache
#
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

#
# Remove the autoconf cache
#
rm -rf autom4te*.cache

#
# Force everything to the abspath of this script
#
srcdir=$(cd $(dirname $0) && pwd)

$srcdir/configure "$@"
