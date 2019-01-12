#include "../Grid.h"
#include "../Blinky.h"
#include "../Pinky.h"
#include "../Inky.h"
#include "../Clyde.h"
#include "../PacManController.h"

//Runs all necassary functions to create a grid
Grid::Grid()
{
}

//Goes though the grid tiles and renders all necassary sprites into the game
void Grid::render()
{
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			int spriteID = mGrid[y][x].ID;


			if (map[y][x][3] == 1)
			{
				spriteID = pacman->UpdateSpriteID();
				pacmanSpriteID = spriteID;
				continue;
			}
			if (map[y][x][3] == 2)
			{
				spriteID = blinky->UpdateSpriteID();
				blinkySpriteID = spriteID;
				continue;
			}
			if (map[y][x][3] == 3)
			{
				spriteID = pinky->UpdateSpriteID();
				pinkySpriteID = spriteID;
				continue;
			}
			if (map[y][x][3] == 4)
			{
				spriteID = inky->UpdateSpriteID();
				inkySpriteID = spriteID;
				continue;
			}
			if (map[y][x][3] == 5)
			{
				spriteID = clyde->UpdateSpriteID();
				clydeSpriteID = spriteID;
				continue;
			}


			//Update the positions of everything that isnt pacman
			if (mGrid[y][x].canDraw)
			{
				//taking away the size height so it "draws" from the top left rather than bottom left
				UG::SetSpritePosition(spriteID, (float)x * TILE_WIDTH, (float)WINDOW_SIZE_HEIGHT - y * TILE_HEIGHT);
			}
		
			UG::DrawSprite(spriteID);
			
		}
	}
}

void Grid::RestartMap()
{
	void setAttributes();
	void generateSprites();
	
}

Vector2<float> Grid::findCharacterPosition(int mapReference)
{
	Vector2<float> position;
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (map[y][x][3] == mapReference)
			{
				position.x = (float)x;
				position.y = (float)y;
			}
		}
	}
	return position;
}

void Grid::addCharacters(Blinky* _blinky, Pinky* _pinky,
	Inky* _inky, Clyde* _clyde, PacMan* _pacman)
{
	blinky = _blinky;
	pinky = _pinky;
	inky = _inky;
	clyde = _clyde;
	pacman = _pacman;
}

//Generates empty tiles for the grid
void Grid::generateBaseGrid()
{
	for (int x = 0; x < MAP_WIDTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			mGrid[y][x] = Tile();
}

//Sets the tiles boolean values relative to their grids ID
void Grid::setAttributes()
{
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			//Tile Type
			switch (map[y][x][0])
			{
			case 0: //Empty tile - walkable
				mGrid[y][x].isWalkable = true;
				break;
			case 1: //Empty tile - unwalkable
				mGrid[y][x].isBlocking = true;
				break;
			case 2: //Portal
				mGrid[y][x].isWalkable = true;
				mGrid[y][x].isPortal = true;
				break;
			case 3:
				mGrid[y][x].isBlocking = true;
				break;
			case 4:
				mGrid[y][x].isBlocking = true;
				break;
			case 8: //Ghost Door
				mGrid[y][x].isDoor = true;
				mGrid[y][x].isHouseTile = true;
				break;
			case 9: //Ghost House
				mGrid[y][x].isHouseTile = true;
				break;
			default:
				break;
			}

			//Collectables
			switch (map[y][x][1])
			{
			case 1: //Dot
				mGrid[y][x].hasDot = true;
				break;
			case 2: //Power Pill
				mGrid[y][x].hasPowerPill = true;
				break;
			default:
				break;
			}

			//Junctions/Corners
			switch (map[y][x][2])
			{
			case 1:
				mGrid[y][x].isNode = true;
				break;
			case 2:
				mGrid[y][x].isNode = true;
				break;
			default:
				break;
			}

			switch (map[y][x][4])
			{
			case 2:
				mGrid[y][x].isBlinkyPOI = true;
				break;
			case 3:
				mGrid[y][x].isPinkyPOI = true;
				break;
			case 4:
				mGrid[y][x].isInkyPOI = true;
				break;
			case 5:
				mGrid[y][x].isClydePOI = true;
				break;
			case 6:
				mGrid[y][x].isHousePOI = true;
				break;
			default:
				break;
			}
		}
	}
}

//Draws sprites for each tile
void Grid::generateSprites()
{
	std::vector<int> viUpMovementSprites;
	std::vector<int> viDownMovementSprites;
	std::vector<int> viRightMovementSprites;
	std::vector<int> viLeftMovementSprites;
	std::vector<int> viFrightenedSprites;
	std::vector<int> viDeadSprites;

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			std::string spritePath;

			//Tile Type
			switch (map[y][x][0])
			{
			case 0: //Empty tile
				spritePath = "./build/images/empty.png";
				break;
			case 1: //Empty tile
				spritePath = "./build/images/empty.png";
				break;
			case 2: //Portal
				spritePath = "./build/images/empty.png";
				break;
			case 3: //Vertical Wall
				spritePath = "./build/images/VerticalWall.png";
				break;
			case 4: //Horizontal Wall
				spritePath = "./build/images/HorizontalWall.png";
				break;
			case 8: //Ghost Door
				spritePath = "./build/images/Door.png";
				break;
			case 9: //Ghost House
				spritePath = "./build/images/empty.png";
				break;
			default:
				break;
			}

			//Collectables
			switch (map[y][x][1])
			{
			case 1: //Dot
				spritePath = "./build/images/Dot.png";
				break;
			case 2: //Power Pill
				spritePath = "./build/images/PowerPill.png";
				break;
			default:
				break;
			}

			//Characters
			switch (map[y][x][3])
			{
			case 1: //Pacman
			{
				std::vector<int> viMovementSprites;

				viDeadSprites.clear();

				viMovementSprites.push_back(UG::CreateSprite("./build/images/Pac1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viMovementSprites.push_back(UG::CreateSprite("./build/images/Pac2.png", TILE_WIDTH, TILE_HEIGHT, true));
				viMovementSprites.push_back(UG::CreateSprite("./build/images/Pac3.png", TILE_WIDTH, TILE_HEIGHT, true));

				viDeadSprites.push_back(UG::CreateSprite("./build/images/Pac1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viDeadSprites.push_back(UG::CreateSprite("./build/images/Pac2.png", TILE_WIDTH, TILE_HEIGHT, true));
				viDeadSprites.push_back(UG::CreateSprite("./build/images/Pac3.png", TILE_WIDTH, TILE_HEIGHT, true));
				viDeadSprites.push_back(UG::CreateSprite("./build/images/Pac4.png", TILE_WIDTH, TILE_HEIGHT, true));
				viDeadSprites.push_back(UG::CreateSprite("./build/images/Pac5.png", TILE_WIDTH, TILE_HEIGHT, true));
				viDeadSprites.push_back(UG::CreateSprite("./build/images/Pac6.png", TILE_WIDTH, TILE_HEIGHT, true));
				viDeadSprites.push_back(UG::CreateSprite("./build/images/Pac7.png", TILE_WIDTH, TILE_HEIGHT, true));

				pacman->SetSprites(viMovementSprites, viDeadSprites);

				pacman->SetCurrentSpriteID(viMovementSprites[0]);
				pacmanSpriteID = viMovementSprites[0];
				break;
			}
			case 2: //Blinky
			{
				viUpMovementSprites.clear();
				viDownMovementSprites.clear();
				viRightMovementSprites.clear();
				viLeftMovementSprites.clear();
				viFrightenedSprites.clear();
				viDeadSprites.clear();

				viUpMovementSprites.push_back(UG::CreateSprite("./build/images/BlinkyUp1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viUpMovementSprites.push_back(UG::CreateSprite("./build/images/BlinkyUp2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viDownMovementSprites.push_back(UG::CreateSprite("./build/images/BlinkyDown1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viDownMovementSprites.push_back(UG::CreateSprite("./build/images/BlinkyDown2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viRightMovementSprites.push_back(UG::CreateSprite("./build/images/BlinkyRight1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viRightMovementSprites.push_back(UG::CreateSprite("./build/images/BlinkyRight2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viLeftMovementSprites.push_back(UG::CreateSprite("./build/images/BlinkyLeft1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viLeftMovementSprites.push_back(UG::CreateSprite("./build/images/BlinkyLeft2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened2.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened3.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened4.png", TILE_WIDTH, TILE_HEIGHT, true));

				viDeadSprites.push_back(UG::CreateSprite("./build/images/GhostDead.png", TILE_WIDTH, TILE_HEIGHT, true));
				//viDeadSprites.push_back(UG::CreateSprite("./build/images/GhostDead.png", TILE_WIDTH, TILE_HEIGHT, true));

				blinky->SetSprites(viUpMovementSprites, viDownMovementSprites, viRightMovementSprites,
					viLeftMovementSprites, viFrightenedSprites, viDeadSprites);

				blinky->SetCurrentSpriteID(viDownMovementSprites[0]);
				blinkySpriteID = viDownMovementSprites[0];
				break;
			}
			case 3: //Pinky
				viUpMovementSprites.clear();
				viDownMovementSprites.clear();
				viRightMovementSprites.clear();
				viLeftMovementSprites.clear();
				viFrightenedSprites.clear();
				viDeadSprites.clear();

				viUpMovementSprites.push_back(UG::CreateSprite("./build/images/PinkyUp1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viUpMovementSprites.push_back(UG::CreateSprite("./build/images/PinkyUp2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viDownMovementSprites.push_back(UG::CreateSprite("./build/images/PinkyDown1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viDownMovementSprites.push_back(UG::CreateSprite("./build/images/PinkyDown2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viRightMovementSprites.push_back(UG::CreateSprite("./build/images/PinkyRight1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viRightMovementSprites.push_back(UG::CreateSprite("./build/images/PinkyRight2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viLeftMovementSprites.push_back(UG::CreateSprite("./build/images/PinkyLeft1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viLeftMovementSprites.push_back(UG::CreateSprite("./build/images/PinkyLeft2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened2.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened3.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened4.png", TILE_WIDTH, TILE_HEIGHT, true));

				viDeadSprites.push_back(UG::CreateSprite("./build/images/GhostDead.png", TILE_WIDTH, TILE_HEIGHT, true));
				//viDeadSprites.push_back(UG::CreateSprite("./build/images/GhostDead.png", TILE_WIDTH, TILE_HEIGHT, true));

				pinky->SetSprites(viUpMovementSprites, viDownMovementSprites, viRightMovementSprites,
					viLeftMovementSprites, viFrightenedSprites, viDeadSprites);

				pinky->SetCurrentSpriteID(viDownMovementSprites[0]);
				pinkySpriteID = viDownMovementSprites[0];
				break;
			case 4: //Inky
				viUpMovementSprites.clear();
				viDownMovementSprites.clear();
				viRightMovementSprites.clear();
				viLeftMovementSprites.clear();
				viFrightenedSprites.clear();
				viDeadSprites.clear();

				viUpMovementSprites.push_back(UG::CreateSprite("./build/images/InkyUp1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viUpMovementSprites.push_back(UG::CreateSprite("./build/images/InkyUp2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viDownMovementSprites.push_back(UG::CreateSprite("./build/images/InkyDown1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viDownMovementSprites.push_back(UG::CreateSprite("./build/images/InkyDown2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viRightMovementSprites.push_back(UG::CreateSprite("./build/images/InkyRight1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viRightMovementSprites.push_back(UG::CreateSprite("./build/images/InkyRight2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viLeftMovementSprites.push_back(UG::CreateSprite("./build/images/InkyLeft1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viLeftMovementSprites.push_back(UG::CreateSprite("./build/images/InkyLeft2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened2.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened3.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened4.png", TILE_WIDTH, TILE_HEIGHT, true));

				viDeadSprites.push_back(UG::CreateSprite("./build/images/GhostDead.png", TILE_WIDTH, TILE_HEIGHT, true));
				//viDeadSprites.push_back(UG::CreateSprite("./build/images/GhostDead.png", TILE_WIDTH, TILE_HEIGHT, true));

				inky->SetSprites(viUpMovementSprites, viDownMovementSprites, viRightMovementSprites,
					viLeftMovementSprites, viFrightenedSprites, viDeadSprites);

				inky->SetCurrentSpriteID(viDownMovementSprites[0]);
				inkySpriteID = viDownMovementSprites[0];
				break;
			case 5: //Clyde
				viUpMovementSprites.clear();
				viDownMovementSprites.clear();
				viRightMovementSprites.clear();
				viLeftMovementSprites.clear();
				viFrightenedSprites.clear();
				viDeadSprites.clear();

				viUpMovementSprites.push_back(UG::CreateSprite("./build/images/ClydeUp1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viUpMovementSprites.push_back(UG::CreateSprite("./build/images/ClydeUp2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viDownMovementSprites.push_back(UG::CreateSprite("./build/images/ClydeDown1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viDownMovementSprites.push_back(UG::CreateSprite("./build/images/ClydeDown2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viRightMovementSprites.push_back(UG::CreateSprite("./build/images/ClydeRight1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viRightMovementSprites.push_back(UG::CreateSprite("./build/images/ClydeRight2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viLeftMovementSprites.push_back(UG::CreateSprite("./build/images/ClydeLeft1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viLeftMovementSprites.push_back(UG::CreateSprite("./build/images/ClydeLeft2.png", TILE_WIDTH, TILE_HEIGHT, true));

				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened1.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened2.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened3.png", TILE_WIDTH, TILE_HEIGHT, true));
				viFrightenedSprites.push_back(UG::CreateSprite("./build/images/Frightened4.png", TILE_WIDTH, TILE_HEIGHT, true));

				viDeadSprites.push_back(UG::CreateSprite("./build/images/GhostDead.png", TILE_WIDTH, TILE_HEIGHT, true));
				//viDeadSprites.push_back(UG::CreateSprite("./build/images/GhostDead.png", TILE_WIDTH, TILE_HEIGHT, true));

				clyde->SetSprites(viUpMovementSprites, viDownMovementSprites, viRightMovementSprites,
					viLeftMovementSprites, viFrightenedSprites, viDeadSprites);

				clyde->SetCurrentSpriteID(viDownMovementSprites[0]);
				clydeSpriteID = viDownMovementSprites[0];
				break;
			default:
				break;
			}
	
			//Creates the sprite and save the sprite id to mGrid[y][x].ID
			mGrid[y][x].ID = UG::CreateSprite(spritePath.c_str(), TILE_WIDTH, TILE_HEIGHT, true);
			
			//ok for now but needs to be changed to something more efficent
			switch (map[y][x][3])
			{
			case 1:
				pacmanSpriteID = mGrid[y][x].ID;
				break;
			case 2:
				blinkySpriteID = mGrid[y][x].ID;
				break;
			case 3:
				pinkySpriteID = mGrid[y][x].ID;
				break;
			case 4:
				inkySpriteID = mGrid[y][x].ID;
				break;
			case 5:
				clydeSpriteID = mGrid[y][x].ID;
				break;
			}
		}
	}
}

void Grid::loadMap()
{
	//open a stream to the map file
	std::ifstream mapFile(mapFileDirectory);

	//if it cant open the file return a failure
	if (mapFile.fail())
	{
		std::cout << "Could not load mapFile " << mapFileDirectory << std::endl;
	}
	else
	{
		std::string oneLine;
		bool readData = false;
		int y = -1;

		//while we can get a line from the file, we store that content in "oneLine"
		while (getline(mapFile, oneLine))
		{
			//erase the new line character from oneLine
			oneLine.erase(std::remove(oneLine.begin(), oneLine.end(), '\n'), oneLine.end());

			//are we at the map bit yet?
			if (readData)
			{
				y++;

				std::string token;
				std::istringstream iss(oneLine);

				int x = -1;
				//while there are still spilt characters to convert
				while (std::getline(iss, token, ','))
				{
					x++;

					auto viMapCodes = std::vector<int>();
					viMapCodes.reserve(token.size());
					//char is represented as an ASCII value.

					for (char c : token) {
						if (isdigit(c)) viMapCodes.push_back(c - '0');
						//else throw std::runtime_error("it wasn't a digit! halp!!");
					}

					//Convert from character to integer
					//map[y][x] = std::stoi(token, nullptr, 0);

					map[y][x] = viMapCodes;
				}
			}

			if (oneLine == "MapStart")
				readData = true;
		}
	}

	mapFile.close();
}

void Grid::setNeighbours()
{
	Vector2<float> portal1 = Vector2<float>(0, 0);
	Vector2<float> portal2 = Vector2<float>(0, 0);

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			

			//if the tile is a node
			if (mGrid[y][x].isBlocking)
				continue;

			if (mGrid[y][x].isPortal)
			{
				if (portal1 == Vector2<float>(0.f, 0.f))
					portal1 = Vector2<float>((float)x, (float)y);

				else if (portal2 == Vector2<float>(0.f, 0.f))
					portal2 = Vector2<float>((float)x, (float)y);
			}

			//If there is not a wall above the node
			if (!mGrid[y - 1][x].isBlocking)
			{
				Step* step = new Step();
				step->position = Vector2<float>((float)x, (float)y - 1);
				if (mGrid[y][x + 1].isHouseTile)
					step->isHouseTile = true;
				mGrid[y][x].neighbourSteps[0] = step;
			}

			//If there is not a wall below the node
			if (!mGrid[y + 1][x].isBlocking)
			{
				Step* step = new Step();
				step->position = Vector2<float>((float)x, (float)y + 1);
				if (mGrid[y][x + 1].isHouseTile)
					step->isHouseTile = true;
				mGrid[y][x].neighbourSteps[1] = step;
			}

			//If there is not a wall left of the node
			if (!mGrid[y][x - 1].isBlocking)
			{
				Step* step = new Step();
				step->position = Vector2<float>((float)x - 1, (float)y);
				if (mGrid[y][x + 1].isHouseTile)
					step->isHouseTile = true;
				mGrid[y][x].neighbourSteps[2] = step;
			}

			//If there is not a wall right of the node
			if (!mGrid[y][x + 1].isBlocking)
			{
				Step* step = new Step();
				step->position = Vector2<float>((float)x + 1, (float)y);
				if (mGrid[y][x + 1].isHouseTile)
					step->isHouseTile = true;
				mGrid[y][x].neighbourSteps[3] = step;
			}

			//Portals
			if (portal1 != Vector2<float> (0,0) && portal2 != Vector2<float>(0,0))
			{
				savePortal(portal1, portal2);
				savePortal(portal2, portal1);
			}
		}
	}
}

void Grid::savePortal(Vector2<float> _sourcePortal, Vector2<float> _neighbourPortal)
{
	Step* step = new Step();
	
	step->position = Vector2<float>(_neighbourPortal.x, _neighbourPortal.y);
	step->portal = true;

	if (_sourcePortal.y < _neighbourPortal.y) //portal is above so we save it in the Down position
		mGrid[(int)_sourcePortal.y][(int)_sourcePortal.x].neighbourSteps[1] = step;

	if (_sourcePortal.y > _neighbourPortal.y) //portal is below so we save it in the Up position
		mGrid[(int)_sourcePortal.y][(int)_sourcePortal.x].neighbourSteps[0] = step;

	if (_sourcePortal.x < _neighbourPortal.x) //portal is on the Left so we save it in the Right position
		mGrid[(int)_sourcePortal.y][(int)_sourcePortal.x].neighbourSteps[3] = step;

	if (_sourcePortal.x > _neighbourPortal.x) //portal is on the Right so we save it in the Left position
		mGrid[(int)_sourcePortal.y][(int)_sourcePortal.x].neighbourSteps[2] = step;
}

void Grid::prepareGrid()
{
	loadMap();
	generateBaseGrid();
	setAttributes();
	setNeighbours();
	generateSprites();
}
