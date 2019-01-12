#ifndef __TIMER_H__
#define __TIMER_H__

//\===========================================================================================================================================
//\ Filename: Timer.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A timer class designed to be a global timer so that most time related insidances happen at the same time
//\===========================================================================================================================================
#include <vector>
#include "UGFW.h"
#include "UG_Defines.h"
#include "../GameState.h"
#include "../PlayerStatistics.h"

//Forward declartion of Ghost class
class Ghost;
class Timer
{
public:
	//Constructor
	Timer();
	
	//update function that is called at the end of everytime that the main function completes
	void update();

	//function that grabs and sets the ghosts in a vector of ghosts pointers
	void SetGhosts(std::vector<Ghost*> _ghosts);

	//Change state to frightened Mode
	void SetFrightenedMode();

	//Boolean functions that return the current mode
	bool FrighenedMode();
	bool ChaseMode();
	bool ScatterMode();

	void SetPlayerStats(PlayerStatistics* a_pPlayerStats);

	void AddGhostScore();
	void ResetGhostScore();

private:
	//function that starts all of the timers
	void startTimers();

	//private timers that run when called
	void chaseTimer();
	void scatterTimer();
	void frightenedTimer();

private:
	//Vector of ghost pointers
	std::vector<Ghost*> vpGhosts;

	//Booleans for which mode the ghosts are in
	bool bChaseMode;
	bool bScatterMode;
	bool bFrightenedMode;

	//Timers for the ghosts
	float fFrightenedTime;
	float fChaseTime;
	float fScatterTime;
	float fHouseTime;

	//iterator to keep track of the ghost timers
	int i;

	int iGhostScore;

	//pointer for game state
	GameState* pGameState;
	PlayerStatistics* pPlayerStats;
};

#endif // __TIMER_H__