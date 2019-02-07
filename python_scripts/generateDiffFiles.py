

import os
import sys


def getInputFileName(count):
    file_prefix = "../fuzzer_test_cases/random"
    file_postfix = ".txt"
    return file_prefix + str(count) + file_postfix

def getOutputFileName(count):
    file_prefix = "../jianhui_results/jianhui"
    file_postfix = ".txt"
    return file_prefix + str(count) + file_postfix

def fuzz(count):
    """
    runs the input_file through the quadrilateral identifier and outputs
    output_file
    """
    input_file = getInputFileName(count)
    output_file = getOutputFileName(count)
    os.system("../quad < " + input_file + " > " + output_file)

def read(count):
    input_file = getInputFileName(count)
    output_file = getOutputFileName(count)
    with open("../fuzzer_results/" + output_file, "r") as f:
        print("count", count, f.read())

def testDouble(list, result, count):
    int_list = [str(x * 2) for x in list]
    joiner = " "
    f_input = open("tmp_input.txt", "w+")
    f_input.write(joiner.join(int_list))
    f_input.close()
    os.system("../quad < tmp_input.txt > tmp_output.txt")
    with open("tmp_output.txt", "r") as f:
        output = f.read()
        if (output != result):
            print("ERROR - DOUBLE")
            print("\tfile # " + str(count))
            print("\t" + output, "vs.", result)
            sys.exit()
    os.system("rm -f tmp_input.txt tmp_output.txt")

def testHalf(list, result, count):
    str_list = [str(int(x/2)) for x in list]
    joiner = " "
    f_input = open("tmp_input.txt", "w+")
    f_input.write(joiner.join(str_list))
    f_input.close()
    os.system("../quad < tmp_input.txt > tmp_output.txt")
    with open("tmp_output.txt", "r") as f:
        output = f.read()
        if (output != result):
            print("ERROR - Half")
            print("\tfile # " + str(count))
            print("\t" + output, "vs.", result)
            sys.exit()
    os.system("rm -f tmp_input.txt tmp_output.txt")

def checkIfManipulatable(file, key, count):
    with open(file, "r") as f:
        line = f.read()
        line_split = line.split(" ")
        int_list = [int(x) for x in line_split]
        if all(x <= 50 for x in int_list):
            testDouble(int_list, key, count)
        elif all(x >= 50 and x % 2 == 0 for x in int_list):
            testHalf(int_list, key, count)

def manipulateInputTest(count):
    input_file = getInputFileName(count)
    output_file = getOutputFileName(count)
    with open(output_file, "r") as f:
        line = f.read()
        if ("error" not in line):
            checkIfManipulatable(input_file, line, count)

def main():
    os.chdir(sys.path[0])
    trials = 1500
    count = 1
    for i in range(trials):
        fuzz(count)
        count += 1









main()
