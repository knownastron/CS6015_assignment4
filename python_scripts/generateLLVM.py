#!/bin/bash
"""
rm -f quad.profdata quad.profraw quad
clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o quad
LLVM_PROFILE_FILE="quadSquare.profraw" ./quad < ./test_cases/testSquare.txt

llvm-profdata merge -sparse quadSquare.profraw quadRectangle.profraw quadRhombi.profraw quadParallelogram.profraw quadTrapezoid.profraw quadKite.profraw quadQuadrilateral.profraw error1-1.profraw error1-2.profraw error1-3.profraw error2-1.profraw error2-2.profraw error2-2.profraw error3-1.profraw error3-2.profraw error3-3.profraw error4-1.profraw error4-2.profraw error4-3.profraw -o quad.profdata
llvm-cov show ./quad -instr-profile=quad.profdata

rm -f default.profraw quad.profdata quadSquare.profraw quadRectangle.profraw quadRhombi.profraw quadParallelogram.profraw quadTrapezoid.profraw quadKite.profraw quadQuadrilateral.profraw error1-1.profraw error1-2.profraw error1-3.profraw error2-1.profraw error2-2.profraw error2-3.profraw error3-1.profraw error3-2.profraw error3-3.profraw error4-1.profraw error4-2.profraw error4-3.profraw quad.profdata quad
"""

import os
import sys

def getInputFileName(count):
    file_prefix = "../fuzzer_test_cases/random"
    file_postfix = ".txt"
    return file_prefix + str(count) + file_postfix

def getOutputFileName(count):
    file_prefix = "../fuzzer_results/result"
    file_postfix = ".txt"
    return file_prefix + str(count) + file_postfix

def getProfrawFileName(count):
    file_prefix = "random"
    file_postfix = ".profraw"
    return file_prefix + str(count) + file_postfix

def main():
    os.chdir(sys.path[0])
    trials = 1500
    os.system("rm -f quad.profdata quad.profraw quad")
    os.system("clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping ../main.cpp -o ../quad")

    for count in range(1, trials + 1):
        input_file = getInputFileName(count)
        profraw_file = getProfrawFileName(count)
        os.system("LLVM_PROFILE_FILE=" + profraw_file + " ../quad < " + input_file + " > templlvm.txt")

    merge_str = "llvm-profdata merge -sparse "
    for count in range(1, trials + 1):
        merge_str += getProfrawFileName(count) + " "
        count += 1
    merge_str += "-o quad.profdata"
    os.system(merge_str)
    os.system("llvm-cov show ../quad -instr-profile=quad.profdata > ../coverage.txt")

    for count in range(1, trials + 1):
        profraw_file = getProfrawFileName(count)
        os.system("rm -f " + profraw_file + " " + "quad.profdata " + "templlvm.txt")
        count += 1

os.chdir(sys.path[0])
main()
