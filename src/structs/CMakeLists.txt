file( GLOB_RECURSE structs_files *.h )

install(FILES ${structs_files} DESTINATION include/arccos/structs)