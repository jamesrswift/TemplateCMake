Project(Library1 VERSION 1.0
        DESCRIPTION "Library 1"
        LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "*.cpp")

add_library(Library1 ${SOURCES})
target_include_directories(Library1
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
SET( PROJECT_PUBLIC_TARGETS Library1 ${PROJECT_PUBLIC_TARGETS} )