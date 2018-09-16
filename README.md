[![Build Status](https://travis-ci.org/aconchillo/scew.svg?branch=master)](https://travis-ci.org/aconchillo/scew)

# SCEW: A Simple C Expat Wrapper

The aim of SCEW is to provide an easy interface around the XML Expat parser,
as well as a simple interface for creating new XML documents. It provides
functions to load and access XML elements without the need to create Expat
event handling routines every time you want to load a new XML document.

These are the main SCEW features:

- Uses a DOM-like object model for new or parsed XML documents.
- Supports loading concatenated XML documents.
- Can copy and compare full XML documents, elements or attributes.
- Writes XML documents to multiple outputs.
- Allows adding new I/O sources easily.
- UTF-8, ISO-8859-1 and US-ASCII encodings (and UTF-16 in Windows).


# Download

SCEW is freely available for download under the terms of the GNU Lesser
General Public License v2.1 (LGPL).

Download the latest tarball and untar it:

- [[http://download.savannah.gnu.org/releases/scew/scew-1.2.0.tar.gz][scew-1.2.0.tar.gz]]

If you are cloning the repository make sure you run this first:

    : $ ./autogen.sh

Then, run the typical sequence:

    : $ ./configure
    : $ make
    : $ sudo make install


# License

Copyright (C) 2002-2018 Aleix Conchillo Flaque

SCEW is free software; you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free
Software Foundation; either version 2.1 of the License, or (at your option)
any later version.

SCEW is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General Public License along
with this library; if not, write to the Free Software Foundation, Inc., 51
Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
