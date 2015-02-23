


add_subdirectory(mptools)

add_subdirectory(logging)

add_subdirectory(structs)

add_definitions( "-std=c++14" )


add_library( libarccos ${MPLTOOLS_SRCS} ${LOGGING_SRCS} ${STRUCTS_SRCS} )
