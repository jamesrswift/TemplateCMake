cmake_minimum_required(VERSION 3.14...4.0)

project(MyProject VERSION 1.0.0
                  DESCRIPTION "Very nice project"
                  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(cmake/externSubmodules.cmake)

#------------------------------
# Handle includes

configure_file (
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Version.h.in"
    "${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/Version.h"
)

include_directories(include)

file(GLOB_RECURSE HEADERS_H "headers/*.h")
file(GLOB_RECURSE HEADERS_HPP "headers/*.hpp")
file(GLOB_RECURSE HEADERS_HXX "headers/*.hxx")
SET(HEADERS ${HEADERS_H} ${HEADERS_HPP} ${HEADERS_HXX})

#------------------------------
# Handle Components

add_subdirectory(components)

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_PUBLIC_TARGETS})


#------------------------------
# Handle Applications

add_subdirectory(apps)

#------------------------------
# Handle installation

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_PUBLIC_TARGETS}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )


#------------------------------
# Handle Testing
# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
