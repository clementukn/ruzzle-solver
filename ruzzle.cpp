#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <map>

#include "game.h"


int main(int argc, char **argv)
{
	if (argc < 2) {
		std::cout << "Please provide the dictionary file as argument.\n";
		return 1;
	}

	// ifstream dic ("/usr/share/dict/words");
	std::string dicFilename(argv[1]);
	std::ifstream dic (dicFilename);
	if (!dic.is_open()) {
		std::cout << "Couldn't open the dictionary file.\n";
		return 1;
	}

	int gridSize = Game::gSize;
	std::string letters(""), parameters("");
	while (letters.size() != gridSize * gridSize) {
		std::cout << "What does the grid look like (left to right and up to down, ex : ARTFSKDI...):\n";
		std::cin >> letters;
	}
	while (parameters.size() != gridSize * gridSize) {
		std::cout << "Enter specific parameters for the grid : (ex : YBOOOOGR...)\n";
		std::cin >> parameters;
	}
	
	std::multimap<int, std::string, std::greater<int>> solutions;
	Game grid(letters, parameters);

	clock_t starts = clock();
	// For every word of the dic, try to find a path
	while (dic.good()) {
		std::string word;
		getline (dic, word);
		if (word.size() <= 1) continue;

		// upper case the word to match letters of the grid
		std::transform(word.begin(), word.end(), word.begin(), ::toupper);
		int score = grid.findPath(word);
		if (score > 0) {
			solutions.insert(std::make_pair(score, word));
		}
	}
	dic.close();
	
	clock_t end = clock();
	for (auto& sol : solutions) {
		std::cout << sol.second << " : " << sol.first << '\n';
	}

	std::cout << "computed in " << double(end - starts) / CLOCKS_PER_SEC << '\n';
}