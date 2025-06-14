message(STATUS "Adding components:")

SET(PROJECT_COMPONENT_SUBDIRS
    Library1
)

SET(GLOBAL PROPERTY PROJECT_COMPONENT_TARGETS "")

message(STATUS "\tAdding directories:")
foreach(SUBDIR IN LISTS PROJECT_COMPONENT_SUBDIRS)
    message(STATUS "\t\t- ${SUBDIR}")
    add_subdirectory(${SUBDIR})
endforeach()

get_property(ALL_COMPONENT_TARGETS GLOBAL PROPERTY PROJECT_COMPONENT_TARGETS)
message(STATUS "\tFound targets:")
foreach(COMPONENT IN LISTS ALL_COMPONENT_TARGETS)
    message(STATUS "\t\t- ${COMPONENT}")
    set_target_properties(${COMPONENT} PROPERTIES FOLDER "components")
endforeach()