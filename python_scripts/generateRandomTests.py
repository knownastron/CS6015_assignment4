import os
import random
import string
import sys

def generateRandomLine():
    line = str(random.randint(0,100))

    for i in range(5):
        line += " " + str(random.randint(0, 100))

    return line

def generateSquare():
    num = str(random.randint(0,100))
    line = num + " " + str(0) + " " + num + " " + num + " " + str(0) + " " + num
    return line

def generateRectangle():
    num1 = str(random.randint(0,100))
    num2 = str(random.randint(0,100))
    line = num1 + " " + str(0) + " " + num1 + " " + num2 + " " + str(0) + " " + num2
    return line


def getNumOutsideRange():
    curNum = 50
    while curNum in range(0,101):
        curNum = random.randint(-100, 200)
    return curNum

def getRandomChar():
    letter = random.choice(string.printable)
    while letter.isspace() or letter in string.digits:
        letter = random.choice(string.printable)
    return letter

def generateOutOfBound():
    line = ''
    numOfOut = random.randint(1, 6) # get number out of bounds
    indexes = []
    for num in range(numOfOut):
        indexes.append(random.randint(0,5)) # 4
    # first int
    if 0 in indexes:
        line = str(getNumOutsideRange())
    else:
        line = str(random.randint(0,100))

    # all other ints
    for i in range(1,6):
        if i in indexes:
            line += " " + str(getNumOutsideRange())
        else:
            line += " " + str(random.randint(0, 100))
    return line

def generateMissing():
    line = str(random.randint(0, 100))

    for i in range(4):
        line += " " + str(random.randint(0, 100))

    return line

def generateCharLine():
    line = ''
    numOfChar = random.randint(1, 6) # get number out of bounds
    indexes = []
    for num in range(numOfChar):
        indexes.append(random.randint(0,5)) # 4

    # first int
    if 0 in indexes:
        line = str(getRandomChar())
    else:
        line = str(random.randint(0,100))

    # all other ints
    for i in range(1,5):
        if i in indexes:
            line += " " + str(getRandomChar())
        else:
            line += " " + str(random.randint(0, 100))
    return line

def main():
    os.chdir(sys.path[0])
    trials = 1500
    file_prefix = "../fuzzer_test_cases/random"
    file_postfix = ".txt"
    count = 1

    for i in range(trials):
        cur_file = file_prefix + str(count) + file_postfix
        out = open(cur_file, 'w+')
        line = ''
        if count % 100 == 0:
            line = generateSquare()
        elif count % 101 == 0:
            line = generateRectangle()
        elif count % 102 == 0:
            line = generateOutOfBound()
            # print("bound", count, line)
        elif count % 103 == 0:
            line = generateMissing()
            # print("missing", count, line)
        elif count % 104 == 0:
            line = generateCharLine()
            # print("char", count, line)
        else:
            line = generateRandomLine()
        out.write(line)
        count += 1

def test():
    for i in range(100):
        print(getRandomChar())

main()
# test()
