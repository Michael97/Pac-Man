#ifndef __CLYDE_H__
#define __CLYDE_H__

////////////////////////////////////////////////////////////
// File: Clyde.h
// Author: Michael Thomas
// Date Created: 14/10/2017
// Brief: A class for the ghost "Clyde".
////////////////////////////////////////////////////////////

#include "../Ghost.h"

class Clyde : public Ghost
{
public:
	//Constructor
	Clyde();

	//Scatter function
	void Scatter();

	//Chase function
	void Chase();
};

#endif // __CLYDE_H__