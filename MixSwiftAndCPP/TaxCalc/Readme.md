## Build
```
cd build
cmake .. -GNinja
ninja
```

## Run tests
```
cd build
ctest
```

## Code Coverage
```
cd build/src/CMakeFiles/TaxCalc.dir
gcov TaxCalculator.cpp.gcno
mkdir ../../../../coverage
geninfo -o ../../../../coverage/lcov.info --ignore-errors inconsistent,inconsistent .
cd ../../../../coverage
genhtml lcov.info --output-directory results --ignore-errors inconsistent
```