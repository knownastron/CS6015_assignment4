#!/bin/bash
rm -f quad.profdata quad.profraw
clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o quad
LLVM_PROFILE_FILE="quad.profraw" ./quad < testMaster.txt
llvm-profdata merge -sparse quad.profraw -o quad.profdata
llvm-cov show ./quad -instr-profile=quad.profdata

rm -f quad.profdata quad.profraw
