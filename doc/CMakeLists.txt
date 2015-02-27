option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" OFF)

if(BUILD_DOCUMENTATION)

  find_package(Doxygen)

  if(NOT DOXYGEN_FOUND)
    MESSAGE(FATAL_ERROR "Doxygen is needed to build the documentation.")
  endif()

  set( DOXYGEN_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in )
  set( DOXYGEN_FILTERED_CONFIG ${PROJECT_BINARY_DIR}/doc/Doxyfile )

  set( DOXYGEN_INDEX ${CMAKE_CURRENT_BINARY_DIR}/html/index.html )

  #variables for output
  set( DOXYGEN_INPUT ${PROJECT_SOURCE_DIR}/include )
  set( DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR} )

  configure_file( ${DOXYGEN_CONFIG} ${DOXYGEN_FILTERED_CONFIG} @ONLY )

  add_custom_command( OUTPUT ${DOXYGEN_INDEX}
                      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILTERED_CONFIG}
                      COMMENT "Generating HTML documentation")

  add_custom_target( doc ALL DEPENDS ${DOXYGEN_INDEX} )

  install( DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc )

endif()