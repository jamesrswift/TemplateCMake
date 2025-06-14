project(MyApplication VERSION 1.0
				   DESCRIPTION "My Application"
				   LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(MyApplication ${SOURCES})