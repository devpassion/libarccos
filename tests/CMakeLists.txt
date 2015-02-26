###################################
#
# Configuration des tests unitaires
#
###################################

include( CTest )
enable_testing()

find_library( CPPUNIT cppunit)

if( CPPUNIT-NOTFOUND )
  message( FATAL_ERROR "cppunit est introuvable" )
endif(CPPUNIT-NOTFOUND )



function( make_test rep )
    file( GLOB_RECURSE source_files ${rep}/*.cpp )
    add_subdirectory( ${rep} )
    add_executable(arccos_${rep}_tests  ${source_files} )
    add_test( ${rep} arccos_${rep}_tests )
    target_link_libraries(arccos_${rep}_tests cppunit)
    add_dependencies( arccos_${rep}_tests libarccos )
    add_dependencies( check arccos_${rep}_tests )
endfunction(make_test)

## Options de compilation

## Obligatoire, active le standard c++11 (ou 14)
add_definitions("-std=c++14")
## messages du compilateur
add_definitions("-Wall")
add_definitions("-Wextra")

## Optimisations
# add_definitions("-march=native")  # optimisation pour la machine
#add_definitions("-O3") # ou -Ofast pour désactiver le respect des standards stricts
# add_definitions("-O0 -g") # debug

# TODO: paramétrer avec une variable d'environnement
add_definitions( "-DLOGLEVEL=2")

# Ajout de chaque répertoire
add_subdirectory( "mptoolstests" )
add_subdirectory( "structstests" )
# -------------------------

