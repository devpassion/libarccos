file( GLOB_RECURSE mpltools_files *.h )

install(FILES ${mpltools_files} DESTINATION include/arccos/mpltools)