# The name of our project is "DGtal". CMakeLists files in this
# project can refer to the root source directory of the project as
# ${DGTAL_SOURCE_DIR} and to the root binary directory of the
# project as ${DGTAL_BINARY_DIR}.

# -----------------------------------------------------------------------------
# Project definition
# -----------------------------------------------------------------------------
project (DGtal)
cmake_minimum_required (VERSION 2.6) 

# -----------------------------------------------------------------------------
# Display some information
# -----------------------------------------------------------------------------
message(STATUS "-------------------------------------------------------------------------------" )
message(STATUS "Source DIR is ${PROJECT_SOURCE_DIR}")
message(STATUS "Binary DIR is ${PROJECT_BINARY_DIR}")
message(STATUS "Build type is ${CMAKE_BUILD_TYPE}")
message(STATUS "Installation prefix directory is " ${CMAKE_INSTALL_PREFIX})
message(STATUS "Host system is " ${CMAKE_HOST_SYSTEM} " with processor " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "Target system is " ${CMAKE_SYSTEM} " with processor " ${CMAKE_SYSTEM_PROCESSOR})

# -----------------------------------------------------------------------------
# Define variables and cmake parameters
# -----------------------------------------------------------------------------
# Look for modules
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

SET(DGtal_VERSION_MAJOR 0)
SET(DGtal_VERSION_MINOR 3)
SET(DGtal_VERSION_PATCH 1)
SET(DGTAL_VERSION "${DGtal_VERSION_MAJOR}.${DGtal_VERSION_MINOR}.${DGtal_VERSION_PATCH}")
SET(PROJECT_VERSION "${DGtal_VERSION_MAJOR}.${DGtal_VERSION_MINOR}.${DGtal_VERSION_PATCH}")
SET(VERSION ${DGtal_VERSION_MAJOR}.${DGtal_VERSION_MINOR}.${DGtal_VERSION_PATCH})

MESSAGE(STATUS "DGtal Version ${PROJECT_VERSION}")
message(STATUS "-------------------------------------------------------------------------------" )

# -- Environement variables
if (UNIX)
  add_definitions(-DUNIX)
endif (UNIX)
if (WIN32)
  add_definitions(-DWIN32)
endif (WIN32)
if (APPLE)
  add_definitions(-DAPPLE)
endif (APPLE)


# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
set(INSTALL_DATA_DIR share CACHE PATH "Installation directory for data files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE DATA)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# -----------------------------------------------------------------------------
# Doxygen doc target
# -----------------------------------------------------------------------------
set(INSTALL_DOC_PATH ${CMAKE_INSTALL_PREFIX}/doc/${CMAKE_PROJECT_NAME} )
INCLUDE("${CMAKE_MODULE_PATH}/doxygen.cmake")
INCLUDE("${CMAKE_MODULE_PATH}/TargetDoxygenDoc.cmake" OPTIONAL)

# -----------------------------------------------------------------------------
# uninstall target
# -----------------------------------------------------------------------------
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/TargetUninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/TargetUninstall.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/TargetUninstall.cmake")

# -----------------------------------------------------------------------------
# Defines some variables
# -----------------------------------------------------------------------------
set ( LIBDGTAL_NAME "DGtal" )
set ( LIBDGTALVISU3D_NAME "DGtal-visu3d" )

# -----------------------------------------------------------------------------
# Parsing cmake options
# -----------------------------------------------------------------------------
OPTION(BUILD_SHARED_LIBS "Build shared libraries." ON)
OPTION(BUILD_INLINE_FUNCTIONS "Build inline functions." ON)
OPTION(DEBUG_VERBOSE "Verbose messages in debug mode." OFF)

if ( ${CMAKE_BUILD_TYPE} MATCHES "Debug" )
  IF (DEBUG_VERBOSE)
    ADD_DEFINITIONS(-DDEBUG_VERBOSE)
    MESSAGE(STATUS "Debug verbose mode activated")
  ENDIF(DEBUG_VERBOSE)
endif( ${CMAKE_BUILD_TYPE} MATCHES "Debug" )

if (BUILD_INLINE_FUNCTIONS)
  ADD_DEFINITIONS(-DINLINE=inline)
else (BUILD_INLINE_FUNCTIONS)
  ADD_DEFINITIONS(-DINLINE="")
endif (BUILD_INLINE_FUNCTIONS)

# -----------------------------------------------------------------------------
# Check CPP0X
# -----------------------------------------------------------------------------
INCLUDE(${CMAKE_MODULE_PATH}/CheckCPP0X.cmake)

# -----------------------------------------------------------------------------
# Check Dependencies
# -----------------------------------------------------------------------------
INCLUDE(${CMAKE_MODULE_PATH}/CheckDGtalDependencies.cmake)

# -----------------------------------------------------------------------------
# Benchmark target
# -----------------------------------------------------------------------------
ADD_CUSTOM_TARGET(benchmark COMMAND echo "Benchmarks launched.....")

# -----------------------------------------------------------------------------
# CTest options
# -----------------------------------------------------------------------------
ENABLE_TESTING()
include(CTest)
if (BUILD_TESTING)
  if (CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function        -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
  endif (CMAKE_COMPILER_IS_GNUCXX)
  if (CMAKE_COMPILER_IS_GNUCC)
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
  endif (CMAKE_COMPILER_IS_GNUCC)
  add_subdirectory (tests)
endif (BUILD_TESTING)


#------------------------------------------------------------------------------
# Configuration of the Config.h
#------------------------------------------------------------------------------
CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/src/DGtal/base/Config.h.in" "${PROJECT_SOURCE_DIR}/src/DGtal/base/Config.h" IMMEDIATE)

#------------------------------------------------------------------------------
# Some directories and files should also be cleaned when invoking 'make clean'
#------------------------------------------------------------------------------
ADD_CUSTOM_TARGET(distclean
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/TargetDistclean.cmake")

#------------------------------------------------------------------------------
# CPack Configurations
#------------------------------------------------------------------------------
INCLUDE("${CMAKE_MODULE_PATH}/DGtalCPackConfig.cmake")

#------------------------------------------------------------------------------
# Add subdirectories
#------------------------------------------------------------------------------
add_subdirectory (src)
add_subdirectory (tools)

#------------------------------------------------------------------------------
# Examples
#------------------------------------------------------------------------------
OPTION(BUILD_EXAMPLES "Build examples." ON)
IF (BUILD_EXAMPLES)
  add_subdirectory (examples)
ENDIF(BUILD_EXAMPLES)

#------------------------------------------------------------------------------
# DGtal Configuration file for the install target
#------------------------------------------------------------------------------

#--- Headers installation
install(DIRECTORY "${PROJECT_SOURCE_DIR}/src/" 
  DESTINATION "${INSTALL_INCLUDE_DIR}/" PATTERN "[A-Za-z0-9]+.*h")
INCLUDE("${CMAKE_MODULE_PATH}/DGtalConfigGenerator.cmake")
