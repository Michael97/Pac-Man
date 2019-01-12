#ifndef __COLLIDER_H__
#define __COLLIDER_H__

//\===========================================================================================================================================
//\ Filename: Collider.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class for colliders.
//\===========================================================================================================================================

#include "./Vector2.h"
#include <limits>

class Collider
{
public:
	//Constructor
	Collider(Vector2<float> _vector);
	~Collider();

	//Checks to see if a collision has occured
	bool CheckCollision(Collider other);

	//Returns the position of the collider
	Vector2<float> GetPosition() { return vector; }
	//Returns the half size of the collider
	Vector2<float> GetHalfSize() { return Vector2<float> (14 / 2.0f, 14 / 2.0f); }

private:
	Vector2<float> vector;
};

#endif // __COLLIDER_H__