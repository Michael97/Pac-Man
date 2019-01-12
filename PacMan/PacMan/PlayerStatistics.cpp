#include "PlayerStatistics.h"

PlayerStatistics::PlayerStatistics()
{
	iScore = 0;
	iLives = 3;
	iFruit = 0;
	iLevel = 1;
	iPellets = 246;
	bExtraLife = true;
}

int PlayerStatistics::GetScore()
{
	return iScore;
}

void PlayerStatistics::AddScore(int _score)
{
	iScore += _score;
	CanGetExtraLife();
}

int PlayerStatistics::GetLives()
{
	return iLives;
}

void PlayerStatistics::SubtractLives(int _lives)
{
	bPlayerDead = true;
	iLives -= _lives;
}

void PlayerStatistics::AddLives(int _lives)
{
	iLives += _lives;
}

int PlayerStatistics::GetFruit()
{
	return iFruit;
}

void PlayerStatistics::AddFruit(int _fruit)
{
	iFruit += _fruit;
}

int PlayerStatistics::GetLevel()
{
	return iLevel;
}

void PlayerStatistics::IncreaseLevel(int a_iAmount)
{
	iLevel += a_iAmount;
}

void PlayerStatistics::ResetPellets()
{
	iPellets = 246;
}

bool PlayerStatistics::PlayerDied()
{
	return bPlayerDead;
}

void PlayerStatistics::ResetPlayerDied()
{
	bPlayerDead = false;
}

int PlayerStatistics::GetPellets()
{
	return iPellets;
}

void PlayerStatistics::SubtractPellets(int a_iPellets)
{
	iPellets -= a_iPellets;
}

void PlayerStatistics::ResetGhostScore()
{
	iGhostScore = 100;
}

int PlayerStatistics::GetGhostScore()
{
	iGhostScore *= 2;
	return iGhostScore;
}

void PlayerStatistics::ResetStats()
{
	iScore = 0;
	iLives = 3;
	iFruit = 0;
	iLevel = 1;
	iPellets = 244;
	bExtraLife = true;
}

void PlayerStatistics::CanGetExtraLife()
{
	if (iScore >= 10000)
	{
		if (bExtraLife)
		{
			AddLives(1);
			bExtraLife = false;
		}
	}
}

