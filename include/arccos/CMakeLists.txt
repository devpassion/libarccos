file( GLOB_RECURSE ALL_HEADERS . *.h )

install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include  FILES_MATCHING PATTERN "*.h"  )
