#ifndef __INKY_H__
#define __INKY_H__

////////////////////////////////////////////////////////////
// File: Inky.h
// Author: Michael Thomas
// Date Created: 14/10/2017
// Brief: A class for the ghost "Inky".
////////////////////////////////////////////////////////////

#include "../Ghost.h"

class Inky : public Ghost
{
public:
	//Contructor
	Inky();
	
	//Scatter function
	void Scatter();

	//Chase Function
	void Chase();

	//function to grab and set blinkies entity class
	void SetBlinky(Entity* _blinky);

private:
	//blinkies entity class
	Entity* blinky;
};

#endif // __INKY_H__