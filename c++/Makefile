all: main

main: lib_rotate
	g++ -o rotate main.cpp -L ./ -I ./ -l _rotate

debug: lib_rotate_debug
	g++ -g -o rotate main.cpp -L ./ -I ./ -l _rotate

lib_rotate:
	g++ -c -o rotate.o rotate.cpp -I ./
	ar rcs lib_rotate.a rotate.o

lib_rotate_debug:
	g++ -g -c -o rotate.o rotate.cpp -I ./
	ar rcs lib_rotate.a rotate.o

tests: lib_rotate_debug
	g++ -g -o rotate_tests rotate_tests.cpp -L ./ -I ./ -l _rotate

run_tests: tests
	./rotate_tests

clean:
	rm -rf rotate
	rm -rf lib_rotate.a
	rm -rf rotate.o
	rm -rf output/*