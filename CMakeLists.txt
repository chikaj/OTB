if(WIN32)
  cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)
else()
  cmake_minimum_required(VERSION 2.8.6 FATAL_ERROR)
endif()

foreach(p
    CMP0025 # CMake 3.0
    CMP0042 # CMake 3.0 
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

# CMP0046 : from CMake 3.0, old behaviour is more convenient
if(POLICY CMP0046)
  cmake_policy(SET CMP0046 OLD)
endif()

# TODO Check if OTB cmake is compatible with CMP0054 NEW policy
# CMP0054 : New policy introduce in CMake 3.1, keep old behaviour for now
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 OLD)
endif()

project(OTB)

include(CMakeDependentOption)
#
# use ExternalProject
include(ExternalProject)

if( CMAKE_HOST_WIN32 )

  string( LENGTH "${CMAKE_CURRENT_SOURCE_DIR}" n )
  if( n GREATER 50 )
    message(
      FATAL_ERROR
      "OTB source code directory path length is too long (${n} > 50)."
      "Please move the OTB source code directory to a directory with a shorter path."
      )
  endif()

  string( LENGTH "${CMAKE_CURRENT_BINARY_DIR}" n )
  if( n GREATER 50 )
    message(
      FATAL_ERROR
      "OTB build directory path length is too long (${n} > 50)."
      "Please set the OTB build directory to a directory with a shorter path."
      )
  endif()

endif()

set(CMAKE_MODULE_PATH ${OTB_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})
include (SourceStatus)
include(PreventInSourceBuilds)
include(PreventInBuildInstalls)
include(OTBModuleMacros)
include(OTBModuleRemote)

set(main_project_name ${_OTBModuleMacros_DEFAULT_LABEL})

#-----------------------------------------------------------------------------
# OTB version number.
set(OTB_VERSION_MAJOR "5")
set(OTB_VERSION_MINOR "0")
set(OTB_VERSION_PATCH "0")
set(OTB_VERSION_STRING "${OTB_VERSION_MAJOR}.${OTB_VERSION_MINOR}.${OTB_VERSION_PATCH}")

if(NOT OTB_INSTALL_RUNTIME_DIR)
  set(OTB_INSTALL_RUNTIME_DIR bin)
endif()
if(NOT OTB_INSTALL_LIBRARY_DIR)
  set(OTB_INSTALL_LIBRARY_DIR lib)
endif()
if(NOT OTB_INSTALL_ARCHIVE_DIR)
  set(OTB_INSTALL_ARCHIVE_DIR lib)
endif()
if(NOT OTB_INSTALL_INCLUDE_DIR)
  set(OTB_INSTALL_INCLUDE_DIR include/OTB-${OTB_VERSION_MAJOR}.${OTB_VERSION_MINOR})
endif()
if(NOT OTB_INSTALL_APP_DIR)
  set(OTB_INSTALL_APP_DIR "lib/otb/applications")
endif()
if(NOT OTB_INSTALL_PYTHON_DIR)
  set(OTB_INSTALL_PYTHON_DIR "lib/otb/python")
endif()
if(NOT OTB_INSTALL_JAVA_DIR)
  set(OTB_INSTALL_JAVA_DIR "lib/otb/java")
endif()
if(NOT OTB_INSTALL_DATA_DIR)
  set(OTB_INSTALL_DATA_DIR share/OTB-${OTB_VERSION_MAJOR}.${OTB_VERSION_MINOR})
endif()
if(NOT OTB_INSTALL_DOC_DIR)
  set(OTB_INSTALL_DOC_DIR share/doc/OTB-${OTB_VERSION_MAJOR}.${OTB_VERSION_MINOR})
endif()
if(NOT OTB_INSTALL_PACKAGE_DIR)
  set(OTB_INSTALL_PACKAGE_DIR "${OTB_INSTALL_LIBRARY_DIR}/cmake/OTB-${OTB_VERSION_MAJOR}.${OTB_VERSION_MINOR}")
endif()

# Override CMake's built-in add_* commands: assign LABELS to tests and targets
# automatically. Depends on the CMake variable otb-module being set to the
# "current" module when add_* is called.
macro(verify_otb_module_is_set)
  if("" STREQUAL "${otb-module}")
    message(FATAL_ERROR "CMake variable otb-module is not set")
  endif()
endmacro()

#-----------------------------------------------------------------------------
# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


#-----------------------------------------------------------------------------
# Enable running cppcheck for each module on its source and test directories.
option(OTB_CPPCHECK_TEST "Run cppcheck for static code analysis" OFF)
mark_as_advanced(OTB_CPPCHECK_TEST)

#-----------------------------------------------------------------------------
# Forbid downloading resources from the network during a build. This helps
# when building on systems without network connectivity to determine which
# resources much be obtained manually and made available to the build.
option(OTB_FORBID_DOWNLOADS "Do not download source code or data from the network" OFF)
mark_as_advanced(OTB_FORBID_DOWNLOADS)
macro(otb_download_attempt_check _name)
  if(OTB_FORBID_DOWNLOADS)
    message(SEND_ERROR "Attempted to download ${_name} when OTB_FORBID_DOWNLOADS is ON")
  endif()
endmacro()

# TODO : handle shared libs on windows
option(BUILD_SHARED_LIBS "Build OTB with shared libraries." ON)
set(OTB_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

#-----------------------------------------------------------------------------
# Option to activate deprecated classes
option(OTB_USE_DEPRECATED "Turn on the use and test of deprecated classes" OFF)
mark_as_advanced(OTB_USE_DEPRECATED)

#-----------------------------------------------------------------------------
# SHOW_ALL_MSG_DEBUG option
option(OTB_SHOW_ALL_MSG_DEBUG "Show all debug messages (very verbose)" OFF)
mark_as_advanced(OTB_SHOW_ALL_MSG_DEBUG)

include(OTBSetStandardCompilerFlags)
#---------------------------------------------------------------
# run try compiles and tests for OTB

# TODO check if we need this
#include(otbTestFriendTemplatedFunction)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OTB_REQUIRED_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OTB_REQUIRED_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OTB_REQUIRED_LINK_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${OTB_REQUIRED_LINK_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${OTB_REQUIRED_LINK_FLAGS}")

# detect some C++11 keywords
include(OTBCheckCpp11Keywords)

# TODO BUILD_TESTING is created by default by CTest.cmake, and is ON by default.
option(BUILD_TESTING "Build the testing tree." OFF)

include(CTest)

include( CppcheckTargets )

# Setup build locations.
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OTB_BINARY_DIR}/bin)
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OTB_BINARY_DIR}/lib)
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OTB_BINARY_DIR}/lib)
endif()
set(OTB_MODULES_DIR "${OTB_BINARY_DIR}/${OTB_INSTALL_PACKAGE_DIR}/Modules")

#-----------------------------------------------------------------------------
# OTB uses KWStyle for checking the coding style
#include(${OTB_SOURCE_DIR}/Utilities/KWStyle/KWStyle.cmake)

#-----------------------------------------------------------------------------
# By default, OTB does not build the Examples that are illustrated in the Software Guide
option(BUILD_EXAMPLES "Build the Examples directory." OFF)

#----------------------------------------------------------------------------
set(OTB_TEST_OUTPUT_DIR "${OTB_BINARY_DIR}/Testing/Temporary")

#-----------------------------------------------------------------------------
# Configure the default OTB_DATA_ROOT for the location of OTB Data.
find_path(OTB_DATA_ROOT
  NAMES README-OTB-Data
  HINTS $ENV{OTB_DATA_ROOT} ${OTB_SOURCE_DIR}/../OTB-Data
)
mark_as_advanced(OTB_DATA_ROOT)

option(OTB_DATA_USE_LARGEINPUT "Use Large inputs images test." OFF)
mark_as_advanced(OTB_DATA_USE_LARGEINPUT)
if(OTB_DATA_USE_LARGEINPUT)
  find_path(OTB_DATA_LARGEINPUT_ROOT
    NAMES OTBData.readme
    HINTS $ENV{OTB_DATA_LARGEINPUT_ROOT}
  )
  mark_as_advanced(OTB_DATA_LARGEINPUT_ROOT)
endif()

#Generate cmake variables with a set of largeinput data used in tests
include(OTBManageLargeInputPaths)

set(BASELINE       ${OTB_DATA_ROOT}/Baseline/OTB/Images)
set(BASELINE_FILES ${OTB_DATA_ROOT}/Baseline/OTB/Files)
set(INPUTDATA      ${OTB_DATA_ROOT}/Input)
set(TEMP           ${OTB_BINARY_DIR}/Testing/Temporary)
set(EXAMPLEDATA    ${OTB_DATA_ROOT}/Examples)
set(OTBAPP_BASELINE       ${OTB_DATA_ROOT}/Baseline/OTB-Applications/Images)
set(OTBAPP_BASELINE_FILES ${OTB_DATA_ROOT}/Baseline/OTB-Applications/Files)

set(NOTOL      0.0)
set(EPSILON_1  0.1)
set(EPSILON_2  0.01)
set(EPSILON_3  0.001)
set(EPSILON_4  0.0001)
set(EPSILON_5  0.00001)
set(EPSILON_6  0.000001)
set(EPSILON_7  0.0000001)
set(EPSILON_8  0.00000001)
set(EPSILON_9  0.000000001)
set(EPSILON_10 0.0000000001)
set(EPSILON_11 0.00000000001)
set(EPSILON_12 0.000000000001)
set(EPSILON_13 0.0000000000001)
set(EPSILON_14 0.00000000000001)
set(EPSILON_15 0.000000000000001)

#-----------------------------------------------------------------------------
# OTB wrapper for add_test that automatically sets the test's LABELS property
# to the value of its containing module.
#
function(otb_add_test)
  set(largeinput_regex "LARGEINPUT{([^;{}\r\n]*)}")
  
  set(_depends_on_largeinput OFF)
  foreach(arg IN LISTS ARGN)
     if("x${arg}" MATCHES "${largeinput_regex}")
       string(REGEX REPLACE "${largeinput_regex}" "\\1" largeinput_relative_path "${arg}")
       set(_fullpath "${OTB_DATA_LARGEINPUT_ROOT}/${largeinput_relative_path}")
       list(APPEND _out_arg ${_fullpath})
       set(_depends_on_largeinput ON)
     else()
       list(APPEND _out_arg ${arg})
     endif()
  endforeach()

  if (_depends_on_largeinput AND NOT OTB_DATA_USE_LARGEINPUT)
    return()
  endif()

  add_test(${_out_arg})

  if("NAME" STREQUAL "${ARGV0}")
    set(_iat_testname ${ARGV1})
  else()
    set(_iat_testname ${ARGV0})
  endif()

  if(otb-module)
    set(_label ${otb-module})
  else()
    set(_label ${main_project_name})
  endif()

  set_property(TEST ${_iat_testname} PROPERTY LABELS ${_label})

endfunction()

#-----------------------------------------------------------------------------
# OTB function to ignore a test
#
function(otb_tests_ignore)
  set_property(GLOBAL APPEND PROPERTY CTEST_CUSTOM_TESTS_IGNORE ${ARGN})
endfunction()

#-----------------------------------------------------------------------------
# OTB function to ignore a test during MemCheck
#
function(otb_memcheck_ignore)
  set_property(GLOBAL APPEND PROPERTY CTEST_CUSTOM_MEMCHECK_IGNORE ${ARGN})
endfunction()

# Location of OTB Example Data.
# set(OTB_EXAMPLE_DATA_ROOT "${OTB_SOURCE_DIR}/Examples/Data")

#----------------------------------------------------------------------
# Make sure remote modules are downloaded before sorting out the module
# dependencies.
add_subdirectory(Modules/Remote)

# Enable modules according to user inputs and the module dependency DAG.
include(OTBModuleEnablement)

#----------------------------------------------------------------------
# Generate OTBConfig.cmake for the build tree.
set(OTB_CONFIG_CODE "
set(OTB_MODULES_DIR \"${OTB_MODULES_DIR}\")")
set(OTB_USE_FILE "${OTB_SOURCE_DIR}/CMake/UseOTB.cmake")
set(OTB_CONFIG_TARGETS_CONDITION " AND NOT OTB_BINARY_DIR")
set(OTB_CONFIG_TARGETS_FILE "${OTB_BINARY_DIR}/OTBTargets.cmake")
set(OTB_CONFIG_MODULE_API_FILE "${OTB_SOURCE_DIR}/CMake/OTBModuleAPI.cmake")
set(OTB_CONFIG_APPLI_MACROS_FILE "${OTB_SOURCE_DIR}/CMake/OTBApplicationMacros.cmake")
configure_file(CMake/OTBConfig.cmake.in OTBConfig.cmake @ONLY)

# Generate OTBConfig.cmake for the install tree.
set(OTB_CONFIG_CODE "
# Compute the installation prefix from this OTBConfig.cmake file location.
get_filename_component(OTB_INSTALL_PREFIX \"\${CMAKE_CURRENT_LIST_FILE}\" PATH)")
# Construct the proper number of get_filename_component(... PATH)
# calls to compute the installation prefix.
string(REGEX REPLACE "/" ";" _count "${OTB_INSTALL_PACKAGE_DIR}")
foreach(p ${_count})
  set(OTB_CONFIG_CODE "${OTB_CONFIG_CODE}
get_filename_component(OTB_INSTALL_PREFIX \"\${OTB_INSTALL_PREFIX}\" PATH)")
endforeach()
set(OTB_CONFIG_CODE "${OTB_CONFIG_CODE}
set(OTB_MODULES_DIR \"\${OTB_INSTALL_PREFIX}/${OTB_INSTALL_PACKAGE_DIR}/Modules\")")
set(OTB_USE_FILE "\${OTB_INSTALL_PREFIX}/${OTB_INSTALL_PACKAGE_DIR}/UseOTB.cmake")
set(OTB_CONFIG_TARGETS_CONDITION "")
set(OTB_CONFIG_TARGETS_FILE "\${OTB_INSTALL_PREFIX}/${OTB_INSTALL_PACKAGE_DIR}/OTBTargets.cmake")
set(OTB_CONFIG_MODULE_API_FILE "\${OTB_INSTALL_PREFIX}/${OTB_INSTALL_PACKAGE_DIR}/OTBModuleAPI.cmake")
set(OTB_CONFIG_APPLI_MACROS_FILE "\${OTB_INSTALL_PREFIX}/${OTB_INSTALL_PACKAGE_DIR}/OTBApplicationMacros.cmake")

configure_file(CMake/OTBConfig.cmake.in CMakeFiles/OTBConfig.cmake @ONLY)

# TODO : port unscrustify scripts from ITK to OTB ?
# #----------------------------------------------------------------------------
# # Configure maintenance scripts
# configure_file(Utilities/Maintenance/doSingleKWStyleUncrustifyFix.sh.in
#   Utilities/Maintenance/doSingleKWStyleUncrustifyFix.sh @ONLY)

#-----------------------------------------------------------------------------
configure_file(CMake/OTBConfigVersion.cmake.in OTBConfigVersion.cmake @ONLY)

install(FILES ${OTB_BINARY_DIR}/CMakeFiles/OTBConfig.cmake
              ${OTB_BINARY_DIR}/OTBConfigVersion.cmake
              CMake/OTBApplicationMacros.cmake
              CMake/OTBModuleAPI.cmake
              CMake/UseOTB.cmake
  DESTINATION ${OTB_INSTALL_PACKAGE_DIR}
  COMPONENT Development)
get_property(OTBTargets_MODULES GLOBAL PROPERTY OTBTargets_MODULES)
if(OTBTargets_MODULES)
  install(EXPORT OTBTargets DESTINATION ${OTB_INSTALL_PACKAGE_DIR}
          COMPONENT Development)
else()
  set(CMAKE_CONFIGURABLE_FILE_CONTENT "# No targets!")
  configure_file(${CMAKE_ROOT}/Modules/CMakeConfigurableFile.in
                 ${OTB_BINARY_DIR}/CMakeFiles/OTBTargets.cmake @ONLY)
  install(FILES ${OTB_BINARY_DIR}/CMakeFiles/OTBTargets.cmake
          DESTINATION ${OTB_INSTALL_PACKAGE_DIR} COMPONENT Development)
endif()

# install FindXXX.cmake
file(GLOB OTB_FIND_PACKAGE_SCRIPTS CMake/Find*.cmake)
install(FILES ${OTB_FIND_PACKAGE_SCRIPTS} DESTINATION ${OTB_INSTALL_PACKAGE_DIR} COMPONENT Development)

# TODO : install release notes, copyright notice, ...
# install(FILES "LICENSE" "NOTICE" "README.txt" DESTINATION ${OTB_INSTALL_DOC_DIR} COMPONENT Runtime)
install(FILES "LICENSE" DESTINATION ${OTB_INSTALL_DOC_DIR} COMPONENT Runtime)

if(BUILD_TESTING)
  add_subdirectory(Utilities/InstallTest)
endif()
#-----------------------------------------------------------------------------
# The subdirectories added below this line should use only the public
# interface with find_package(ITK). Set ITK_DIR to use this ITK build.
set(OTB_DIR "${OTB_BINARY_DIR}")

if(BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif()

#----------------------------------------------------------------------
# Provide an option for generating documentation.
add_subdirectory(Utilities/Doxygen)

# TODO cleanup
# Create target to download data from the OTBData group. This must come after
# all tests have been added that reference the group, so we put it last.
