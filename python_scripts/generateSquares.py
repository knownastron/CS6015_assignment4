out = open("testSquare.txt", "w")

one = 0
two = 0
three = 0
four = 0
five = 0
six = 0

while (one < 101):
    one += 1

    three += 1
    four += 1

    six += 1

    out.write(str(one) + " " + str(two) + " " + str(three) + " " + str(four) + " " + str(five) + " " + str(six) + "\n")
