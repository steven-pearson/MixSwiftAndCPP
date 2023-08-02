
add_executable(TaxCalcTest TaxCalcTest.cpp)

# links gtest
target_link_libraries( TaxCalcTest ${GTEST_LIBRARIES} TaxCalc )


