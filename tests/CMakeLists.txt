###################################
#
# Configuration des tests unitaires
#
###################################


function( make_test rep )
    file( GLOB_RECURSE source_files ${rep}/*.cpp )
    add_subdirectory( ${rep} )
    add_executable(arccos_${rep}_tests  ${source_files} )
    add_test( ${rep} arccos_${rep}_tests )
    target_link_libraries(arccos_${rep}_tests cppunit)
    add_dependencies( arccos_${rep}_tests libarccos )
endfunction(make_test)





## Options de compilation

## Obligatoire, active le standard c++11
add_definitions("-std=c++11")
## messages du compilateur
add_definitions("-Wall")
add_definitions("-Wextra")

## Optimisations
# add_definitions("-march=native")  # optimisation pour la machine
#add_definitions("-O3") # ou -Ofast pour désactiver le respect des standards stricts
add_definitions("-O3") # debug

# Ajout de chaque répertoire
add_subdirectory( "mptoolstests" )

# -------------------------

