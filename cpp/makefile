all: first funct funct_dat funct_data

.outputFolder:
	mkdir -p out

first: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm first.cpp -o out/first
	./out/first

funct: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm functional.cpp -o out/functional
	./out/functional

funct_dat: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm functional.cpp -o out/functional
	./out/functional ./Dat .txt

funct_data: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm functional.cpp -o out/functional
	./out/functional ./Data .txt