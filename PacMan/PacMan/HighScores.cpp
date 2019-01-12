#include "HighScores.h"
#include <sstream>
#include <fstream>
#include <array>
#include <iostream>
#include <iomanip> 

void HighScores::SaveStats(int a_iScore)
{
	std::string sStats (letter.begin(), letter.end());

	sStats += ", ";
	sStats += std::to_string(a_iScore);

	std::ifstream readHighScoresFile(readHighScoresFileDirectory); //file to read from
	std::ofstream writeHighScoresFile(writeHighScoresFileDirectory); //temp file

	//if it cant open the file return a failure
	if (readHighScoresFile.fail())
	{
		std::cout << "Could not load mapFile " << readHighScoresFileDirectory << std::endl;
	}
	//if it cant open the file return a failure
	else if (writeHighScoresFile.fail())
	{
		std::cout << "Could not load mapFile " << writeHighScoresFileDirectory << std::endl;
	}

	else
	{
		std::string oneLine;
		//y is the line number we are on
		int y = 0;
		//if the score has already been updated we dont want to update it again.
		bool hasUpdated = false;

		//while we can get a line from the file, we store that content in "oneLine"
		while (getline(readHighScoresFile, oneLine))
		{
			//erase the new line character from oneLine
			oneLine.erase(std::remove(oneLine.begin(), oneLine.end(), '\n'), oneLine.end());

			y++;

			std::string token;
			std::istringstream iss(oneLine);

			//this is how many tokens there are in y
			int x = 0;

			//while there are still spilt characters to convert
			while (std::getline(iss, token, ','))
			{
				x++;
				//the second token will always be a number so we can change it from a string to an int for comparing
				if (x == 2)
				{
					//convert the string of numbers to a int
					int iHighScore = atoi(token.c_str());

					//if the score is higher and we havent updated the score yet then we update it!
					if (a_iScore < iHighScore && !hasUpdated)
					{
						oneLine = sStats;
						hasUpdated = true;
					}
					writeHighScoresFile << oneLine + "/n";
				}
			}
		}
	}
}
