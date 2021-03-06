###########################################################################
# Prelude.
###########################################################################
AC_INIT([IBAMR],[171104],[boyceg@gmail.com],[IBAMR],[https://ibamr.github.io])
AC_PREREQ([2.69])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADER([config/IBAMR_config.h.tmp])
AX_PREFIX_CONFIG_H([config/IBAMR_config.h],[IBAMR],[config/IBAMR_config.h.tmp])
AM_INIT_AUTOMAKE([1.12 -Wall -Werror dist-bzip2 foreign -Wno-extra-portability subdir-objects])
AM_SILENT_RULES([yes])
AM_MAINTAINER_MODE([disable])
AC_LANG(C++)
dnl libMesh will automatically detect and use C++14 features if they are
dnl available by default (e.g., with GCC 6.0 and newer). Ensure that we have the
dnl same version flag by using exactly the same macro setup as libMesh:
dnl
dnl (this variable is set up by libMesh)
enablecxx11=yes
AX_CXX_COMPILE_STDCXX_11([],[mandatory])

###########################################################################
# Checks for programs.
###########################################################################
AC_ARG_VAR(LDFLAGS,[linker flags, e.g. -L<lib dir> if you have libraries in a nonstandard directory <lib dir>])
AC_ARG_VAR(LIBS,[linker commands, e.g. -l<lib> if you require a nonstandard library <lib>])
AC_ARG_VAR(FCLIBS,[linker flags and commands, e.g. -L<lib dir> and -l<lib> for the "Fortran intrinsic and run-time libraries" that are required to successfully link a Fortran program or shared library])
AC_PROG_CC		# Check for a C compiler.
AC_PROG_CPP		# Check for a C preprocessor.
AC_PROG_CXX		# Check for a C++ compiler.
AC_PROG_CXXCPP		# Check for a C++ preprocessor.
AC_PROG_FC		# Check for a Fortran compiler.
AC_FC_LIBRARY_LDFLAGS	# Determine the linker flags for the Fortran intrinsic and runtime libraries.
AC_FC_WRAPPERS		# Determine the form of the symbol name mangling used by the Fortran compiler and setup wrappers to perform the name mangling.
F77="$FC"		# Set F77, FFLAGS, and FLIBS to avoid needing to call AC_PROG_F77.
FFLAGS="$FCFLAGS"
FLIBS="$FCLIBS"
AC_FC_SRCEXT(f)
AC_SUBST(F77)
AC_SUBST(FFLAGS)
AC_SUBST(FLIBS)
AX_PROG_CC_MPI		# Check for an MPI C compiler wrapper and use it as the default C compiler.
AX_PROG_CXX_MPI		# Check for an MPI C++ compiler wrapper and use it as the default C++ compiler.
AC_HEADER_MAJOR
AC_HEADER_STDC
LT_INIT
AC_LIB_PROG_LD_GNU
AC_ARG_WITH([M4],
  AS_HELP_STRING([--with-M4=ARG],[manually set M4 to ARG]))
AC_CHECK_PROGS(M4, $with_M4 gm4 m4,,)
if test -z "$M4" ; then
  AC_MSG_ERROR([m4 preprocessor not found, specify via --with-M4=ARG])
fi
AC_PROG_GREP
AC_PROG_SED
CHECK_BUILTIN_EXPECT
CHECK_BUILTIN_PREFETCH

###########################################################################
# Version information (requires sed).
###########################################################################
dnl Since this is an M4 script we must use the quadrigraphs @<:@ and @:>@ for
dnl brackets, i.e., for [ and ]
ibamr_version_major=$($SED "s/^\(@<:@0-9@:>@\+\)\..*/\1/" "$srcdir/VERSION")
ibamr_version_minor=$($SED "s/^@<:@^.@:>@\+\.\(@<:@0-9@:>@\+\)\.@<:@0-9@:>@\+.*/\1/" "$srcdir/VERSION")
ibamr_version_subminor=$($SED "s/^@<:@^.@:>@\+\.@<:@^.@:>@\+\.\(@<:@0-9@:>@\+\).*/\1/" "$srcdir/VERSION")
AC_DEFINE_UNQUOTED(VERSION_MAJOR, $ibamr_version_major, [Major version of IBAMR.])
AC_DEFINE_UNQUOTED(VERSION_MINOR, $ibamr_version_minor, [Minor version of IBAMR.])
AC_DEFINE_UNQUOTED(VERSION_SUBMINOR, $ibamr_version_subminor, [Subminor version of IBAMR.])

dnl We have to use a funny name for the key to guarantee that it comes after
dnl IBAMR_VERSION_SUBMINOR.
dnl
dnl TODO: Our code ignores backslashes when placing ifdef/endif guards around
dnl individual macros: i.e., autoheader writes
dnl     #define IBAMR_VERSION_GTE(...) ... \
dnl     #endif
dnl     ..... \
dnl     .....
dnl
dnl which doesn't make any sense. Get around this by just putting everything on
dnl one line. It is probably possible to fix this by editing
dnl m4/ax_prefix_config_h.m4, circa line 173.
AH_VERBATIM(VERSION_T_CHECK, [/* Version check macro. */
#define VERSION_GTE(major, minor, subminor) ((IBAMR_VERSION_MAJOR*10000 + IBAMR_VERSION_MINOR*100 + IBAMR_VERSION_SUBMINOR) >= (major)*10000 + (minor)*100 + (subminor))])



###########################################################################
# Checks for optional and required third-party libraries.
###########################################################################
PACKAGE_INITIALIZE_ENVIRONMENT
echo
echo "=================================="
echo "Configuring required package Boost"
echo "=================================="
AC_MSG_NOTICE([first check for a system Boost library; if not found, revert to bundled Boost library])
BOOST_REQUIRE([1.57.0],[
  AC_MSG_WARN([could not find system Boost library, using bundled Boost library])
  USING_BUNDLED_BOOST=yes])
CONFIGURE_BOOST("$ABSOLUTE_SRCDIR/ibtk/contrib/boost","\$(abs_top_builddir)/ibtk/contrib/boost")
CONFIGURE_LIBMESH
CONFIGURE_EIGEN("$ABSOLUTE_SRCDIR/ibtk/contrib/eigen","\$(abs_top_builddir)/ibtk/contrib/eigen")
CONFIGURE_HDF5
CONFIGURE_HYPRE
CONFIGURE_MUPARSER("$ABSOLUTE_SRCDIR/ibtk/contrib/muparser","\$(abs_top_builddir)/ibtk/contrib/muparser")
CONFIGURE_PETSC
CONFIGURE_SAMRAI
CONFIGURE_SILO
CONFIGURE_GSL
CONFIGURE_GTEST
PACKAGE_SETUP_ENVIRONMENT
LIBS="$LIBS $PACKAGE_CONTRIB_LIBS"

AC_SUBST(MPIEXEC)
AC_SUBST(NUMDIFF)

###########################################################################
# Output files.
###########################################################################
echo
echo "================"
echo "Outputting files"
echo "================"
AC_CONFIG_FILES([
  Makefile
  config/make.inc
  examples/Makefile
  examples/CIB/Makefile
  examples/CIB/ex0/Makefile
  examples/CIB/ex1/Makefile
  examples/CIB/ex2/Makefile
  examples/CIB/ex3/Makefile
  examples/CIB/ex4/Makefile
  examples/CIBFE/Makefile
  examples/CIBFE/ex0/Makefile
  examples/CIBFE/ex1/Makefile
  examples/ConstraintIB/Makefile
  examples/ConstraintIB/eel2d/Makefile
  examples/ConstraintIB/eel3d/Makefile
  examples/ConstraintIB/falling_sphere/Makefile
  examples/ConstraintIB/flow_past_cylinder/Makefile
  examples/ConstraintIB/flow_past_cylinder_HF/Makefile
  examples/ConstraintIB/impulsively_started_cylinder/Makefile
  examples/ConstraintIB/knifefish/Makefile
  examples/ConstraintIB/moving_plate/Makefile
  examples/ConstraintIB/oscillating_rigid_cylinder/Makefile
  examples/ConstraintIB/stokes_first_problem/Makefile
  examples/IB/Makefile
  examples/IB/explicit/Makefile
  examples/IB/explicit/ex0/Makefile
  examples/IB/explicit/ex1/Makefile
  examples/IB/explicit/ex2/Makefile
  examples/IB/explicit/ex3/Makefile
  examples/IB/explicit/ex4/Makefile
  examples/IB/explicit/ex5/Makefile
  examples/IB/explicit/ex6/Makefile
  examples/IBFE/Makefile
  examples/IBFE/explicit/Makefile
  examples/IBFE/explicit/ex0/Makefile
  examples/IBFE/explicit/ex1/Makefile
  examples/IBFE/explicit/ex2/Makefile
  examples/IBFE/explicit/ex3/Makefile
  examples/IBFE/explicit/ex4/Makefile
  examples/IBFE/explicit/ex5/Makefile
  examples/IBFE/explicit/ex6/Makefile
  examples/IBFE/explicit/ex7/Makefile
  examples/IBFE/explicit/ex8/Makefile
  examples/IBFE/explicit/ex9/Makefile
  examples/IBFE/explicit/ex10/Makefile
  examples/IBFE/explicit/ex11/Makefile
  examples/IMP/Makefile
  examples/IMP/explicit/Makefile
  examples/IMP/explicit/ex0/Makefile
  examples/adv_diff/Makefile
  examples/adv_diff/ex0/Makefile
  examples/adv_diff/ex1/Makefile
  examples/adv_diff/ex2/Makefile
  examples/advect/Makefile
  examples/level_set/Makefile
  examples/level_set/ex0/Makefile
  examples/level_set/ex1/Makefile
  examples/multiphase_flow/Makefile
  examples/multiphase_flow/ex0/Makefile
  examples/multiphase_flow/ex1/Makefile
  examples/multiphase_flow/ex2/Makefile
  examples/multiphase_flow/ex3/Makefile
  examples/multiphase_flow/ex4/Makefile
  examples/multiphase_flow/ex5/Makefile
  examples/multiphase_flow/ex6/Makefile
  examples/multiphase_flow/ex7/Makefile
  examples/multiphase_flow/ex8/Makefile
  examples/multiphase_flow/ex9/Makefile
  examples/navier_stokes/Makefile
  examples/navier_stokes/ex0/Makefile
  examples/navier_stokes/ex1/Makefile
  examples/navier_stokes/ex2/Makefile
  examples/navier_stokes/ex3/Makefile
  examples/navier_stokes/ex4/Makefile
  examples/navier_stokes/ex5/Makefile
  examples/navier_stokes/ex6/Makefile
  examples/vc_navier_stokes/Makefile
  examples/vc_navier_stokes/ex0/Makefile
  examples/vc_navier_stokes/ex1/Makefile
  examples/vc_navier_stokes/ex2/Makefile
  lib/Makefile
  src/Makefile
  src/fortran/Makefile
  src/IB/Makefile
  src/adv_diff/Makefile
  src/adv_diff/fortran/Makefile
  src/advect/Makefile
  src/advect/fortran/Makefile
  src/level_set/Makefile
  src/level_set/fortran/Makefile
  src/navier_stokes/Makefile
  src/navier_stokes/fortran/Makefile
  src/utilities/Makefile
  src/tools/Makefile
  tests/Makefile
  tests/IBFE/Makefile
  tests/IBTK/Makefile
  tests/multiphase_flow/Makefile
])
AC_CONFIG_SUBDIRS([ibtk])
AC_OUTPUT
echo
echo "===================================================================="
echo "===================================================================="
echo
AC_MSG_NOTICE([IBAMR appears to have been configured successfully.  Now:

   make lib        Build the IBAMR library and its supporting IBTK library
   make examples   Build all of the IBAMR and IBTK example programs

Note that the IBAMR and IBTK example programs are not run by "make examples".
To run the examples, e.g.,

   make examples
   cd examples/IB/explicit/ex0
   ./main2d input2d

You may also build and run individual example programs, e.g., via

   cd examples/IB/explicit/ex0
   make examples
   ./main2d input2d])
