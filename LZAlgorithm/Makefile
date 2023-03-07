output: main.o LZAlgorithm.o
	g++ main.o LZAlgorithm.o -o output.exe

main.o: main.cpp
	g++ -c main.cpp

LZAlgorithm.o: LZAlgorithm.cpp
	g++ -c LZAlgorithm.cpp

clean:
	del *.o output.exe