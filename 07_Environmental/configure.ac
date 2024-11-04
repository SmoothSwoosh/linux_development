AC_PREREQ([2.71])

AC_INIT([rhasher], [1.0], [])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_PROG_CC

AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

AC_CHECK_LIB([readline], [readline])
AC_CHECK_LIB([rhash])

AC_CHECK_HEADER([rhash.h])
AC_CHECK_HEADER([readline/readline.h])

AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--enable-readline], [enable readline, disable getline]),
    AC_DEFINE(READLINE,[],[enable readline])
)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
