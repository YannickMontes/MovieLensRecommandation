#Makefile

CXX = g++
CXXFLAGS = -Wall -std=c++11 -g -fpermissive

main: main.o User.o
	$(CXX) $(CXXFLAGS) -o main main.o User.o

main.o: main.cpp User.h Constantes.h
	$(CXX) $(CXXFLAGS) -c main.cpp

User.o: User.h
