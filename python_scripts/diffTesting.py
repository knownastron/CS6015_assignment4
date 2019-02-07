import os

def getInputFileName(count):
    file_prefix = "../fuzzer_test_cases/random"
    file_postfix = ".txt"
    return file_prefix + str(count) + file_postfix

def getJianhuiFileName(count):
    file_prefix = "../jianhui_results/jianhui"
    file_postfix = ".txt"
    return file_prefix + str(count) + file_postfix

def getOutputFileName(count):
    file_prefix = "../fuzzer_results/result"
    file_postfix = ".txt"
    return file_prefix + str(count) + file_postfix

os.system("python generateRandomTests.py")
os.system("python generateResultFiles.py")
os.system("python generateDiffFiles.py")

trials = 1500
for i in range(1, trials + 1):
    jianhui_output_file = getJianhuiFileName(i)

    my_output_file = getOutputFileName(i)
    os.system("diff " + my_output_file + " " + jianhui_output_file)
