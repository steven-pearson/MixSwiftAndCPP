## Build
```
cd build
cmake .. -GNinja
ninja
```

## Generate the Xcode project
```
mkdir Xcode
cd Xcode
cmake .. -G Xcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_Swift_COMPILER_FORCED=true -DCMAKE_OSX_DEPLOYMENT_TARGET=14.0
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