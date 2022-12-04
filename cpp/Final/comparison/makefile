all: compare

.outputFolder:
	mkdir -p out

compare: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm comparison.cpp -o out/comparison
	./out/comparison solution.txt ../output/output.txt