AC_INIT([mini], [0.1], [pyrerune@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_HEADERS([config.h])
AC_CHECK_HEADERS([ncurses.h],,exit)
AC_CHECK_LIB([ncurses], [initscr],,exit)
AC_PROG_CC
AC_CONFIG_FILES([src/Makefile])
AC_OUTPUT
