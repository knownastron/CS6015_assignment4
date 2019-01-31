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
LLVM_PROFILE_FILE="error1-1.profraw" ./quad < ./error_test_cases/testError1-1.txt
LLVM_PROFILE_FILE="error1-2.profraw" ./quad < ./error_test_cases/testError1-2.txt
LLVM_PROFILE_FILE="error1-3.profraw" ./quad < ./error_test_cases/testError1-3.txt
LLVM_PROFILE_FILE="error2-1.profraw" ./quad < ./error_test_cases/testError2-1.txt
LLVM_PROFILE_FILE="error2-2.profraw" ./quad < ./error_test_cases/testError2-2.txt
LLVM_PROFILE_FILE="error2-3.profraw" ./quad < ./error_test_cases/testError2-3.txt
LLVM_PROFILE_FILE="error3-1.profraw" ./quad < ./error_test_cases/testError3-1.txt
LLVM_PROFILE_FILE="error3-2.profraw" ./quad < ./error_test_cases/testError3-2.txt
LLVM_PROFILE_FILE="error3-3.profraw" ./quad < ./error_test_cases/testError3-3.txt
LLVM_PROFILE_FILE="error4-1.profraw" ./quad < ./error_test_cases/testError4-1.txt
LLVM_PROFILE_FILE="error4-2.profraw" ./quad < ./error_test_cases/testError4-2.txt
LLVM_PROFILE_FILE="error4-3.profraw" ./quad < ./error_test_cases/testError4-3.txt

llvm-profdata merge -sparse quadSquare.profraw quadRectangle.profraw quadRhombi.profraw quadParallelogram.profraw quadTrapezoid.profraw quadKite.profraw quadQuadrilateral.profraw error1-1.profraw error1-2.profraw error1-3.profraw error2-1.profraw error2-2.profraw error2-2.profraw error3-1.profraw error3-2.profraw error3-3.profraw error4-1.profraw error4-2.profraw error4-3.profraw -o quad.profdata
llvm-cov show ./quad -instr-profile=quad.profdata

rm -f quad.profdata quadSquare.profraw quadRectangle.profraw quadRhombi.profraw quadParallelogram.profraw quadTrapezoid.profraw quadKite.profraw quadQuadrilateral.profraw error1-1.profraw error1-2.profraw error1-3.profraw error2-1.profraw error2-2.profraw error2-3.profraw error3-1.profraw error3-2.profraw error3-3.profraw error4-1.profraw error4-2.profraw error4-3.profraw quad.profdata
