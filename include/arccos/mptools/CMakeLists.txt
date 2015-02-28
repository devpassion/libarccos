file( GLOB_RECURSE mpltools_files_h *.h )
file( GLOB_RECURSE mpltools_files_cpp *.cpp )

set( MPLTOOLS_SRCS "${mpltools_files_h};${mpltools_files_cpp}" PARENT_SCOPE )

install(FILES ${mpltools_files} DESTINATION include/arccos/mpltools)