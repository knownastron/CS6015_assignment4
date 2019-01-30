#!/bin/bash
./quad < ./test_cases/testKite.txt > resultKite.txt
./quad < ./test_cases/testParallelogram.txt > resultParallelogram.txt
./quad < ./test_cases/testQuadrilateral.txt > resultQuadrilateral.txt
./quad < ./test_cases/testRectangle.txt > resultRectangle.txt
./quad < ./test_cases/testRhombi.txt > resultRhombi.txt
./quad < ./test_cases/testSquare.txt > resultSquare.txt
./quad < ./test_cases/testTrapezoid.txt > resultTrapezoid.txt

diff resultKite.txt ./expected/expectedKite.txt
diff resultParallelogram.txt ./expected/expectedParallelogram.txt
diff resultQuadrilateral.txt ./expected/expectedQuadrilateral.txt
diff resultRectangle.txt ./expected/expectedRectangle.txt
diff resultRhombi.txt ./expected/expectedRhombi.txt
diff resultSquare.txt ./expected/expectedSquare.txt
diff resultTrapezoid.txt ./expected/expectedTrapezoid.txt
