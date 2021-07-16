add-nbo: main.o
	gcc -o add-nbo main.o
main.o: main.cpp
	gcc -c main.cpp
