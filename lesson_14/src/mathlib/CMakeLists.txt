add_library(mathlib STATIC mathlib.cpp)

set_target_properties(mathlib PROPERTIES
    OUTPUT_NAME "mathlib"
    SUFFIX ".libx"
)

add_library(Math::Lib ALIAS mathlib)
