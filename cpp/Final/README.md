# Word Count in C++
Project from Friedl Jakob if20b089 and Haider Philipp if20b097.

## Compile Programm
The Makefile compiles and runs the programm with the current directory(".") and ".txt" as extension, use 'make'.

If you want to compile the programm by yourself use:

    clang++ -std=c++20 -lstdc++ -lm word-count.cpp 
	./a.out <directory> <fileextension>

## Valgrind Memory Check
The "run.sh" script will compile the program and run the valgrind memory check with the current directory(".") and ".txt" as file-extension.

    valgrind --leak-check=yes ./out/word-count . .txt