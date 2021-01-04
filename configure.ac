AC_PREREQ([2.69])
AC_INIT([backmap], [0.0], [matteoeghirotta@gmail.com])
AM_INIT_AUTOMAKE([foreign dist-xz -Wall -Werror]) # silent-rules
AC_CONFIG_SRCDIR([src/backmap.c])

: ${CFLAGS=""}

AC_PROG_CC([clang gcc])
#AC_PROG_CC([musl-gcc gcc clang])
AC_PROG_CC_STDC
AM_PROG_CC_C_O

AC_CHECK_LIB([rt], [main])
AC_CHECK_LIB([m],  [main])

#AC_CONFIG_COMMANDS_PRE(cd contrib/levmar-2.6-mod && cmake . && make && cd -)
AC_CONFIG_FILES([Makefile src/Makefile])

# does not work
#AX_GCC_VERSION
#echo "GCC $GCC VERSION: $GCC_VERSION"

AC_OUTPUT
