cmake_minimum_required(VERSION 3.14...4.0)

project(MyProject VERSION 1.0.0
                  DESCRIPTION "Very nice project"
                  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#include(cmake/externSubmodules.cmake)
include(cmake/defaultBuildType.cmake)
include(cmake/IPO.cmake)
include(cmake/subdirlist.cmake)

#------------------------------
# Handle includes

configure_file (
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Version.h.in"
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Version.h"
)

include_directories(include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

file(GLOB_RECURSE HEADERS_H CONFIGURE_DEPENDS "include/*.h")
file(GLOB_RECURSE HEADERS_HPP CONFIGURE_DEPENDS "include/*.hpp")
file(GLOB_RECURSE HEADERS_HXX CONFIGURE_DEPENDS "include/*.hxx")
SET(HEADERS ${HEADERS_H} ${HEADERS_HPP} ${HEADERS_HXX})

#------------------------------
# Handle Components

add_subdirectory(components)
get_property(ALL_COMPONENT_TARGETS GLOBAL PROPERTY PROJECT_COMPONENT_TARGETS)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${ALL_COMPONENT_TARGETS})

#------------------------------
# Handle Applications

add_subdirectory(apps)
get_property(ALL_APPLICATION_TARGETS GLOBAL PROPERTY PROJECT_APPLICATION_TARGETS)

#------------------------------
# Handle installation

install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} ${ALL_COMPONENT_TARGETS} ${ALL_APPLICATION_TARGETS}
    RUNTIME DESTINATION bin           # For executables (on Windows .exe)
    LIBRARY DESTINATION bin           # For shared libraries (.so/.dylib)
    ARCHIVE DESTINATION lib           # For static libraries (.a/.lib)
)

#------------------------------
# Handle Testing
# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

#------------------------------
# Handle Documentation

find_package(Doxygen OPTIONAL_COMPONENTS mscgen dia dot)

set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)


add_custom_target(doxygen
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation"
)

set_target_properties(doxygen PROPERTIES FOLDER "utility")

#------------------------------
# Handle Assets

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
if(EXISTS ${ASSETS_DIR})
    file(GLOB_RECURSE ASSETS CONFIGURE_DEPENDS "${ASSETS_DIR}/*")
    install(FILES ${ASSETS} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/assets)
    file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
    message(STATUS "No assets directory found, skipping asset installation.")
endif()