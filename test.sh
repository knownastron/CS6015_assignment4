#!/bin/bash
./quad < ./test_cases/testKite.txt > resultKite.txt
./quad < ./test_cases/testParallelogram.txt > resultParallelogram.txt
./quad < ./test_cases/testQuadrilateral.txt > resultQuadrilateral.txt
./quad < ./test_cases/testRectangle.txt > resultRectangle.txt
./quad < ./test_cases/testRhombi.txt > resultRhombi.txt
./quad < ./test_cases/testSquare.txt > resultSquare.txt
./quad < ./test_cases/testTrapezoid.txt > resultTrapezoid.txt

diff resultKite.txt expectedKite.txt
diff resultParallelogram.txt expectedParallelogram.txt
diff resultQuadrilateral.txt expectedQuadrilateral.txt
diff resultRectangle.txt expectedRectangle.txt
diff resultRhombi.txt expectedRhombi.txt
diff resultSquare.txt expectedSquare.txt
diff resultTrapezoid.txt expectedTrapezoid.txt
