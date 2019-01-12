#ifndef __BLINKY_H__
#define __BLINKY_H__

////////////////////////////////////////////////////////////
// File: Blinky.h
// Author: Michael Thomas
// Date Created: 14/10/2017
// Brief: A class for the ghost "Blinky".
////////////////////////////////////////////////////////////

#include "Ghost.h"

class Blinky : public Ghost
{
public:
	//Constructor
	Blinky();

	//Scatter function
	void Scatter();
	//Chase function
	void Chase();
};

#endif // __BLINKY_H__