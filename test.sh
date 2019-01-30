#!/bin/bash
./quad < ./test_cases/testKite.txt > ./results/resultKite.txt
./quad < ./test_cases/testParallelogram.txt > ./results/resultParallelogram.txt
./quad < ./test_cases/testQuadrilateral.txt > ./results/resultQuadrilateral.txt
./quad < ./test_cases/testRectangle.txt > ./results/resultRectangle.txt
./quad < ./test_cases/testRhombi.txt > ./results/resultRhombi.txt
./quad < ./test_cases/testSquare.txt > ./results/resultSquare.txt
./quad < ./test_cases/testTrapezoid.txt > ./results/resultTrapezoid.txt

diff ./results/resultKite.txt ./expected/expectedKite.txt
diff ./results/resultParallelogram.txt ./expected/expectedParallelogram.txt
diff ./results/resultQuadrilateral.txt ./expected/expectedQuadrilateral.txt
diff ./results/resultRectangle.txt ./expected/expectedRectangle.txt
diff ./results/resultRhombi.txt ./expected/expectedRhombi.txt
diff ./results/resultSquare.txt ./expected/expectedSquare.txt
diff ./results/resultTrapezoid.txt ./expected/expectedTrapezoid.txt


