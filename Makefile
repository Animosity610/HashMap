output: main.o hashmap.o
	g++ hashmap.o main.o -o hotelFinder
main.o: main.cpp
	g++ -std=c++1y -c main.cpp
hashmap.o: hashmap.cpp hashmap.h
	g++ -std=c++17 -c hashmap.cpp
clean:
	rm *.o hotelFinder

