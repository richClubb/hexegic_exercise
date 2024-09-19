all: main

main: lib_rotate
	gcc -o rotate main.c -L ./ -I ./ -l _rotate

lib_rotate:
	gcc -c -o rotate.o rotate.c -I ./
	ar rcs lib_rotate.a rotate.o

clean:
	rm -rf rotate.o lib_rotate.a rotate
	rm -rf output/*