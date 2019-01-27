out = open("testRectangle.txt", "w")

one = 2
two = 0
three = 2
four = 1
five = 0
six = 1

while (one < 99):
    one += 1

    three += 1
    four += 1

    six += 1

    out.write(str(one) + " " + str(two) + " " + str(three) + " " + str(four) + " " + str(five) + " " + str(six) + "\n")
