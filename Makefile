program: main.o algorithm.o
	g++ main.o algorithm.o -o program.exe

main.o: main.cpp
	g++ -c main.cpp

algorithm.o: algorithm.cpp
	g++ -c algorithm.cpp

clean:
	del *.o program.exe