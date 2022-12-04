all: word-count word-count-nested

.outputFolder:
	mkdir -p out

word-count: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm word-count.cpp -o out/word-count
	./out/word-count ./data .txt

word-count-nested: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm word-count.cpp -o out/word-count
	./out/word-count ./nestedData .txt