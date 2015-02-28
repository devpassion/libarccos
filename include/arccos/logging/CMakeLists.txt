file( GLOB_RECURSE logging_files *.h )

set( LOGGING_SRCS ${logging_files} PARENT_SCOPE )

install(FILES ${logging_files} DESTINATION include/arccos/logging)