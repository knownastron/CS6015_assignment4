import os
import sys

def getOutputFileName(count):
    file_prefix = "../fuzzer_results/result"
    file_postfix = ".txt"
    return file_prefix + str(count) + file_postfix

def testOutOfBound(count):
    output_file = getOutputFileName(count)
    with open(output_file, "r") as f:
        line = f.read()
        if line != "error 1":
            print("ERROR - OUT OF BOUND")
            print("\tfile # " + str(count))
            print("\t" + line, "vs. error 1")
            sys.exit()

def testMissing(count):
    output_file = getOutputFileName(count)
    with open(output_file, "r") as f:
        line = f.read()
        if line != "error 1":
            print("ERROR - MISSING")
            print("\tfile # " + str(count))
            print("\t" + line, "vs. error 1")
            sys.exit()

def testChar(count):
    output_file = getOutputFileName(count)

    with open(output_file, "r") as f:
        line = f.read()
        if line != "error 1":
            print("ERROR - CHAR")
            print("\tfile # " + str(count))
            print("\t" + line, "vs. error 1")
            sys.exit()

def errorTest(count):
    if count % 102 == 0:
        testOutOfBound(count)
    elif count % 103 == 0:
        testMissing(count)
    elif count % 104 == 0:
        testChar(count)






def main():
    os.chdir(sys.path[0])
    trials = 1500
    count = 1
    for i in range(trials):
        errorTest(count)
        count += 1
    print("Error Testing complete - OK")

main()
