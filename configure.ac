AC_PREREQ([2.71])
AC_INIT([backmap],[0.0],[matteoeghirotta@gmail.com])
AM_INIT_AUTOMAKE([foreign dist-xz -Wall -Werror]) # silent-rules
AC_CONFIG_SRCDIR([src/backmap.c])

# keep this: no default CFLAGS
: ${CFLAGS=""}

AC_PROG_CC([clang gcc musl-gcc ])
AM_PROG_CC_C_O

AC_CHECK_LIB([rt], [main])
AC_CHECK_LIB([m],  [main])

#AC_CONFIG_COMMANDS_PRE(cd contrib/levmar-2.6-mod && cmake . && make && cd -)
AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT
