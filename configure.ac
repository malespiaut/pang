# Process this file with autoconf to produce a configure script.
# $Id$
AC_INIT(README)

# Detect the canonical host and target build environment
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# Setup for automake
PROJ_NAME=ppang
PROJ_VERSION=1.1.1
AM_INIT_AUTOMAKE($PROJ_NAME, $PROJ_VERSION)

# Check for tools
AC_PROG_CC
AC_PROG_CXX

# Check for compiler environment
AC_C_CONST

# Figure out which math and OpenGL libraries to use
case "$target" in
    *-*-cygwin* | *-*-mingw32*)
        MATHLIB=""
        SYS_GL_LIBS="-lopengl32"
        ;;
    *-*-beos* | *-*-darwin*)
        MATHLIB=""
        SYS_GL_LIBS="-lGL"
        ;;
    *-*-aix*)
        if test x$ac_cv_prog_gcc = xyes; then
            CFLAGS="-mthreads"
        fi
        ;;
    *)
        MATHLIB="-lm"
        AC_PATH_X
        AC_PATH_XTRA
        if test x$have_x = xyes; then
            CFLAGS="$CFLAGS $X_CFLAGS"
            SYS_GL_LIBS="$X_LIBS -lGL"
        else
            SYS_GL_LIBS="-lGL"
        fi
        ;;
esac
AC_SUBST(MATHLIB)

# Check for SDL
SDL_VERSION=1.1.8
AM_PATH_SDL($SDL_VERSION, :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))
#CFLAGS="$CFLAGS $SDL_CFLAGS -WALL -pedantic -ggdb"
CFLAGS="$CFLAGS $SDL_CFLAGS -Wall"
CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"


# Optionally check for libraries too

AC_ARG_ENABLE(debug,
     [  --enable-debug	Turn on debugging],
     [case "${enableval}" in
       yes) debug=true ;;
       no)  debug=false ;;
       *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
     esac],[debug=false])
     AM_CONDITIONAL(DEBUG, test x$debug = xtrue)

# compile pc version
AC_ARG_ENABLE(pc,
[  --enable-pc          Build the PC version [default=yes]],
              , enable_pc=yes)
if test x$enable_pc = xyes; then
    CFLAGS="$CFLAGS -DPC_VERSION"
fi

# compile for the gp2x
AC_ARG_ENABLE(gp2x,
[  --enable-gp2x          Build the gp2x version [default=no]],
              , enable_gp2x=no)
if test x$enable_gp2x = xyes; then
    CFLAGS="$CFLAGS -DGP2X_VERSION -DRES320X240"
fi

# disable sound
AC_ARG_ENABLE(sound,
[  --enable-sound          Build with sound [default=yes]],
              , disable_sound=no)
if test x$enable_sound == xno; then
    CFLAGS="$CFLAGS -DNO_SOUND"
fi

# compile for the testing the 320x240 resolution
AC_ARG_ENABLE(320x240,
[  --enable-320x240          Test the 320x240 resolution [default=no]],
              , enable_320x240=no)
if test x$enable_320x240 = xyes; then
    CFLAGS="$CFLAGS -DRES320X240"
fi

# compile static
AC_ARG_ENABLE(static,
[  --enable-static          Build the static version [default=no]],
              , enable_static=no)
if test x$enable_static = xyes; then
    CFLAGS="$CFLAGS -static"
fi


# Finally create all the generated files
AC_OUTPUT(Makefile src/Makefile)

echo ""
echo "Features:"
echo "========="
echo " 320x240 Resolution:    $enable_320x240"
echo " GP2X Build (+320x240): $enable_gp2x"
echo " Static Build:          $enable_static"
echo ""
