#CMakeLists associated to the tests subdir
#David Coeurjolly <david.coeurjolly@liris.cnrs.fr>

# Make sure the compiler can find include files.
if ( CPP0X_INITIALIZER_LIST )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif ( CPP0X_INITIALIZER_LIST )

# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/src/)
# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/tests/)


# Make sure the linker can find the Hello library once it is built.
link_directories (${PROJECT_BINARY_DIR})

# ConfigTest.h instanciation.
configure_file(${PROJECT_SOURCE_DIR}/tests/ConfigTest.h.in ${PROJECT_SOURCE_DIR}/tests/ConfigTest.h IMMEDIATE)


#------TESTS subdirectories ------

add_subdirectory(base)
add_subdirectory(kernel)
add_subdirectory(math)
add_subdirectory(utils)
add_subdirectory(geometry/2d)
add_subdirectory(geometry/3d)
add_subdirectory(geometry/nd)
add_subdirectory(topology)
add_subdirectory(io-viewers)
add_subdirectory(io-viewers/3dViewers)
add_subdirectory(io-viewers/colormaps)
add_subdirectory(io-viewers/readers)
add_subdirectory(io-viewers/writers)

add_subdirectory(images)
add_subdirectory(helpers)


