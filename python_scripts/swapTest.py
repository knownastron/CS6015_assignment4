"""
This test swaps point 2 and 4 and checks that the result is the same
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

def swapInputs(file, count):
    with open(file, "r") as f:
        line = f.read()
        line_split = line.split(" ")
        swap(line_split, 0, 4)
        swap(line_split, 1, 5)
        joiner = " "
        str_line = joiner.join(line_split)
        return str_line

def runSwappedLine(swapped_line, result, count):
    f_input = open("tmp_input.txt", "w+")
    f_input.write(swapped_line)
    f_input.close()
    os.system("../quad < tmp_input.txt > tmp_output.txt")
    with open("tmp_output.txt", "r") as f:
        output = f.read()
        if (output != result):
            print("ERROR - Swapped")
            print("\tfile # " + str(count))
            print("\t" + output, "vs.", result)
            sys.exit()
    os.system("rm -f tmp_input.txt tmp_output.txt")
        # 0 1 2 3 4 5

def swap(list, i1, i2):
    tmp = list[i1]
    list[i1] = list[i2]
    list[i2] = tmp

def swapInputTest(count):
    input_file = getInputFileName(count)
    output_file = getOutputFileName(count)
    with open(output_file, "r") as f:
        result_line = f.read()
        if ("error" not in result_line):
            swapped_line = swapInputs(input_file, count)
            runSwappedLine(swapped_line, result_line, count)
            # checkSwapEqualsOriginal(swapped_line, line, count)

def main():
    os.chdir(sys.path[0])

    trials = 1500
    count = 1
    for i in range(trials):
        swapInputTest(count)
        count += 1
    print("Swap Testing complete - OK")









main()
