Project(Library1 VERSION 1.0
        DESCRIPTION "Library 1"
        LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "*.cpp")

add_library(Library1_exe ${SOURCES})

target_include_directories(Library1_exe
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

SET(LIBRARY1_TARGETS Library1_exe)

get_property(_targets GLOBAL PROPERTY PROJECT_COMPONENT_TARGETS)
list(APPEND _targets ${LIBRARY1_TARGETS})
set_property(GLOBAL PROPERTY PROJECT_COMPONENT_TARGETS "${_targets}")