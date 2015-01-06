file( GLOB_RECURSE logging_files *.h )

install(FILES ${logging_files} DESTINATION include/arccos/logging)