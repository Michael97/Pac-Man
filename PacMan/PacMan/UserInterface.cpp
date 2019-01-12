//\===========================================================================================================================================
//\ Filename: UserInterface.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A file designed to render all the images and strings for the game
//\===========================================================================================================================================

#include "UserInterface.h"
#include "UGFW.h"

#include <sstream>
#include <fstream>
#include <array>
#include <iostream>
#include <iomanip> 
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>

///////////////// Rendering Functions //////////////////
void UserInterface::RenderPauseMenu()
{
	int logo = UG::CreateSprite("./build/images/PauseMenu.png", 464, 576, false);
	UG::SetSpritePosition(logo, 0, 576);
	UG::DrawSprite(logo);
}

void UserInterface::RenderHighScoresMenu()
{
	int logo = UG::CreateSprite("./build/images/HighScoresMenu.png", 464, 576, false);
	UG::SetSpritePosition(logo, 0, 576);
	UG::DrawSprite(logo);

	DrawHighScores();
}

void UserInterface::RenderInGameScreen()
{
	int logo = UG::CreateSprite("./build/images/InGameStuff.png", 464, 576, false);
	UG::SetSpritePosition(logo, 0, 576);
	UG::DrawSprite(logo);

	DrawScores();
	DrawLives();
	DrawLevel();
}

void UserInterface::RenderDeadMenu()
{
	int logo = UG::CreateSprite("./build/images/DeadMenu.png", 464, 576, false);
	UG::SetSpritePosition(logo, 0, 576);
	UG::DrawSprite(logo);
}

void UserInterface::RenderControlsMenu()
{
	int logo = UG::CreateSprite("./build/images/ControlsMenu.png", 464, 576, false);
	UG::SetSpritePosition(logo, 0, 576);
	UG::DrawSprite(logo);

	UG::DrawString("Back", 128, 200, 1U, UG::SColour(255, 255, 255, 255));
}


void UserInterface::RenderSplashScreen()
{
	int logo = UG::CreateSprite("./build/images/Splashscreen.png", 464, 576, false);
	UG::SetSpritePosition(logo, 0, 576);
	UG::DrawSprite(logo);
}

void UserInterface::RenderMainMenu()
{
	int logo = UG::CreateSprite("./build/images/MainMenu.png", 464, 576, false);
	UG::SetSpritePosition(logo, 0, 576);
	UG::DrawSprite(logo);

	UG::DrawString("Play", 128, 200, 1U, UG::SColour(255, 255, 255, 255));
	UG::DrawString("HighScores", 128, 150, 1U, UG::SColour(255, 255, 255, 255));
	UG::DrawString("Controls", 128, 100, 1U, UG::SColour(255, 255, 255, 255));
	UG::DrawString("Exit", 128, 50, 1U, UG::SColour(255, 255, 255, 255));
}

void UserInterface::RenderAddHighScoresMenu(char * a_cLetter1, char * a_cLetter2, char * a_cLetter3)
{
	int logo = UG::CreateSprite("./build/images/HighScoresMenu.png", 464, 576, false);
	UG::SetSpritePosition(logo, 0, 576);
	UG::DrawSprite(logo);

	std::ostringstream ssConverter;

	ssConverter << *a_cLetter1 << " " << *a_cLetter2 << " " << *a_cLetter3;

	UG::DrawString(ssConverter.str().c_str(), 128, 200, 1U, UG::SColour(255, 255, 255, 255));

	UG::DrawString("Press Enter to finalize your name!", 32, 50, 1U, UG::SColour(255, 255, 255, 255));

}

////////////////////////////////////////////////////////////////

//Assigns playerstats
void UserInterface::SetPlayerStatistics(PlayerStatistics * a_pPlayerStatistics)
{
	pStats = a_pPlayerStatistics;
}

//converts the score to a string
void UserInterface::DrawScores()
{
	std::ostringstream ssConverter;

	ssConverter << "Score: " << pStats->GetScore();
	
	UG::DrawString(ssConverter.str().c_str(), 16, 540, 1U, UG::SColour(255, 255, 255, 255));
}

//converts the lives to a string
void UserInterface::DrawLives()
{
	std::ostringstream ssConverter;

	ssConverter << "Lives: " << pStats->GetLives();

	UG::DrawString(ssConverter.str().c_str(), 350, 540, 1U, UG::SColour(255, 255, 255, 255));
}

void UserInterface::DrawLevel()
{
	std::ostringstream ssConverter;

	ssConverter << "Level: " << pStats->GetLevel();

	UG::DrawString(ssConverter.str().c_str(), 210, 540, 1U, UG::SColour(255, 255, 255, 255));
}

//Draw highscores
void UserInterface::DrawHighScores()
{
	//open a stream to the map file
	std::ifstream highScoresFile(readHighScoresFileDirectory);

	//if it cant open the file return a failure
	if (highScoresFile.fail())
	{
		std::cout << "Could not load mapFile " << readHighScoresFileDirectory << std::endl;
	}
	else
	{
		std::string oneLine;

		int y = 0;
		//while we can get a line from the file, we store that content in "oneLine"
		while (getline(highScoresFile, oneLine))
		{
			//erase the new line character from oneLine
			oneLine.erase(std::remove(oneLine.begin(), oneLine.end(), '\n'), oneLine.end());
		
			y++;
			std::string token;
			std::istringstream iss(oneLine);

			
			//while there are still spilt characters to convert
			while (std::getline(iss, token))
			{
				std::string finalString = std::to_string(y) + ". " + token;

				UG::DrawString(finalString.c_str(), 70, 450 - (y * 25), 1U, UG::SColour(255, 255, 255, 255));
			}
		}
	}
	highScoresFile.close();
}

//Converts the 3 chars to a vector of chars.
void UserInterface::GetPlayerName(char a_cLetter1, char a_cLetter2, char a_cLetter3)
{
	name.erase(name.begin(), name.end());
	name.push_back(a_cLetter1);
	name.push_back(a_cLetter2);
	name.push_back(a_cLetter3);
}

void UserInterface::UpdateHighScoreTextFile()
{
	//create the string we are gonna save
	std::string sStats (name.begin(), name.end());
	sStats += ", ";
	sStats += std::to_string(pStats->GetScore());

	//opens files
	std::ifstream readHighScoresFile(readHighScoresFileDirectory); //file to read from
	std::ofstream writeHighScoresFile(writeHighScoresFileDirectory); //creating a temp file

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
		//string that holds the string of the line being read
		std::string oneLine;
		
		//y is the line number we are on (limit is 10 as that is the number of highscores
		int y = 0;

		//if the score has already been updated we dont want to update it again.
		bool hasUpdated = false;

		//while we can get a line from the file, we store that content in "oneLine"
		while (getline(readHighScoresFile, oneLine))
		{
			//erase the new line character from oneLine
			oneLine.erase(std::remove(oneLine.begin(), oneLine.end(), '\n'), oneLine.end());

			y++;

			//token of the oneLine string
			std::string token;
			//istringstream of oneline so we can use it in getline
			std::istringstream iss(oneLine);

			//this is how many tokens there are in y
			int x = 0;

			//while there are still spilt characters to convert
			while (std::getline(iss, token, ','))
			{
				x++;
				//convert the string of numbers to a int
				int iHighScore = std::atoi(token.c_str());

				//the second token will always be a number so we can change it from a string to an int for comparing
				if (x == 2 && pStats->GetScore() > iHighScore && y != 10)
				{
					if (hasUpdated)
					{
						writeHighScoresFile << oneLine << std::endl;
					}
					//if the score is higher and we havent updated the score yet then we update it!
					if (!hasUpdated)
					{
						hasUpdated = true;
						//by also writing the score it beat I can keep the scores in order by just not drawing the last score in the text file,
						//therefore deleting it from the file.
						writeHighScoresFile << sStats << std::endl;
						writeHighScoresFile << oneLine << std::endl;
					}
				}
				//if we are on the score and we havent reached 10 highscores then
				else if (x == 2 && y != 10)
					writeHighScoresFile << oneLine << std::endl;

			}
		}

	}
	//close the files
	readHighScoresFile.close();
	writeHighScoresFile.close();

	//delete the reading file
	std::remove(readHighScoresFileDirectory.c_str());
	//rename the writing file to the reading file
	std::rename(writeHighScoresFileDirectory.c_str(), readHighScoresFileDirectory.c_str());	
}