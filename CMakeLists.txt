cmake_minimum_required (VERSION 1.0)

# Sets PROJECT_NAME, PROJECT_SOURCE_DIR, AND PROJECT_BINARY_DIR
project (Tutorial)

# PROJECT_SOURCE_DIR is where the top level CMakeLists file is
# PROJECT_BINARY_DIR is where the build<cmake> command is being run from
# Set version number
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
# Set header directory
set (PROJECT_HEADERS "${PROJECT_SOURCE_DIR}/include")

#Change this when want to install in system
set (MAKE_INSTALL_DIR ${PROJECT_SOURCE_DIR})

# does this system provide the log and exp functions?
include (CheckFunctionExists)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

# configure a header file to pass some of the CMake settings
# to the source code

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
# This is essentially the -I flag
include_directories("${PROJECT_SOURCE_DIR}/include")

# should we use our own math functions?
option (USE_MYMATH 
        "Use tutorial provided math implementation" ON)

# should we use our own math functions?
option (INSTALL_GLOBAL
        "Flag on whether to install in /usr/include as opposed to the src code directories" OFF)

if (INSTALL_GLOBAL)
	set (MAKE_INSTALL_DIR "")
endif (INSTALL_GLOBAL)

# Links MathFunctions to executable we've defined TutorialConfig

# This configures the file, IMMEDIATELY, so do it after everything else it depends on is done
# Thanks for mentioning that tutorial. Fucking waste dude I swear
# This changes the variable names Tutorial_VERSION_MAJOR and minor in the file to the ones set above
configure_file (
  "${PROJECT_SOURCE_DIR}/src/TutorialConfig.h.in"
  "${PROJECT_HEADERS}/TutorialConfig.h"
  )


# add the MathFunctions library?
if (USE_MYMATH)
	# This will add a directory that has compilable code and another CMakeLists file
	include_directories("${PROJECT_SOURCE_DIR}/MathFunctions")
	# This will look for the cmakelists and build from there
	add_subdirectory("MathFunctions")

	set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)


add_executable(Tutorial main.cxx)
target_link_libraries (Tutorial MathFunctions)

# add the install targets
# This is only used when make install is called
# Adding source dir, if just include or bin will install in /usr/local/<dir>
install (TARGETS Tutorial DESTINATION "${MAKE_INSTALL_DIR}/bin")
install (FILES "${PROJECT_HEADERS}/TutorialConfig.h"
         DESTINATION "${MAKE_INSTALL_DIR}/include")


######
# Tests Segment
######

include(CTest)

# does the application run
add_test (TutorialRuns Tutorial 25)

# does it sqrt of 25
add_test (TutorialComp25 Tutorial 25)
set_tests_properties (TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

# does it handle negative numbers
add_test (TutorialNegative Tutorial -25)
set_tests_properties (TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is -nan")

# does it handle small numbers
add_test (TutorialSmall Tutorial 0.0001)
set_tests_properties (TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")

# does the usage message work?
add_test (TutorialUsage Tutorial)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

#define a macro to simplify adding tests, then use it
macro (do_test arg result)
  add_test (TutorialComp${arg} Tutorial ${arg})
  set_tests_properties (TutorialComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)
 
# do a bunch of result based tests
do_test (25 "25 is 5")
do_test (-25 "-25 is -nan")

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include (CPack)

# To run cpack use
# cpack --config CPackConfig.cmake
# That will make the tarball needed to build the project

# cpack --config CPackConfig.cmake
# cpack --config CPackSourceConfig.cmake

# MAKE SURE YOU CLEAN build/ YOU CUNT