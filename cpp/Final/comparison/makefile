all: compare

.outputFolder:
	mkdir -p out

compare: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm comparison.cpp -o out/comparison
	clang++ -std=c++20 -lstdc++ -lm ../word-count.cpp -o ../out/word-count
	../out/word-count ../data .txt
	./out/comparison solution.txt ../output/output.txt