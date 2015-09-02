#ifndef _IMAGE_IMAGE_CONFIG_H
#define _IMAGE_IMAGE_CONFIG_H 1
 
/* supersonic/supersonic-config.h. Generated automatically at end of configure. */
/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Force failure checking. */
#ifndef IMAGE_FORCE_FAILURE_CHECK
#define IMAGE_FORCE_FAILURE_CHECK 1
#endif

/* Define to 1 if you have the `atexit' function. */
#ifndef IMAGE_HAVE_ATEXIT
#define IMAGE_HAVE_ATEXIT 1
#endif

/* define if the Boost library is available */
/* #undef HAVE_BOOST */

/* define if the Boost::System library is available */
/* #undef HAVE_BOOST_SYSTEM */

/* define if the Boost::Timer library is available */
/* #undef HAVE_BOOST_TIMER */

/* define if the compiler supports basic C++11 syntax */
#ifndef IMAGE_HAVE_CXX11
#define IMAGE_HAVE_CXX11 1
#endif

/* Define to 1 if you have the <dlfcn.h> header file. */
#ifndef IMAGE_HAVE_DLFCN_H
#define IMAGE_HAVE_DLFCN_H 1
#endif

/* Define to 1 if you have the `floor' function. */
#ifndef IMAGE_HAVE_FLOOR
#define IMAGE_HAVE_FLOOR 1
#endif

/* Define to 1 if you have the <gflags/gflags.h> header file. */
/* #undef HAVE_GFLAGS_GFLAGS_H */

/* Define to 1 if you have the <glog/logging.h> header file. */
/* #undef HAVE_GLOG_LOGGING_H */

/* Define to 1 if you have the <google/protobuf/text_format.h> header file. */
/* #undef HAVE_GOOGLE_PROTOBUF_TEXT_FORMAT_H */

/* Define to 1 if you have the <inttypes.h> header file. */
#ifndef IMAGE_HAVE_INTTYPES_H
#define IMAGE_HAVE_INTTYPES_H 1
#endif

/* Define to 1 if you have the <limits.h> header file. */
#ifndef IMAGE_HAVE_LIMITS_H
#define IMAGE_HAVE_LIMITS_H 1
#endif

/* Define to 1 if you have the `localtime_r' function. */
#ifndef IMAGE_HAVE_LOCALTIME_R
#define IMAGE_HAVE_LOCALTIME_R 1
#endif

/* Define to 1 if your system has a GNU libc compatible `malloc' function, and
   to 0 otherwise. */
#ifndef IMAGE_HAVE_MALLOC
#define IMAGE_HAVE_MALLOC 1
#endif

/* Define to 1 if you have the <memory.h> header file. */
#ifndef IMAGE_HAVE_MEMORY_H
#define IMAGE_HAVE_MEMORY_H 1
#endif

/* Define to 1 if you have the `memset' function. */
#ifndef IMAGE_HAVE_MEMSET
#define IMAGE_HAVE_MEMSET 1
#endif

/* Define to 1 if you have the `pow' function. */
#ifndef IMAGE_HAVE_POW
#define IMAGE_HAVE_POW 1
#endif

/* Define if you have POSIX threads libraries and header files. */
#ifndef IMAGE_HAVE_PTHREAD
#define IMAGE_HAVE_PTHREAD 1
#endif

/* Define to 1 if the system has the type `ptrdiff_t'. */
#ifndef IMAGE_HAVE_PTRDIFF_T
#define IMAGE_HAVE_PTRDIFF_T 1
#endif

/* Define to 1 if you have the <re2/re2.h> header file. */
/* #undef HAVE_RE2_RE2_H */

/* Define to 1 if your system has a GNU libc compatible `realloc' function,
   and to 0 otherwise. */
#ifndef IMAGE_HAVE_REALLOC
#define IMAGE_HAVE_REALLOC 1
#endif

/* define if the compiler implements pthread_rwlock_* */
#ifndef IMAGE_HAVE_RWLOCK
#define IMAGE_HAVE_RWLOCK 1
#endif

/* Define to 1 if you have the `setenv' function. */
#ifndef IMAGE_HAVE_SETENV
#define IMAGE_HAVE_SETENV 1
#endif

/* Define to 1 if you have the `sqrt' function. */
#ifndef IMAGE_HAVE_SQRT
#define IMAGE_HAVE_SQRT 1
#endif

/* Define to 1 if stdbool.h conforms to C99. */
#ifndef IMAGE_HAVE_STDBOOL_H
#define IMAGE_HAVE_STDBOOL_H 1
#endif

/* Define to 1 if you have the <stddef.h> header file. */
#ifndef IMAGE_HAVE_STDDEF_H
#define IMAGE_HAVE_STDDEF_H 1
#endif

/* Define to 1 if you have the <stdint.h> header file. */
#ifndef IMAGE_HAVE_STDINT_H
#define IMAGE_HAVE_STDINT_H 1
#endif

/* Define to 1 if you have the <stdlib.h> header file. */
#ifndef IMAGE_HAVE_STDLIB_H
#define IMAGE_HAVE_STDLIB_H 1
#endif

/* Define to 1 if you have the `strcasecmp' function. */
#ifndef IMAGE_HAVE_STRCASECMP
#define IMAGE_HAVE_STRCASECMP 1
#endif

/* Define to 1 if you have the `strerror' function. */
#ifndef IMAGE_HAVE_STRERROR
#define IMAGE_HAVE_STRERROR 1
#endif

/* Define to 1 if you have the <string> header file. */
#ifndef IMAGE_HAVE_STRING
#define IMAGE_HAVE_STRING 1
#endif

/* Define to 1 if you have the <strings.h> header file. */
#ifndef IMAGE_HAVE_STRINGS_H
#define IMAGE_HAVE_STRINGS_H 1
#endif

/* Define to 1 if you have the <string.h> header file. */
#ifndef IMAGE_HAVE_STRING_H
#define IMAGE_HAVE_STRING_H 1
#endif

/* Define to 1 if you have the <sys/stat.h> header file. */
#ifndef IMAGE_HAVE_SYS_STAT_H
#define IMAGE_HAVE_SYS_STAT_H 1
#endif

/* Define to 1 if you have the <sys/time.h> header file. */
#ifndef IMAGE_HAVE_SYS_TIME_H
#define IMAGE_HAVE_SYS_TIME_H 1
#endif

/* Define to 1 if you have the <sys/types.h> header file. */
#ifndef IMAGE_HAVE_SYS_TYPES_H
#define IMAGE_HAVE_SYS_TYPES_H 1
#endif

/* Define to 1 if you have the `tzset' function. */
#ifndef IMAGE_HAVE_TZSET
#define IMAGE_HAVE_TZSET 1
#endif

/* Define to 1 if you have the <unistd.h> header file. */
#ifndef IMAGE_HAVE_UNISTD_H
#define IMAGE_HAVE_UNISTD_H 1
#endif

/* Define to 1 if the system has the type `_Bool'. */
/* #undef HAVE__BOOL */

/* define if first argument to InterlockedExchange is just LONG */
/* #undef INTERLOCKED_EXCHANGE_NONVOLATILE */

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#ifndef IMAGE_LT_OBJDIR
#define IMAGE_LT_OBJDIR ".libs/"
#endif

/* Name of package */
#ifndef IMAGE_PACKAGE
#define IMAGE_PACKAGE "supersonic"
#endif

/* Define to the address where bug reports for this package should be sent. */
#ifndef IMAGE_PACKAGE_BUGREPORT
#define IMAGE_PACKAGE_BUGREPORT ""
#endif

/* Define to the full name of this package. */
#ifndef IMAGE_PACKAGE_NAME
#define IMAGE_PACKAGE_NAME "supersonic"
#endif

/* Define to the full name and version of this package. */
#ifndef IMAGE_PACKAGE_STRING
#define IMAGE_PACKAGE_STRING "supersonic 0.9.4"
#endif

/* Define to the one symbol short name of this package. */
#ifndef IMAGE_PACKAGE_TARNAME
#define IMAGE_PACKAGE_TARNAME "supersonic"
#endif

/* Define to the home page for this package. */
#ifndef IMAGE_PACKAGE_URL
#define IMAGE_PACKAGE_URL ""
#endif

/* Define to the version of this package. */
#ifndef IMAGE_PACKAGE_VERSION
#define IMAGE_PACKAGE_VERSION "0.9.4"
#endif

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define to 1 if you have the ANSI C header files. */
#ifndef IMAGE_STDC_HEADERS
#define IMAGE_STDC_HEADERS 1
#endif

/* Version number of package */
#ifndef IMAGE_VERSION
#define IMAGE_VERSION "0.9.4"
#endif

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to rpl_malloc if the replacement function should be used. */
/* #undef malloc */

/* Define to rpl_realloc if the replacement function should be used. */
/* #undef realloc */

/* Define to the equivalent of the C99 'restrict' keyword, or to
   nothing if this is not supported.  Do not define if restrict is
   supported directly.  */
#ifndef _supersonic_restrict
#define _supersonic_restrict __restrict
#endif
/* Work around a bug in Sun C++: it does not support _Restrict or
   __restrict__, even though the corresponding Sun C compiler ends up with
   "#define restrict _Restrict" or "#define restrict __restrict__" in the
   previous line.  Perhaps some future version of Sun C++ will work with
   restrict; if so, hopefully it defines __RESTRICT like Sun C does.  */
#if defined __SUNPRO_CC && !defined __RESTRICT
# define _Restrict
# define __restrict__
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
 
/* once: _IMAGE_IMAGE_CONFIG_H */
#endif
