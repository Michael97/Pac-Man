#include "PathScore.h"

PathScore::PathScore()
	: PathScore(0, 0)
{

}

PathScore::PathScore(int a_iMovement, int a_iHeuristics)
{
	iMovement = a_iMovement;
	iHeuristics = a_iHeuristics;
}

int PathScore::GetTotal() const
{
	return iMovement + iHeuristics;
}

int PathScore::GetMovement()
{
	return iMovement;
}

void PathScore::SetMovement(int a_iMovement)
{
	iMovement = a_iMovement;
}

int PathScore::GetHeuristics()
{
	return iHeuristics;
}

void PathScore::SetHeuristics(int a_iHeuristics)
{
	iHeuristics = a_iHeuristics;
}
