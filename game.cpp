#include "game.h"


const std::vector<std::pair<int, int>> Game::directions_{
	{-1, 0}, {-1, +1}, {0, +1}, {+1, +1}, {+1, 0}, {+1, -1}, {0, -1}, {-1, -1}
};

Game::Game(std::string letters, std::string parameters) {
	for (int i = 0; i < gSize * gSize; ++i) {
		// grid_[i / gSize][i % gSize] = (Block) {letters[i], parameters[i]};
		grid_[i / gSize][i % gSize] = letters[i];
		param_[i / gSize][i % gSize] = parameters[i];
	}
}


int Game::findPath(std::string word) {
	int path[4][4] = {0};
	for (int i = 0; i < gSize; i++) {
		for (int j = 0; j < gSize; j++) {
			if (grid_[i][j] == word[0]) {
				return findPathFrom(i, j, word.substr(1, word.size() - 1), path);
			}
		}
	}
	return 0;
}


// Recursive function that finds the path for a given word
// Return the score of the path if succeeded, -1 otherwise
// path[][] is the easiest struct to keep track of path, and as it's cheap can be passed by val
int Game::findPathFrom(int i, int j, std::string word, int (&path)[gSize][gSize]) {
	// Mark this step in the path
	path[i][j] = 1;

	if (word.size() == 0) {
		return calculateScore(path);
	}

	int score = 0, max_score = 0;
	for (auto& d : directions_) {
		int x = i + d.first;
		int y = j + d.second;
		if (x >= 0 && y >= 0 && x < gSize && y < gSize
			&& path[x][y] != 1 && grid_[x][y] == word[0]) {
			score = findPathFrom(x, y, word.substr(1, word.size() - 1), path);
			if (score > max_score) {
				max_score = score;
			}
		}
	}
	
	// the last step was a dead-end
	path[i][j] = 0;
	return max_score;
}

// default letter's score
int Game::scoreOf(char l) {
		switch (l) {
			case 'D':
				return 2;
				break;
			case 'M':
				return 3;
				break;
			case 'K':
				return 5;
				break;
			case 'Y':
			case 'X':	
			case 'W':
			case 'C':
			case 'B':
			case 'P':
			case 'H':
				return 4;
				break;
			default:
				return 1;
				break;
		}
}

// Calculate the score for a given path
// Cheaper to do it at the end than along the way because of no of dead-ends
int Game::calculateScore(const int (&path)[gSize][gSize]) {
	int length = 0; // bonus points for length
	int score = 0;
	int coeffL = 1, coeffD = 0, coeffT = 0;
	for (int i = 0; i < gSize; i++)
		for (int j = 0; j < gSize; j++)
			if (path[i][j] == 1) {
				length++;
				coeffL = 1;
				// Double Word
				if (param_[i][j] == DWORD)
					coeffD++;
				// Triple Word
				if (param_[i][j] == TWORD)
					coeffT++;
				// Double Letter
				if (param_[i][j] == DLETTER)
					coeffL = 2;
				// Triple Letter
				else if(param_[i][j] == TLETTER)
					coeffL = 3;
				score += (coeffL * scoreOf(grid_[i][j]));
				
			}
	if (coeffD > 0)
		score *= coeffD * 2;
	if (coeffT > 0)
		score *= coeffT * 3;
		
	// Bonus points for length
	if (length >= 7)
		score += 15;
	else if (length == 6)
		score += 10;
	else if (length == 5)
		score += 5;
		
	return score;
}