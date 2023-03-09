output: main.o LZAlgorithm.o tree.o
	g++ main.o LZAlgorithm.o tree.o -o output.exe

main.o: main.cpp
	g++ -c main.cpp

LZAlgorithm.o: LZAlgorithm.cpp
	g++ -c LZAlgorithm.cpp

tree.o: tree.cpp
	g++ -c tree.cpp

clean:
	del *.o output.exe