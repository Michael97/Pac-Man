#ifndef __ASTAR_H__
#define __ASTAR_H__

//\===========================================================================================================================================
//\ Filename: AStar.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class that generates a route for the AI through A* pathfinding
//\===========================================================================================================================================

#include "AStar.h"
#include "../Vector2.h"
#include "../Entity.h"
#include "../Step.h"
#include "../PathScore.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdlib.h>
#include <map>
#include <limits>

class AStar
{
public:
	//Constructors
	AStar();
	AStar(Entity* _entity, Vector2<float> _destination);

private:
	//Creates a path
	void Path();

	//Compute the heuristics and return it as an int
	int ComputeHeuristics(Vector2<float> _position, Vector2<float> _destination);

	//After we found a path we gotta recontruct it
	std::vector<Vector2<float>> ReconstructPath(Step* _currentStep);
	//Finds the quickest step based off the score
	std::vector<Step*> StepsWithLowestFScoreVal();

	//checks to see if the step actually exists
	bool StepExistsInVector(Step* step, std::vector<Step*> steps);
	void CantComputePath();

public:
	std::vector<Vector2<float>> totalPath;

private:
	Entity* ghost;

	Vector2<float> destination;
	Vector2<float> source;

	int movementValue = 1;

	std::vector<Step*> closed;
	std::vector<Step*> open;

	Step* stepBehind;

	std::map<Step*, Step*> cameFrom;
	std::map<Step*, int> gScore;
	std::map<Step*, int> fScore;
};

#endif // __ASTAR_H__