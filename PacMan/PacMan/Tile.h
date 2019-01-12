#ifndef __TILE_H__
#define __TILE_H__

//\===========================================================================================================================================
//\ Filename: Tile.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A tile class that holds variables for specific tiles.
//\===========================================================================================================================================
#include <vector>
#include "../Step.h"

class Tile
{
public:
	//Boolean vales for tile types
	bool isBlocking;
	bool isWalkable;

	//Boolean values for collectables
	bool hasDot;
	bool hasPowerPill;

	//Boolean value for portals
	bool isPortal;

	//Boolean Values for house tiles 
	bool isHouseTile;
	bool isDoor;

	//Boolean value for if this is a node
	bool isNode;

	//Boolean values for point of interests.
	bool isPinkyPOI;
	bool isBlinkyPOI;
	bool isInkyPOI;
	bool isClydePOI;
	bool isHousePOI;

	//Boolean value for candraw
	bool canDraw = true;

	//Vector of pointer Steps, grabs info on neighbours needed for AStar Pathfinding
	std::vector<Step*> neighbourSteps = {
		nullptr, nullptr, nullptr, nullptr
	};

	//The spriteID of the tile (this will be used to draw the sprite)
	int ID;
};

#endif // __TILE_H__