all:
	gcc -c c/main.c -o main.o
	gcc -c c/benchmarks.c -o benchmarks.o
	nasm -f elf64 asm/numbers.asm -o numbers.o
	nasm -f elf64 asm/strings.asm -o strings.o
	nasm -f elf64 asm/arrays.asm -o arrays.o
	gcc -no-pie main.o benchmarks.o numbers.o strings.o arrays.o -o project

clean:
	rm -f *.o project
