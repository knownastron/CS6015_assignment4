#!/bin/bash
rm -f quad.profdata quad.profraw
clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o quad
LLVM_PROFILE_FILE="quadSquare.profraw" ./quad < ./test_cases/testSquare.txt
LLVM_PROFILE_FILE="quadRectangle.profraw" ./quad < ./test_cases/testRectangle.txt
LLVM_PROFILE_FILE="quadRhombi.profraw" ./quad < ./test_cases/testRhombi.txt
LLVM_PROFILE_FILE="quadParallelogram.profraw" ./quad < ./test_cases/testParallelogram.txt
LLVM_PROFILE_FILE="quadTrapezoid.profraw" ./quad < ./test_cases/testTrapezoid.txt
LLVM_PROFILE_FILE="quadKite.profraw" ./quad < ./test_cases/testKite.txt
LLVM_PROFILE_FILE="quadQuadrilateral.profraw" ./quad < ./test_cases/testQuadrilateral.txt
llvm-profdata merge -sparse quadSquare.profraw quadRectangle.profraw quadRhombi.profraw quadParallelogram.profraw quadTrapezoid.profraw quadKite.profraw quadQuadrilateral.profraw -o quad.profdata
llvm-cov show ./quad -instr-profile=quad.profdata

rm -f quad.profdata quadSquare.profraw quadRectangle.profraw quadRhombi.profraw quadParallelogram.profraw quadTrapezoid.profraw quadKite.profraw quadQuadrilateral.profraw quad.profdata
