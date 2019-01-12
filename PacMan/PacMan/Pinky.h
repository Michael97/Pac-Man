#ifndef __PINKY_H__
#define __PINKY_H__

////////////////////////////////////////////////////////////
// File: Pinky.h
// Author: Michael Thomas
// Date Created: 14/10/2017
// Brief: A class for the ghost "Pinky".
////////////////////////////////////////////////////////////

#include "../Ghost.h"

class Pinky : public Ghost
{
public:
	//Constructor
	Pinky();
#
	//Scatter function
	void Scatter();

	//Chase function
	void Chase();
};

#endif // __PINKY_H__