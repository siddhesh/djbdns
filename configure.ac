#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([djbdns], [1.05.3], [pj.pandit@yahoo.co.in])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([dnsip.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_HEADER_MAJOR
AC_CHECK_HEADERS([fcntl.h netinet/in.h stdlib.h sys/param.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_OFF_T

# Checks for library functions.
AC_FUNC_CHOWN
AC_FUNC_GETGROUPS
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_CHECK_FUNCS([fchdir gethostname gettimeofday mkdir munmap select socket utime])

AC_CONFIG_FILES([Makefile]
                [etc/Makefile]
                [etc/ip/Makefile]
                [etc/servers/Makefile])
AC_OUTPUT
