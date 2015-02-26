


add_subdirectory(mptools)

add_subdirectory(logging)

add_subdirectory(structs)

add_subdirectory(game)


add_subdirectory(test)

add_definitions( "-std=c++14" )


add_library( libarccos ${MPLTOOLS_SRCS} ${LOGGING_SRCS} ${STRUCTS_SRCS} ${TEST_SRCS} ${GAME_SRCS} )
