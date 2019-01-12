//\===========================================================================================================================================
//\ Filename: main.cpp
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : main file that executes the code in order to run the game sucessfully.
//\===========================================================================================================================================

//includes to allow use of the UG Framework
#include "UGFW.h"
#include "UG_Defines.h"
#include "../Grid.h"
#include "../PacManController.h"
#include "../Blinky.h"
#include "../Pinky.h"
#include "../Inky.h"
#include "../Clyde.h"
#include "../Timer.h"
#include "../UserInterface.h"
#include "../GameState.h"
#include "../TargetTileSprite.h"
#include "../PlayerStatistics.h"

//\===========================================================================================================================================
//\ Main entry point into our application 
//\  argv - this is the number of command line arguments that are present when we open our application 
//\			if we open this exe by clicking on it with a mouse this number is 1. 
//\  argc - this is a varadic string argument, the number of items in the array is defined by the value in argv
//\===========================================================================================================================================
int main(int argv, char* argc[])
{
	// If statement used to create an instance of the framework
	// If this returns 0 the framework could not be created and
	// the application will terminate with an error state
	if (!UG::Create(464, 576, false, "Pacman", 100, 100)) return 1;

	//setting the font and size
	int font = UG::AddFont("./build/fonts/PacmanFont.ttf", 20);
	UG::SetFont(font);
	
	UG::SetBackgroundColor(UG::SColour(0, 0, 0, 0));

	GameState currentState = SPLASHSCREEN;
	PlayerStatistics playerStatistics;

	Timer fTimer;
	Grid grid;
	PacMan pacman;

	pacman.SetGrid(&grid);
	pacman.SetTimer(&fTimer);
	pacman.SetGameState(&currentState);
	pacman.SetPlayerStatistics(&playerStatistics);

	Blinky blinky;

	blinky.SetPacMan(&pacman);
	blinky.SetGrid(&grid);
	blinky.SetTimer(&fTimer);
	blinky.SetGameState(&currentState);
	
	Pinky pinky;

	pinky.SetPacMan(&pacman);
	pinky.SetGrid(&grid);
	pinky.SetTimer(&fTimer);
	pinky.SetGameState(&currentState);

	Inky inky;

	inky.SetPacMan(&pacman);
	inky.SetGrid(&grid);
	inky.SetBlinky(&blinky);
	inky.SetTimer(&fTimer);
	inky.SetGameState(&currentState);
	
	Clyde clyde;

	clyde.SetPacMan(&pacman);
	clyde.SetGrid(&grid);
	clyde.SetTimer(&fTimer);
	clyde.SetGameState(&currentState);

	pacman.SetSpriteID(grid.pacmanSpriteID);
	blinky.SetSpriteID(grid.blinkySpriteID);
	pinky.SetSpriteID(grid.pinkySpriteID);
	inky.SetSpriteID(grid.inkySpriteID);
	clyde.SetSpriteID(grid.clydeSpriteID);

	std::vector<Ghost*> vpGhosts;

	vpGhosts.push_back(&blinky);
	vpGhosts.push_back(&pinky);
	vpGhosts.push_back(&inky);
	vpGhosts.push_back(&clyde);

	fTimer.SetGhosts(vpGhosts);
	fTimer.SetPlayerStats(&playerStatistics);

	UserInterface userInterface;
	userInterface.SetPlayerStatistics(&playerStatistics);

	std::vector<char> vcName;

	char letter1 = 'A';
	char letter2 = 'A';
	char letter3 = 'A';

	char currentLetter = letter1;

	//a global iterator for choosing 
	int g_i = 1;

	float splashScreenTimer = 0.5f;
	// This is the start of our main game loop, we are using a do while loop (these loops are covered in a lecture!)
	do 
	{
		UG::ClearScreen();
		switch (currentState)
		{
		case SPLASHSCREEN:
			{
				userInterface.RenderSplashScreen();
			
				splashScreenTimer -= UG::GetDeltaTime();

				if (splashScreenTimer <= 0.0f)
					currentState = MAINMENU;

				break;
			}
		case MAINMENU:
			{
				userInterface.RenderMainMenu();

				//Play Button
				if (UG::WasKeyPressed(UG::KEY_1))
				{
					//This lot of code basically resets the map, stats and characters.
					playerStatistics.ResetStats();
					grid = Grid();

					grid.addCharacters(&blinky, &pinky, &inky, &clyde, &pacman);
					grid.prepareGrid();
				
					pacman.SetGridPosition(grid.findCharacterPosition(1));
					pacman.ResetWorldPosition();
					//ghost iterator so we know what ghost we are on
					int i = 1;
					for each (Ghost* ghost in vpGhosts)
					{
						i++;
						ghost->SetGridPosition(grid.findCharacterPosition(i));
						ghost->ResetWorldPosition();
						ghost->SetIsEaten(false);
					}
		
					currentState = INGAME;
				}
				//Highscores button
				if (UG::WasKeyPressed(UG::KEY_2))
				{
					currentState = HIGHSCORESMENU;
				}
				//Control button
				if (UG::WasKeyPressed(UG::KEY_3))
				{
					currentState = CONTROLSMENU;
				}
				//Exit to desktop button
				if (UG::WasKeyPressed(UG::KEY_4))
				{
					UG::Close();
				}
				
				break;
			}
		case INGAME:
			{
				userInterface.RenderInGameScreen();

				if (playerStatistics.PlayerDied())
				{
					pacman.SetGridPosition(grid.findCharacterPosition(1));
					pacman.ResetWorldPosition();
					//ghost iterator so we know what ghost we are on
					int i = 1;
					for each (Ghost* ghost in vpGhosts)
					{
						i++;
						ghost->SetGridPosition(grid.findCharacterPosition(i));
						ghost->ResetWorldPosition();
						ghost->SetIsEaten(false);
					}
					playerStatistics.ResetPlayerDied();
				}

				if (playerStatistics.GetLives() <= 0)
				{
					currentState = DEADMENU;
				}

				if (playerStatistics.GetPellets() <= 0)
				{
					playerStatistics.IncreaseLevel(1);
					playerStatistics.GetPellets();
					//restart level

					//This lot of code basically resets the map, stats and characters.
					grid = Grid();

					grid.addCharacters(&blinky, &pinky, &inky, &clyde, &pacman);
					grid.prepareGrid();

					pacman.SetGridPosition(grid.findCharacterPosition(1));
					pacman.ResetWorldPosition();
					//ghost iterator so we know what ghost we are on
					int i = 1;
					for each (Ghost* ghost in vpGhosts)
					{
						i++;
						ghost->SetGridPosition(grid.findCharacterPosition(i));
						ghost->ResetWorldPosition();
						ghost->SetIsEaten(false);
					}
				}

				// Pause button
				if (UG::WasKeyPressed(UG::KEY_P))
				{
					currentState = PAUSEMENU;
				}

				//Player Movement Controls
				if (UG::IsKeyDown(UG::KEY_DOWN))
					pacman.SetNextDirection(DOWN);

				if (UG::IsKeyDown(UG::KEY_UP))
					pacman.SetNextDirection(UP);

				if (UG::IsKeyDown(UG::KEY_RIGHT))
					pacman.SetNextDirection(RIGHT);

				if (UG::IsKeyDown(UG::KEY_LEFT))
					pacman.SetNextDirection(LEFT);

				fTimer.update();
			
				pacman.update(grid.pacmanSpriteID);
				blinky.update(grid.blinkySpriteID);
				pinky.update(grid.pinkySpriteID);
				inky.update(grid.inkySpriteID);
				clyde.update(grid.clydeSpriteID);
				grid.render();
				break;
			}
		case PAUSEMENU:
			{
				userInterface.RenderPauseMenu();

				//Resume Button
				if (UG::WasKeyPressed(UG::KEY_P) || UG::WasKeyPressed(UG::KEY_1))
				{
					currentState = INGAME;
					break;
				}
				//Quit to main menu button
				if (UG::WasKeyPressed(UG::KEY_2))
				{
					currentState = MAINMENU;
				}
				//Exit to desktop button
				if (UG::WasKeyPressed(UG::KEY_3))
				{
					UG::Close();
				}

				pacman.update(grid.pacmanSpriteID);
				blinky.update(grid.blinkySpriteID);
				pinky.update(grid.pinkySpriteID);
				inky.update(grid.inkySpriteID);
				clyde.update(grid.clydeSpriteID);
				grid.render();
				break;
			}

		case DEADMENU:
			{
				userInterface.RenderDeadMenu();

				//Restart Button
				if (UG::WasKeyPressed(UG::KEY_1))
				{
					currentState = INGAME;
					break;
				}
				//Highscores button
				if (UG::WasKeyPressed(UG::KEY_2))
				{
					currentState = ADDHIGHSCOREMENU;
				}
				//Exit to desktop button
				if (UG::WasKeyPressed(UG::KEY_3))
				{
					currentState = MAINMENU;
				}
				//Exit to desktop button
				if (UG::WasKeyPressed(UG::KEY_4))
				{
					UG::Close();
				}
				break;
			}
		case HIGHSCORESMENU:
			{
				userInterface.RenderHighScoresMenu();

				if (UG::WasKeyPressed(UG::KEY_1))
				{
					currentState = MAINMENU;
					break;
				}
				break;
			}
		case CONTROLSMENU:
			{
				userInterface.RenderControlsMenu();
				//Back Button
				if (UG::WasKeyPressed(UG::KEY_1))
				{
					currentState = MAINMENU;
					break;
				}
				break;
			}
		case ADDHIGHSCOREMENU:
			{
				userInterface.RenderAddHighScoresMenu(&letter1, &letter2, &letter3);

				if (UG::WasKeyPressed(UG::KEY_1))
					currentState = MAINMENU;

				//changes the currently selected letter to the one on the left (if there is one)
				if (UG::WasKeyPressed(UG::KEY_LEFT))
				{
					//minus one from the global iterator
					g_i--;
					//if g_i == 0 then we add 1 as the first letter starts at one
					if (g_i == 0)
						g_i++;

					if (g_i == 1)
						currentLetter = letter1;

					if (g_i == 2)
						currentLetter = letter2;

					if (g_i == 3)
						currentLetter = letter3;

				}
				
				//changes the currently selected letter to the one on the right (if there is one)
				if (UG::WasKeyPressed(UG::KEY_RIGHT))
				{
					//add one to the global iterator
					g_i++;
					//if g_i == 4 then we take away 1 as there are only 3 letters
					if (g_i == 4)
						g_i--;

					//depending on the iterator value set the currentLetter to the corresponding letter.
					if (g_i == 1)
						currentLetter = letter1;

					if (g_i == 2)
						currentLetter = letter2;

					if (g_i == 3)
						currentLetter = letter3;

					std::cout << g_i << std::endl;
				}

				//Changes the letters value downwards, in decending alphabetical order
				if (UG::WasKeyPressed(UG::KEY_UP))
				{
					//if the current letter is A, make the current letter Z.
					if (currentLetter == 'A')
					{
						currentLetter = 'Z';
					}
					else
						currentLetter--;
					
					if (g_i == 1)
						letter1 = currentLetter;

					if (g_i == 2)
						letter2 = currentLetter;

					if (g_i == 3)
						letter3 = currentLetter;
					
				}

				//Changes the letters value upwards, in acending alphabetical order
				if (UG::WasKeyPressed(UG::KEY_DOWN))
				{
					//if the current letter is Z, make the current letter A.
					if (currentLetter == 'Z')
					{
						currentLetter = 'A';
					}
					else
						currentLetter++;

					if (g_i == 1)
						letter1 = currentLetter;

					if (g_i == 2)
						letter2 = currentLetter;

					if (g_i == 3)
						letter3 = currentLetter;

				}

				//saves the selected letters as a name, and updates the highscores list
				if (UG::WasKeyPressed(UG::KEY_ENTER))
				{
					userInterface.GetPlayerName(letter1, letter2, letter3);
					userInterface.UpdateHighScoreTextFile();
					currentState = MAINMENU;
				}
				break;
			}
		default:
			break;
		}

	} while (UG::Process());

	//Close down the framework by calling dispose.
	UG::Dispose();

	return 0;
}