#!/bin/bash
./quad < testKite.txt > resultKite.txt
./quad < testParallelogram.txt > resultParallelogram.txt
./quad < testQuadrilateral.txt > resultQuadrilateral.txt
./quad < testRectangle.txt > resultRectangle.txt
./quad < testRhombi.txt > resultRhombi.txt
./quad < testSquare.txt > resultSquare.txt
./quad < testTrapezoid.txt > resultTrapezoid.txt

diff resultKite.txt expectedKite.txt
diff resultParallelogram.txt expectedParallelogram.txt
diff resultQuadrilateral.txt expectedQuadrilateral.txt
diff resultRectangle.txt expectedRectangle.txt
diff resultRhombi.txt expectedRhombi.txt
diff resultSquare.txt expectedSquare.txt
diff resultTrapezoid.txt expectedTrapezoid.txt
