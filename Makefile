all: quad

quad: main.cpp
	clang++ -std=c++11 main.cpp -o quad

test:
	./test.sh

clean:
	rm -f quad
