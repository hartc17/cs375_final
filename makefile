all:	main.o
	g++ main.o -o main

main.o:	main.cpp RBTree.h
	g++ -c main.cpp

clean:
	rm -f *.o main
