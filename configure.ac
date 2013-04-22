# Copyright (C) 2013 Thomas Sigurdsen <thomas.sigurdsen@gmail.com>
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.

dnl Process this file with autoconf to produce a configure script.

AC_INIT([neuton], [0.1], 
        [https://github.com/HarNys/IMT3601-project/issues?state=open],
        [https://github.com/HarNys/IMT3601-project])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_CONFIG_SRCDIR([src/Includes.hpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([Debug])
AC_CONFIG_MACRO_DIR([m4])

# I am using [foreign] here because we want to use and keep using the markdown 
# format and .md on our README file.
AM_INIT_AUTOMAKE([subdir-objects] [foreign])
AC_CONFIG_FILES([Makefile])

AC_PROG_CXX
AC_PROG_CC
AM_PROG_LIBTOOL

#AC_CHECK_LIB
PKG_CHECK_MODULES(SFML, [sfml-all >= 2.0])
#PKG_CHECK_MODULES(SFML, [sfml-graphics >= 2])
#PKG_CHECK_MODULES(SFML, [sfml-system >= 2])
#PKG_CHECK_MODULES(SFML, [sfml-audio >= 2])

AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADER_STDBOOL

AC_CHECK_FUNCS([pow sqrt strchr])

AC_OUTPUT

echo
echo
echo Neuton.................................... : Version $VERSION
echo Prefix....................................... : $prefix
