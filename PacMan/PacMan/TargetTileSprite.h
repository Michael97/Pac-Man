#ifndef __TARGETTILESPRITE_H__
#define __TARGETTILESPRITE_H__

//\===========================================================================================================================================
//\ Filename: Vector2.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class that creates a sprite and places itself at the target location of the selected ghost. Purely for debugging and testing purposes
//\===========================================================================================================================================

#include "Entity.h"
#include "../Vector2.h"
#include "../CoordTranslator.h"

class TargetTileSprite : public Entity
{
public:
	//Constructor
	TargetTileSprite();

	//unused
	void frightened();
	void flipDirection();

	//A function that grabs the vector2 of a point and places itself there
	void Target(Vector2<float> _location);

	//unused
	bool canMoveToTargetTile(Vector2<float> _targetGridPosition);
};

#endif // __TARGETTILESPRITE_H__