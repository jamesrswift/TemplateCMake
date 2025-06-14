SET(PROJECT_APPS_SUBDIRS
    MyApplication
)

message(STATUS "Adding applications:")
foreach(APPLICATION ${PROJECT_APPS_SUBDIRS})
    message(STATUS "\t${APPLICATION}")
    add_subdirectory(${APPLICATION})
endforeach()
