Project(Library1 VERSION 1.0
        DESCRIPTION "Library 1"
        LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(MyLibrary_lib ${SOURCES})

target_include_directories(MyLibrary_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

SET(LIBRARY1_TARGETS MyLibrary_lib)

get_property(_targets GLOBAL PROPERTY PROJECT_COMPONENT_TARGETS)
list(APPEND _targets ${LIBRARY1_TARGETS})
set_property(GLOBAL PROPERTY PROJECT_COMPONENT_TARGETS "${_targets}")