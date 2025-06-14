message(STATUS "Adding applications:")

SET(PROJECT_APPS_SUBDIRS
    MyApplication
)

set(GLOBAL PROPERTY PROJECT_APPLICATION_TARGETS "")

message(STATUS "\tAdding directories:")
foreach(SUBDIR IN LISTS PROJECT_APPS_SUBDIRS)
    message(STATUS "\t\t- ${SUBDIR}")
    add_subdirectory(${SUBDIR})
endforeach()

get_property(ALL_APPLICATION_TARGETS GLOBAL PROPERTY PROJECT_APPLICATION_TARGETS)
message(STATUS "\tFound targets:")
foreach(APPLICATION IN LISTS ALL_APPLICATION_TARGETS)
    message(STATUS "\t\t- ${APPLICATION}")
    set_target_properties(${APPLICATION} PROPERTIES FOLDER "apps")
endforeach()