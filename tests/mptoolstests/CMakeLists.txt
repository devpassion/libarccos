# # 
# 
# # 

make_test( "intervaltests" )
make_test( "loggingtests" )

# Déplacer
add_definitions( "-DTMP=build/tmp" )