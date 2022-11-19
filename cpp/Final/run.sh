clang++ -std=c++20 -lstdc++ -lm word-count.cpp -o out/word-count
valgrind --leak-check=yes ./out/word-count . .txt