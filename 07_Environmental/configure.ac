#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [0.0], [sereganovik2002@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([readline],[readline])
AC_CHECK_LIB([rhash], [rhash_library_init])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h rhash.h readline/readline.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp])

AC_ARG_ENABLE([readline], AS_HELP_STRING([--enable-readline], [enable readline]), AC_DEFINE(READLINE, [], [readline enabled]))

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
