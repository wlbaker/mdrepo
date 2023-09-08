#

# AC_INIT formate changed in 2.63
AC_PREREQ([2.63])

# package version number, not the same as shared lib version!
m4_define([pista_package_version_major], [0])
m4_define([pista_package_version_minor], [3])
m4_define([pista_package_version_micro], [0])
m4_define([pista_package_version], [pista_package_version_major.pista_package_version_minor.pista_package_version_micro])

AC_INIT([pista], [pista_package_version], [william.l.baker2@gmail.com])

AC_CONFIG_MACRO_DIR([m4])

# The AC_CONFIG_SRCDIR macro is a sanity check. Its purpose is to ensure that the generated 
# configure script knows that the directory on which it is being executed is actually the 
# project directory.

AC_CONFIG_SRCDIR(include/pista.h)


# AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror])

# AR detection comes before LT_INIT
AM_PROG_AR

#
# build both shared and static  LT_INIT( [static] [shared] )
#

LT_INIT( [static] [shared] )

AC_PROG_CC
# use add c99 flag
AC_PROG_CC_STDC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_LANG([C++])
AX_PKG_SWIG

# 
# For function checking, look at:
# https://github.com/mojolingo/asterisk/blob/master/configure.ac
# 
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([gethostbyname gethostname gettimeofday htonll inet_ntoa isascii memchr memmove memset mkdir strdup strtod strtol strtold strtoq utime])

#
# Adding debug support per:
# https://stackoverflow.com/questions/4553735/gnu-autotools-debug-release-targets
# 
AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

# Initialize pkg-config.
# We require at least 0.22, as "Requires.private" behaviour changed there.
# 01JAN16: removed wlb...macro not recognized?
# PKG_PROG_PKG_CONFIG([0.22])

# Library version (NOT the same as the package version).
# Carefully read the libtool docs before updating these numbers!
# The algorithm for determining which number to change (and how) is nontrivial!
# http://www.gnu.org/software/libtool/manual/libtool.html#Updating-version-info
PISTA_LIB_VERSION_CURRENT=2
PISTA_LIB_VERSION_REVISION=0
PISTA_LIB_VERSION_AGE=0
PISTA_LIB_VERSION="$PISTA_LIB_VERSION_CURRENT:$PISTA_LIB_VERSION_REVISION:$PISTA_LIB_VERSION_AGE"
PISTA_LIB_LDFLAGS="-version-info $PISTA_LIB_VERSION"
AC_SUBST(PISTA_LIB_VERSION_CURRENT)
AC_SUBST(PISTA_LIB_VERSION_REVISION)
AC_SUBST(PISTA_LIB_VERSION_AGE)
AC_SUBST(PISTA_LIB_VERSION)
AC_SUBST(PISTA_LIB_LDFLAGS)

AC_ARG_ENABLE(all-drivers, AC_HELP_STRING([--enable-all-drivers],
    [enable all drivers by default [default=yes]]),
    [HW_ENABLED_DEFAULT="$enableval"],
    [HW_ENABLED_DEFAULT="yes"])


#
# Platform specific setup
#
#############################
AC_CANONICAL_HOST
# Check for which host we are on and setup a few things
# specifically based on the host

have_zeromq="yes"
have_avahiclient="no"
have_exodriver="yes"
have_mccul="no"
have_bmp180="no"
have_simu="yes"
# have_propaqm="yes"
have_dt="no"
windows_build="no"

case $host_os in
  darwin* )
        # Do something specific for mac
        ;;
  linux*)
        # Do something specific for linux
	have_bmp180="yes"
        ;;
   *BSD*)
        # Do something specific for BSD
        ;;
   mingw*)
        # Some drivers only run on one OS or another
	# have_mccul="yes"
        # The answer is still no!!!
	have_dt="no"
	windows_build="yes"
        ;;
   cygwin*)
        # Some drivers only run on one OS or another
	# have_mccul="yes"
        # The answer is still no!!!
	have_dt="no"
	windows_build="yes"
        ;;
    *)
        #Default Case
        AC_MSG_ERROR([Your platform is not currently supported: "$host_os"])
        ;;
esac

AM_CONDITIONAL(WINDOWS_BUILD, test "$windows_build" = "yes")

# Usage: DRIVER([Device name], [driver-name])
# An optional third argument [no] disables that driver.
m4_define([driverize], [m4_tolower(m4_bpatsubst([$1], [[^0-9a-zA-Z-]+], [-]))])
m4_define([upperize], [m4_toupper(m4_bpatsubst([$1], [[^0-9a-zA-Z_]+], [_]))])
AC_DEFUN([DRIVER], [
    if test -z "$3"; then
        default=$HW_ENABLED_DEFAULT
    else
        default="$3"
    fi
    AC_ARG_ENABLE($2, AC_HELP_STRING([--enable-$2], [enable $1 support]),
        [m4_join([], [HW_], upperize([$2]))="$enableval"],
        [m4_join([], [HW_], upperize([$2]))=$default])
    dots=$(echo -n ".............................." | cut -c 1-$(expr 32 - $(echo -n $2|wc -c)))
    driver_summary="${driver_summary}  - $2${dots} \${m4_join([], [HW_], upperize([$2]))}@"
])

DRIVER([HT70], [ht70])
DRIVER([MedSys III], [medsys3])
DRIVER([Impact 731], [imp731])
DRIVER([DT], [dt], "$have_dt")
DRIVER([Measurement Corporation UL], [mccul], "$have_mccul")
DRIVER([BMP180 T/Pressure], [bmp180], "$have_bmp180")
DRIVER([Simulation], [simu], "$have_simu")
DRIVER([LabJack U3], [u3], no)
DRIVER([Propaq M], [propaqm]) # , "$have_propaqm" )

AC_ARG_ENABLE(libserialport,
    AC_HELP_STRING([--disable-libserialport],
    [disable libserialport support [default=detect]]))

AC_ARG_ENABLE(liblabjackusb,
    AC_HELP_STRING([--disable-liblabjackusb],
    [disable liblabjackusb support [default=detect]]))

#C_ARG_ENABLE(libusb,
#    AC_HELP_STRING([--disable-libusb],
#    [disable libusb support [default=detect]]))

# Language binding '--enable' options:

AC_ARG_ENABLE(bindings,
    AC_HELP_STRING([--enable-bindings],
    [build language bindings [default=yes]]),
    [BINDINGS_ALL="$enableval"], [BINDINGS_ALL="yes"])

AC_ARG_ENABLE(cxx,
    AC_HELP_STRING([--enable-cxx],
    [build C++ bindings [default=yes]]),
    [BINDINGS_CXX="$enableval"], [BINDINGS_CXX=$BINDINGS_ALL])

AC_ARG_ENABLE(python,
    AC_HELP_STRING([--enable-python],
    [build Python bindings [default=no]]),
    [BINDINGS_PYTHON="$enableval"], [BINDINGS_PYTHON=$BINDINGS_ALL])

# WLB--disable python
# BINDINGS_PYTHON="no"

AC_ARG_ENABLE(java,
    AC_HELP_STRING([--enable-java],
    [build Java bindings [default=yes]]),
    [BINDINGS_JAVA="$enableval"], [BINDINGS_JAVA=$BINDINGS_ALL])

AC_ARG_WITH(jni-include-path,
    AC_HELP_STRING([--with-jni-include-path=path],
    [specify include path for JNI [default=autodetect]]),
    [JNI_INCLUDE_DIRS="$withval"], [JNI_INCLUDE_DIRS=auto])

# Check if the C++ compiler supports the C++11 standard.

m4_ifdef([AX_CXX_COMPILE_STDCXX_11], [AX_CXX_COMPILE_STDCXX_11(,[optional])],
    [AC_MSG_NOTICE([Missing macro m4_toupper(aX_CXX_COMPILE_STDCXX_11), no C++11 check])])

if test "x$HAVE_CXX11" != "x1"; then
    BINDINGS_CXX="no"; cxx_msg="C++11 compiler required"
fi

# The C++ bindings use Doxygen to parse symbols.
AC_CHECK_PROG([HAVE_DOXYGEN], [doxygen], [yes])
if test "x$HAVE_DOXYGEN" != "xyes"; then
    BINDINGS_CXX="no"; cxx_msg="Doxygen required"
fi

# Python is needed for the C++ bindings.
AM_PATH_PYTHON([2.7], [HAVE_PYTHON="yes"],
    [HAVE_PYTHON="no"; BINDINGS_CXX="no"; cxx_msg="Python required"])

# The Python bindings need Python development files.
PKG_CHECK_MODULES([python], [python >= 2.7],
    [CXXFLAGS="$CXXFLAGS $python_CFLAGS";
    CXXLIBS="$CXXLIBS $python_LIBS"],
[PKG_CHECK_MODULES([python3], [python3 >= 3.0],
    [CXXFLAGS="$CXXFLAGS $python3_CFLAGS";
    CXXLIBS="$CXXLIBS $python3_LIBS"],
        [BINDINGS_PYTHON="no"; python_msg="Python headers required"])])

# The Python bindings need the setuptools Python module.
m4_ifdef([AX_PYTHON_MODULE], [AX_PYTHON_MODULE([setuptools])],
    # We'll let it go through even if the macro wasn't found, the Python
    # module may still be there.
    [HAVE_PYTHON_SETUPTOOLS="yes";
        AC_MSG_NOTICE([Missing macro m4_toupper(aX_PYTHON_MODULE), no setuptools check])]
)
if test "x$HAVE_PYMOD_SETUPTOOLS" != "xyes"; then
    BINDINGS_PYTHON="no"; python_msg="Python setuptools module required"
fi

# The Python and Java bindings use SWIG to generate code.
AC_CHECK_PROG([HAVE_SWIG], [swig], [yes])
if test "x$HAVE_SWIG" != "xyes"; then
    BINDINGS_PYTHON="no"; python_msg="SWIG required"
    BINDINGS_JAVA="no"; java_msg="SWIG required"
fi

# Checks for libraries.

case "$host" in
*mingw*)
    # We need to link against the Winsock2 library for TCP.
    LIBS="$LIBS -lws2_32";;
esac

# This variable collects the pkg-config names of all detected libs.
# It is then used to construct the "Requires.private:" field in the
# pista.pc file.
PISTA_PKGLIBS=""

#
# Everybody needs protobuf
#
# ...I need protobuf-c
#
# PKG_CHECK_MODULES([protobuf], [protobuf])

#
# propaq discovery needs avahi
#
## if enabled_propaq
PKG_CHECK_MODULES(
        [AVAHICLIENT], 
        [avahi-client >= 0.6 ], 
        [
            LIB_CFLAGS="$LIB_CFLAGS $AVAHICLIENT_CFLAGS";
            LIBS="$LIBS $AVAHICLIENT_LIBS";
            have_avahiclient="yes"; 
        ],
        [have_avahiclient="no"])
## fi

## HT70 needs XML decoding via expat
PKG_CHECK_MODULES(
        [EXPAT], 
        [expat >= 2.2 ], 
        [
            LIB_CFLAGS="$LIB_CFLAGS $EXPAT_CFLAGS";
            LIBS="$LIBS $EXPAT_LIBS";
            have_expat="yes"; 
        ],
        [have_expat="no"])

echo "if no avahiclient -- disable propaqm discovery"

if test "x$have_avahiclient" = "xno"; then
    echo "no client"
else
    # Define HAVE_AVAHICLIENT in config.h if we found libserialport.
    AC_DEFINE_UNQUOTED(HAVE_AVAHICLIENT, [1],
        [Specifies whether we have avahi client.])
fi
#
# sserial is only needed for some hardware drivers. Disable drivers if not found.
#
echo "testing libserialport"
if test "x$enable_libserialport" != "xno"; then
    PKG_CHECK_MODULES(
        [libserialport], 
        [libserialport >= 0.1.0],
        [
            have_libserialport="yes"; 
            LIB_CFLAGS="$LIB_CFLAGS $libserialport_CFLAGS";
            LIBS="$LIBS $libserialport_LIBS";
            PISTA_PKGLIBS="$PISTA_PKGLIBS libserialport"
        ],
        [have_libserialport="no"])
    if test "x$enable_libserialport$have_libserialport" = "xyesno"; then
        AC_MSG_ERROR([libserialport support requested, but it was not found.])
    fi
else
    have_libserialport="no"
fi

echo "if no libserialport -- disable some devices"

if test "x$have_libserialport" = "xno"; then
    HW_AGILENT_DMM="no"; HW_APPA_55II="no";
    HW_ATTEN_PPS3XXX="no"; HW_BRYMEN_DMM="no"; HW_CEM_DT_885X="no"
else
    # Define HAVE_LIBSERIALPORT in config.h if we found libserialport.
    AC_DEFINE_UNQUOTED(HAVE_LIBSERIALPORT, [1],
        [Specifies whether we have libserialport.])
fi

echo "testing libwebsockets"
#
# libwebsockets is needed for propaq-m.
#
if test "x$enable_libwebsockets" != "xno"; then
    PKG_CHECK_MODULES([libwebsockets], [libwebsockets >= 1.7.0 ],
        [have_libwebsockets="yes"; LIB_CFLAGS="$LIB_CFLAGS $libwebsockets_CFLAGS";
        LIBS="$LIBS $libwebsockets_LIBS";
        PISTA_PKGLIBS="$PISTA_PKGLIBS libwebsockets"],
        [have_libwebsockets="no"])
    if test "x$enable_libwebsockets$have_libwebsockets" = "xyesno"; then
        AC_MSG_ERROR([libwebsockets support requested, but it was not found.])
    fi
else
    have_libwebsockets="no"
fi

echo "have_libwebsockets=$have_libwebsockets"

if test "x$have_libwebsockets" = "xno"; then
    HW_PROPAQM="no"
else
    # Define HAVE_LIBWEBSOCKETS in config.h if we found libwebsockets.
    AC_DEFINE_UNQUOTED(HAVE_LIBWEBSOCKETS, [1],
        [Specifies whether we have libwebsockets.])
fi

echo "WLB FIXME: allow --enable-propaqm"
HW_PROPAQM="yes"

echo "if no websockets, then no propaq"
#
# yajl is needed for propaq-m.
#
if test "x$enable_yajl" != "xno"; then
    PKG_CHECK_MODULES([yajl], [yajl >= 2.1.0 ],
        [have_yajl="yes"; LIB_CFLAGS="$LIB_CFLAGS $yajl_CFLAGS";
        LIBS="$LIBS $yajl_LIBS";
        PISTA_PKGLIBS="$PISTA_PKGLIBS yajl"],
        [have_yajl="no"])
    if test "x$enable_yajl$have_yajl" = "xyesno"; then
        AC_MSG_ERROR([yajl support requested, but it was not found.])
    fi
else
    have_yajl="no"
fi

if test "x$have_yajl" = "xno"; then
    HW_PROPAQM="no";
else
    # Define HAVE_LIBYAJL in config.h if we found yajl.
    AC_DEFINE_UNQUOTED(HAVE_LIBYAJL, [1],
        [Specifies whether we have yajl.])
fi

#
#
# liblabjackusb is usef for HW_U3.  Disable if not found.
#
have_liblabjackusb="no"
if test "x$enable_liblabjackusb" != "xno"; then
	#
	# you want a compile test here...there is not package installed
	#
        have_liblabjackusb="yes";
		LIB_CFLAGS="$LIB_CFLAGS -I/usr/local/include"

	# wlb--PUT THIS BACK
        # LIBS="$LIBS -L/usr/local/lib -llabjackusb"

        # PISTA_PKGLIBS="$PISTA_PKGLIBS liblabjack"

    if test "x$enable_liblabjackusb$have_liblabjackusb" = "xyesno"; then
        AC_MSG_ERROR([liblabjackusb support requested, but it was not found.])
    fi
else
    have_liblabjackusb="no"
fi
if test "x$have_liblabjackusb" = "xno"; then
    HW_U3="no"; 
else
    # Define HAVE_LIBLABJACKUSB in config.h if we found liblabjackusb.
    AC_DEFINE_UNQUOTED(HAVE_LIBLABJACKUSB, [1],
        [Specifies whether we have liblabjackusb.])
fi

#
# boost asio. Disable if not found.
#
have_boost_asio="no"
if test "x$enable_boost_asio" != "xno"; then
	#
	# you want a compile test here...there is not package installed
	#
	AC_SUBST(BOOST_ASIO_LIB)

    if test "x$HAVE_BOOST_ASIO" = "xyes"; then
        AC_MSG_ERROR([boost asio support requested, but it was not found.])
    fi
else
    have_boost_asio="no"
fi

AC_SUBST(PISTA_PKGLIBS)

# Serial port helper code is only compiled in if libserialport was found.
AM_CONDITIONAL(HAVE_LIBSERIALPORT, test "x$have_libserialport" != xno)
AM_CONDITIONAL(HAVE_LIBLABJACKUSB, test "x$have_liblabjackusb" != xno)
AM_CONDITIONAL(NEED_ZEROMQ, test "x$have_zeromq" != xno)
AM_CONDITIONAL(HAVE_BOOST_ASIO, test "x$have_boost_asio" != xno)
AM_CONDITIONAL(HAVE_MCCUL, test "x$have_mccul" != xno)
AM_CONDITIONAL(HAVE_BMP180, test "x$have_bmp180" != xno)
AM_CONDITIONAL(HAVE_SIMU, test "x$have_simu" != xno)
AM_CONDITIONAL(HAVE_LIBWEBSOCKETS, test "x$have_libwebsockets" != xno)
AM_CONDITIONAL(HAVE_LIBYAJL, test "x$have_yajl" != xno)
AM_CONDITIONAL(HAVE_AVAHICLIENT, test "x$have_avahiclient" != xno)
AM_CONDITIONAL(HAVE_EXPAT, test "x$have_expat" != xno)

CFLAGS="$CFLAGS -Iinclude -I${srcdir}/include $LIB_CFLAGS"
CXXFLAGS="$CXXFLAGS -Iinclude -I${srcdir}/include -Ibindings/cxx -Ibindings/cxx/include -I${srcdir}/bindings/cxx/include $LIB_CFLAGS"

# Find Java compiler and JNI includes for Java bindings.
AC_CHECK_PROG([HAVE_JAVAC], [javac], [yes], [no])
if test "x$HAVE_JAVAC" = "xyes" && test "x$BINDINGS_JAVA" = "xyes"; then
    AC_PROG_JAVAC
    if test "x$JNI_INCLUDE_DIRS" = "xauto"; then
        if test "x$cross_compiling" = "xyes"; then
            JNI_INCLUDE_DIRS=
        else
            AC_JNI_INCLUDE_DIR
        fi
    fi
    for JNI_INCLUDE_DIR in $JNI_INCLUDE_DIRS; do
        CXXFLAGS="$CXXFLAGS -I$JNI_INCLUDE_DIR"
    done
    AC_LANG_PUSH([C++])
    AC_CHECK_HEADERS([jni.h], [], [BINDINGS_JAVA="no"; java_msg="Java JNI headers required"])
    AC_LANG_POP([C++])
else
    BINDINGS_JAVA="no"; java_msg="Java compiler required"
fi

# Python and Java bindings depend on C++ bindings.
if test "x$BINDINGS_CXX" != "xyes"; then
    BINDINGS_PYTHON="no"; python_msg="C++ bindings required"
    BINDINGS_JAVA="no"; java_msg="C++ bindings required"
fi

# Now set AM_CONDITIONALs and AC_DEFINEs for the enabled/disabled drivers.

AC_DEFUN([DRIVER2], [
    AM_CONDITIONAL($1, test "x$2" = "xyes")
    if test "x$2" = "xyes"; then AC_DEFINE($3, 1, [.]) fi
])

DRIVER2([HW_HT70], [$HW_HT70], [HAVE_HT70])
DRIVER2([HW_IMP731], [$HW_IMP731], [HAVE_IMP731])
DRIVER2([HW_MEDSYS3], [$HW_MEDSYS3], [HAVE_MEDSYS3])
DRIVER2([HW_U3], [$HW_U3], [HAVE_U3])
DRIVER2([HW_DT], [$HW_DT], [HAVE_DT])
DRIVER2([HW_SIMU], [$have_simu], [HAVE_SIMU])
DRIVER2([HW_BMP180], [$have_bmp180], [HAVE_BMP180])
DRIVER2([HW_MCCUL], [$have_mccul], [HAVE_MCCUL])
DRIVER2([HW_PROPAQM], [$HW_PROPAQM], [HAVE_PROPAQM])

AM_CONDITIONAL(BINDINGS_CXX, test x$BINDINGS_CXX = xyes)

AM_CONDITIONAL(BINDINGS_PYTHON, test x$BINDINGS_PYTHON = xyes)

AM_CONDITIONAL(BINDINGS_JAVA, test x$BINDINGS_JAVA = xyes)

# Checks for typedefs, structures, and compiler characteristics.
AC_C_BIGENDIAN

AC_SUBST(MAKEFLAGS, '--no-print-directory')
AC_SUBST(AM_LIBTOOLFLAGS, '--silent')

PISTA_PACKAGE_VERSION_MAJOR=pista_package_version_major
PISTA_PACKAGE_VERSION_MINOR=pista_package_version_minor
PISTA_PACKAGE_VERSION_MICRO=pista_package_version_micro
PISTA_PACKAGE_VERSION=pista_package_version

AC_SUBST(PISTA_PACKAGE_VERSION_MAJOR)
AC_SUBST(PISTA_PACKAGE_VERSION_MINOR)
AC_SUBST(PISTA_PACKAGE_VERSION_MICRO)
AC_SUBST(PISTA_PACKAGE_VERSION)

AC_CONFIG_HEADER([include/config.h])
AC_CONFIG_FILES([Makefile pista.pc bindings/cxx/libpistacxx.pc])
AC_OUTPUT

echo
echo "libpista configuration summary:"
echo
echo "  - Package version (major.minor.micro):    $PISTA_PACKAGE_VERSION"
echo "  - Library version (current:revision:age): $PISTA_LIB_VERSION"
echo "  - Prefix: $prefix"
echo "  - Building on: $build"
echo "  - Building for: $host"
echo
echo "Detected libraries:"
echo

# Note: This only works for libs with pkg-config integration.
for lib in "libserialport >= 0.1.0" \
    "libusb-1.0 >= 1.0.16" "libftdi >= 0.16" \
    "pygobject-3.0 >= 3.0.0" "check >= 0.9.4"  "libboostasio >= 1.0" \
    "liblabjackusb-1.0 >= 1.0.0" "libwebsockets >= 1.7.0" \
    "yajl >= 2.1.0" \
    "avahi-client >= 0.6" \
    "expat >= 2.2"
do
    optional="OPTIONAL"
    if test "x$lib" = "xglib-2.0 >= 2.32.0"; then optional="REQUIRED"; fi
    if test "x$lib" = "xlibzip >= 0.10"; then optional="REQUIRED"; fi
    if `$PKG_CONFIG --exists $lib`; then
        ver=`$PKG_CONFIG --modversion $lib`
        answer="yes ($ver)"
    else
        answer="no"
    fi
    echo "  - ($optional) $lib: $answer"
done

eval echo -e "@Enabled hardware drivers:@@${driver_summary}" | tr @ \\n

# Prepare final bindings report messages.
final_cxx=""
final_python=""
final_java=""
if test "$enable_bindings" = "no"; then
    final_cxx=" (disabled)"
    final_python=" (disabled)"
    final_java=" (disabled)"
else
    if test "$enable_cxx" = "no"; then
        final_cxx=" (disabled)"
    elif test "$BINDINGS_CXX" = "no"; then
        final_cxx=" ($cxx_msg)"
    fi
    if test "$enable_python" = "no"; then
        final_python=" (disabled)"
    elif test "$BINDINGS_PYTHON" = "no"; then
        final_python=" ($python_msg)"
    fi
    if test "$enable_java" = "no"; then
        final_java=" (disabled)"
    elif test "$BINDINGS_JAVA" = "no"; then
        final_java=" ($java_msg)"
    fi
fi

echo "Enabled optional transports:"
echo " - TCP............................. yes"
if test "x$have_rpc" = "x0"; then
echo " - RPC............................. no"
else
echo " - RPC............................. yes"
fi
echo " - serial.......................... $have_libserialport"
echo " - websockets...................... $have_libwebsockets"
echo " - avahiclient..................... $have_avahiclient"
echo

echo "Enabled language bindings:"
echo " - C++............................. $BINDINGS_CXX$final_cxx"
echo " - Python.......................... $BINDINGS_PYTHON$final_python"
echo " - Java............................ $BINDINGS_JAVA$final_java"
echo

