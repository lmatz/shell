test: main.o Builtin.o Interpreter.o execute.o
	g++ -o test main.o Builtin.o Interpreter.o execute.o

main.o:main.cpp
	g++ -c main.cpp

Interpreter.o:Interpreter.cpp Interpreter.h 
	g++ -c Interpreter.cpp 

Builtin.o:Builtin.cpp Builtin.h 
	g++ -c Builtin.cpp 

execute.o:execute.cpp execute.h 
	g++ -c execute.cpp
