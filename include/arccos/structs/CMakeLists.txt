file( GLOB_RECURSE structs_files_cpp *.cpp )
file( GLOB_RECURSE structs_files_h *.h )

set( STRUCTS_SRCS "${structs_files_h};${structs_files_cpp}" PARENT_SCOPE )

install(FILES ${structs_files} DESTINATION include/arccos/structs)