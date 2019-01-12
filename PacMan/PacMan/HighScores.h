#ifndef __HIGHSCORES_H__
#define __HIGHSCORES_H__
#include <vector>

class HighScores
{
public:
	void SaveStats(int a_iScore);

private:
	std::vector<char> letter;

	std::string writeHighScoresFileDirectory = "./build/highScores/WriteHighScores.txt";
	std::string readHighScoresFileDirectory = "./build/highScores/ReadHighScores.txt";
};

#endif // __HIGHSCORES_H__
