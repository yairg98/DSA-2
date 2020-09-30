# makefile for testing

all: model.exe

model.exe: model.o
	g++ -o model.exe model.o hash.o

model.o: model.cpp hash.o
	g++ -c model.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o modelDebug.exe model.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~