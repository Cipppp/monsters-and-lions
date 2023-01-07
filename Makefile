finalPrices: main.cpp
	rm -f ./data/generated/finalPrices.csv

	g++ -std=c++11 main.cpp -o main && ./main