a.out: main.o convex.o list.o
	g++ -std=c++11 main.o convex.o list.o -o a.out
main.o: main.cpp convex.h
	g++ -std=c++11 -c main.cpp
convex.o: convex.cpp convex.h list.h
	g++ -std=c++11 -c convex.cpp 
list.o: list.cpp list.h
	g++ -std=c++11 -c list.cpp
clean:
	rm -f *.o*
