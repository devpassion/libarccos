file( GLOB_RECURSE mpltools_files mpltools/*.h )

install(FILES ${mpltools_files} DESTINATION include/arccos/mpltools)