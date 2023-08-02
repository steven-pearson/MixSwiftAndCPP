add_library(TaxCalc TaxCalculator.cpp)

if(NOT MSVC)
    target_compile_options(TaxCalc PUBLIC -Wall -pedantic)
endif(NOT MSVC)
# Include code-coverage settings:
target_link_libraries(TaxCalc PUBLIC coverage_config)