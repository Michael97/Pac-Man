#ifndef __STEP_H__
#define __STEP_H__

//\===========================================================================================================================================
//\ Filename: Step.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class created to hold the vital information needed to use a * pathfinding
//\===========================================================================================================================================

#include "../Vector2.h"
#include "../PathScore.h"

class Step
{
public:
	//Constructor
	Step();

	//functions that grab the vector2 of the step
	Step(Vector2<float> _position);
	Step(Vector2<float>* _position);

	//operator overload to compare 2 steps
	bool operator>(const Step& _step) const;

public:
	//Vector2 of step
	Vector2<float> position;
	
	//Step* for a parent step (if there is one)
	Step* parentStep = nullptr;

	//score for the step
	PathScore score;

	//Booleans for different tiles
	bool portal;
	bool isHouseTile;
};

#endif // __STEP_H__