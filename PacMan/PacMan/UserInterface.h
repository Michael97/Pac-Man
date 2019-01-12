#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

//\===========================================================================================================================================
//\ Filename: UserInterface.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A file designed to render all the images and strings for the game
//\===========================================================================================================================================

#include "../PlayerStatistics.h"
#include "../HighScores.h"

class UserInterface
{
public:
	//functions that render images and text on screen when called
	void RenderSplashScreen();
	void RenderMainMenu();
	void RenderPauseMenu();
	void RenderHighScoresMenu();
	void RenderInGameScreen();
	void RenderDeadMenu();
	void RenderControlsMenu();
	void RenderAddHighScoresMenu(char * a_cLetter1, char * a_cLetter2, char * a_cLetter3);

	//Grabs the playerstatics as a pointer so we can access the variables and functions inside it.
	void SetPlayerStatistics(PlayerStatistics* a_pPlayerStatistics);

	//Grabs the players name
	void GetPlayerName(char a_cLetter1, char a_cLetter2, char a_cLetter3);

	// updates the highscores text file
	void UpdateHighScoreTextFile();
	
private:
	//a function that draws the score of the player
	void DrawScores();
	//a function that draws the lives of the player
	void DrawLives();
	//a function that draws the fruit (not yet implemented)
	void DrawFruit();

	void DrawLevel();

	//a function that draws the highscores
	void DrawHighScores();
	

private:
	//boolean value for if the game is paused
	bool isPaused;

	//a pointer to the player stats
	PlayerStatistics* pStats;

	//Highscore stuff
	//vector of chars for the name
	std::vector<char> name;

	//strings to store the file directory
	std::string writeHighScoresFileDirectory = "./build/highScores/WriteHighScores.txt";
	std::string readHighScoresFileDirectory = "./build/highScores/ReadHighScores.txt";


};

#endif // __USERINTERFACE_H__