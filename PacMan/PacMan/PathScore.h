#ifndef __PATHSCORE_H__
#define __PATHSCORE_H__

//\===========================================================================================================================================
//\ Filename: PlayerStatistics.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class that determines the score of a step class.
//\===========================================================================================================================================
class PathScore 
{
public:
	//Constructor
	PathScore();

	//sets intital values
	PathScore(int movement, int heuristics);

	//Returns the total score
	int GetTotal() const;

	//Returns teh movement score
	int GetMovement();

	//Sets the movement variable
	void SetMovement(int a_iMovement);

	//Returns the heuristics score
	int GetHeuristics();

	//Sets the heuristics score
	void SetHeuristics(int a_iHeuristics);

private:
	int iMovement;
	int iHeuristics;
};

#endif // __PATHSCORE_H__