all: main

main: lib_rotate.a
	gcc -o rotate main.c -L ./ -I ./ -l _rotate

lib_rotate.a:
	gcc -c -o rotate.o rotate.c -I ./
	ar rcs lib_rotate.a rotate.o

clean:
	rm -rf rotate.o lib_rotate.a rotate