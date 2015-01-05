add_subdirectory(mptools)

add_subdirectory(logging)

file( GLOB_RECURSE logging_files logging/*.h )
file( GLOB_RECURSE mpltools_files mpltools/*.h )

install(FILES ${logging_files} DESTINATION include/arccos/logging)
install(FILES ${mpltools_files} DESTINATION include/arccos/mpltools)