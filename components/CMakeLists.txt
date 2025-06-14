
SET(PROJECT_TARGET_SUBDIRS
    Library1
)

message(STATUS "Adding components:")
foreach(SUBDIR ${PROJECT_TARGET_SUBDIRS})
    message(STATUS "\t${SUBDIR}")
    add_subdirectory(${SUBDIR})
endforeach()
