file( GLOB_RECURSE game_files_cpp *.cpp )
file( GLOB_RECURSE game_files_h *.h )

set( GAME_SRCS "${game_files_h};${game_files_cpp}" PARENT_SCOPE )

install(FILES ${game_files} DESTINATION include/arccos/game)