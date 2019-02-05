all: quad

quad: main.cpp
	clang++ -std=c++11 main.cpp -o quad

test:
	./test.sh

fuzzer:
	./fuzz

cover:

clean:
	rm -f quad
