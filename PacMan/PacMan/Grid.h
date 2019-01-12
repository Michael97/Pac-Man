#ifndef __GRID_H__
#define __GRID_H__

//\===========================================================================================================================================
//\ Filename: Grid.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class to create and store info for a grid.
//\===========================================================================================================================================

#include <array>
#include <string>
#include <iostream>
#include <UGFW.h>
#include <fstream>
#include <sstream>
#include "../Tile.h"
#include "../Vector2.h"

//map width is actually 28, but due to drawing 
//from the center this is the offset so it doesnt look off
#define MAP_WIDTH 29
#define MAP_HEIGHT 36
#define TILE_WIDTH 16
#define TILE_HEIGHT 16

#define WINDOW_SIZE_WIDTH MAP_WIDTH*TILE_HEIGHT
#define WINDOW_SIZE_HEIGHT MAP_HEIGHT*TILE_HEIGHT

//Forward Declaration
class Pinky;
class Inky;
class Clyde;
class PacMan;
class Blinky;	
class Grid
{
public:
	//Constrctor
	Grid();
	
	//Function to render the map
	void render();


	//Function to reset the attributes and sprites in the grid
	void RestartMap();

	//Returns the vector2 of the map reference
	Vector2<float> findCharacterPosition(int a_iMapReference);
	
	//gets and sets the charaters in the game
	void addCharacters(Blinky* _blinky, Pinky* _pinky,
		Inky* _inky, Clyde* _clyde, PacMan* _pacman);
	
	//prepares the grid for playing on
	void prepareGrid();

private:
	//Generaes the base grid
	void generateBaseGrid();

	//Reads the map text file and sets the tiles attributes
	void setAttributes();

	//Generates the sprites
	void generateSprites();

	//Loads the map
	void loadMap();

	//Finds and sets all neighbours for all tiles/nodes
	void setNeighbours();

	//Finds and saves the 2 portal nodes
	void savePortal(Vector2<float> _sourcePortal, Vector2<float> _neighbourPortal);
	
public:
	//Grid of tiles
	Tile mGrid[MAP_HEIGHT][MAP_WIDTH];
	bool bReset = false;
	//y is down and x across
	//MultiDimensional vector for the grids
	std::vector<int> map[MAP_HEIGHT][MAP_WIDTH];

	//sprite IDs for each character (this is kinda bad, should change it to smthing more efficent)
	int pacmanSpriteID;
	int pinkySpriteID;
	int inkySpriteID;
	int blinkySpriteID;
	int clydeSpriteID;

	//String for the map directory
	std::string mapFileDirectory = "./build/mapGeneration/Map.txt";

private:
	//Class pointers for the characters in the game
	Blinky* blinky;
	Pinky* pinky;
	Inky* inky;
	Clyde* clyde;
	PacMan* pacman;

};

#endif // __GRID_H__