file( GLOB_RECURSE test_files_cpp *.cpp )
file( GLOB_RECURSE test_files_h *.h )

set( TEST_SRCS "${test_files_h};${test_files_cpp}" PARENT_SCOPE )

install(FILES ${test_files} DESTINATION include/arccos/test)