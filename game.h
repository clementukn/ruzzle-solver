#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
// size of the grid
// #define SIZE 4

// Keyborad sequences used to fill spec[4][4]
#define EMPTY	'O'
#define DWORD	'D'
#define TWORD	'T'
#define DLETTER	'Y'
#define TLETTER	'R'

class Game {
public:
	static const int gSize = 4;
	Game(std::string letters, std::string parameters);
	~Game() { }

	int findPath(std::string word);

private:
	int findPathFrom(int i, int j, std::string word, int (&path)[gSize][gSize]);
	int scoreOf(char l);
	int calculateScore(const int (&path)[gSize][gSize]);

	// struct Block {
	// 	char c; // letter
	// 	char p; // parameter (y, g, b r)
	// };

	char grid_[gSize][gSize];
	char param_[gSize][gSize];

	static const std::vector<std::pair<int, int>> directions_;
};

#endif