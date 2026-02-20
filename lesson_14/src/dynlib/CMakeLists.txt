add_library(dyn_math SHARED dynlib.cpp)

set_target_properties(dyn_math PROPERTIES
    PREFIX "dyn_"          
    OUTPUT_NAME "dyn_math" 
)
