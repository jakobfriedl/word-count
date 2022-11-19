all: first funct funct_dat funct_data opt_data opt_dat opt_funct

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

opt_dat: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm functional_opt.cpp -o out/functional_opt
	./out/functional_opt ./Dat .txt

opt_data: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm functional_opt.cpp -o out/functional_opt
	./out/functional_opt ./Data .txt

opt_funct: .outputFolder
	clang++ -std=c++20 -lstdc++ -lm functional_opt_funct.cpp -o out/functional_opt_funct
	./out/functional_opt_funct ./Data .txt