project(MyApplication VERSION 1.0.0
        DESCRIPTION "My Application"
		LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(MyApplication ${SOURCES})

target_include_directories(MyApplication
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

SET(MyApplication_TARGETS MyApplication)

get_property(_targets GLOBAL PROPERTY PROJECT_APPLICATION_TARGETS)
list(APPEND _targets ${MyApplication_TARGETS})
set_property(GLOBAL PROPERTY PROJECT_APPLICATION_TARGETS "${_targets}")