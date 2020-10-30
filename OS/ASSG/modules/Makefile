all: run

run: main.o utilities.o navigate.o cmdMode.o 
	g++ main.o utilities.o navigate.o cmdMode.o -o run

main.o: main.cpp
	g++ -c main.cpp

utilities.o: utilities.cpp
	g++ -c utilities.cpp

cmdMode.o: cmdMode.cpp
	g++ -c cmdMode.cpp

navigate.o: navigate.cpp
	g++ -c navigate.cpp

clear:
	rm -f *.o