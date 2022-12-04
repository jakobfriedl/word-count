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
### Makefile
The makefiles contains 2 options:
- make word-count 
    - compiles the program with the folder "data" which contains the sample data from Moodle and ".txt" as extension
- make word-count-nested
    - compiles the program with the folder-structure "nestedData" which contains 3 levels of folders and each contains the sample data from Moodle and ".txt" as extension
- make
    - without options, runs both "word-count" and "word-count-nested" 


## Run Valgrind Memory Check

The `run.sh`-script compiles the program and runs the valgrind memory check with the current directory and ".txt" as the program arguments.

```sh
sh run.sh

# OR 

valgrind --leak-check=yes ./out/word-count . .txt
```

## Test Script
The `test.sh`-script compiles the program and execute a run with nested folders, a run for a single file, a comparison between the solution and the output, as well as the valgrind memory check.

```sh
sh test.sh
```

## Comparison Folder
The comparison folder includes a C++ program to compare 2 Textfiles, the moodle lowercase-reference-file and a Makefile to compare the solutions. The make file compiles the comparison.cpp and then compares the most most recent output-file of word-count.cpp to the solution.txt-file.
