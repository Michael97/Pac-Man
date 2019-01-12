#ifndef __PLAYERSTATISTICS_H__
#define __PLAYERSTATISTICS_H__

//\===========================================================================================================================================
//\ Filename: PlayerStatistics.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class to hold the player stats in and functions to change the values
//\===========================================================================================================================================
#include "../GameState.h"

class PlayerStatistics
{
public:
	//Constructor
	PlayerStatistics();

	//Returns the score as an int
	int GetScore();
	//adds the amount entered onto the score.
	void AddScore(int a_iScore);

	//Returns the lives as an int
	int GetLives();
	//subtracts the amount entered from lives
	void SubtractLives(int a_iLives);
	//adds the amount entered onto lives
	void AddLives(int a_iLives);

	//returns the amount of fruit eaten as int
	int GetFruit();
	//adds the amount entered onto the fruit
	void AddFruit(int a_iFruit);

	//returns the level we are on
	int GetLevel();
	//increases the level number by the inputted amount
	void IncreaseLevel(int a_iAmount);

	void ResetPellets();

	bool PlayerDied();
	void ResetPlayerDied();

	int GetPellets();

	void SubtractPellets(int a_iPellets);

	void ResetGhostScore();

	int GetGhostScore();

	//Resets the stats
	void ResetStats();

	void CanGetExtraLife();

private:
	//Private variables for stats
	int iScore;
	int iLives;
	int iFruit;
	int iLevel;
	int iPellets;

	int iGhostScore;

	bool bPlayerDead;

	bool bExtraLife;
};

#endif // __PLAYERSTATISTICS_H__
