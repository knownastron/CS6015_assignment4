input_txt = ["testParallelogram.txt", "testRhombi.txt", "testTrapezoid.txt",
            "testKite.txt", "testQuadrilateral.txt", "testSquare.txt", "testRectangle.txt"]
expected_txt = ["expectedParallelogram.txt", "expectedRhombi.txt", "expectedTrapezoid.txt",
            "expectedKite.txt", "expectedQuadrilateral.txt", "expectedSquare.txt", "expectedRectangle.txt"]
line_output = ["parallelogram", "rhombus", "trapezoid", "kite", "quadrilateral", "square", "rectangle"]


for i in range(len(input_txt)):
    with open(input_txt[i]) as f:
        lines = f.readlines()
        out = open(expected_txt[i], "w")
        for line in lines:
            out.write(line_output[i] + "\n")
