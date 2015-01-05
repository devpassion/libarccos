file( GLOB_RECURSE logging_files logging/*.h )

install(FILES ${logging_files} DESTINATION include/arccos/logging)