# Word Count

WordCount-project in C++ by Jakob Friedl (if20b089) and Philipp Haider (if20b097). This project was developed for the Functional Programming Course at UAS Technikum Wien in the winter-semester 2022/23. 

## Install dependencies
```bash
apt install libboost-filesystem-dev
apt install valgrind
```

## Compile

The Makefile compiles and runs the program and counts words in .txt files in the current working directory.

To compile the program without the Makefile, use:

```sh
clang++ -std=c++20 -lstdc++ -lm word-count.cpp 
./a.out <directory> <extension>
```

## Run Valgrind Memory Check

The `run.sh`-script will compile the program and run the valgrind memory check with the current directory(".") and ".txt" as file-extension.

```sh
sh run.sh

# OR 

valgrind --leak-check=yes ./out/word-count . .txt
```
## Test Script
The `test.sh`-script will compile the programm and do a run with nested folders, a run for a single file, a comparison between the solution and the output as well as the valgrind memory check.

```sh
sh test.sh
```

## Comparison Folder
The comparison folders includes a C++ programm to compare 2 Textfiles, the solution from moodle for the _tolower and a make file to compare the solutions. The make file compiles the comparison.cpp and the word-count.cpp first and then executes the comparison.