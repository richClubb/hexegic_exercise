all: main

main: lib_rotate
	gcc -o rotate main.c -L ./ -I ./ -l _rotate

debug: clean lib_rotate_debug
	gcc -g -o rotate main.c -L ./ -I ./ -l _rotate 

lib_rotate:
	gcc -c -o rotate.o rotate.c -I ./
	ar rcs lib_rotate.a rotate.o

lib_rotate_debug:
	gcc -g -c -o rotate.o rotate.c -I ./
	ar rcs lib_rotate.a rotate.o

tests: lib_rotate_debug
	gcc -g -o rotate_tests rotate_tests.c -L ./ -I ./ -l _rotate

run_tests: tests
	./rotate_tests

clean:
	rm -rf rotate.o lib_rotate.a rotate
	rm -rf output/*