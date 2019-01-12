#ifndef __COORDTRANSLATOR_H__
#define __COORDTRANSLATOR_H__

//\===========================================================================================================================================
//\ Filename: CoordTranslator.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class for converting from grid position to world position
//\===========================================================================================================================================

#include "../Grid.h"
#include "../Vector2.h"

//Since the tiles are 16x16 we need to resize the coords to meet these specs
class CoordTranslator
{
public:
	static Vector2<float> translateToWorldPosition(Vector2<float> gridPosition)
	{
		gridPosition.x *= TILE_WIDTH;
		gridPosition.y *= TILE_HEIGHT;

		return gridPosition;
	}
};

#endif // __COORDTRANSLATOR_H__