#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([akinator], [0.0.1], [sereganovik2002@gmail.com])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN([akinator])
AC_CONFIG_SRCDIR([akinator.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile Doxyfile])
AC_OUTPUT