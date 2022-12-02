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
./run.sh

# OR 

valgrind --leak-check=yes ./out/word-count . .txt
```
