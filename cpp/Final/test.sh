#!/bin/bash

echo "Running tests..."

echo "Compiling..."
clang++ -std=c++20 -lstdc++ -lm word-count.cpp -o out/word-count
clang++ -std=c++20 -lstdc++ -lm comparison/comparison.cpp -o comparison/out/comparison

echo "word-count nestedData"
./out/word-count ./nestedData .txt

echo "word-count data"
./out/word-count ./data .txt

echo "comparison"
./comparison/out/comparison ./comparison/solution.txt ./output/output.txt

#echo "valgrind"
valgrind --leak-check=yes ./out/word-count . .txt