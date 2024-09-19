all: main

main: lib_rotate
	g++ -o rotate main.cpp -L ./ -I ./ -l _rotate

lib_rotate:
	g++ -c -o rotate.o rotate.cpp -I ./
	ar rcs lib_rotate.a rotate.o

clean:
	rm -rf rotate
	rm -rf lib_rotate.a
	rm -rf rotate.o
	rm -rf output/*