#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

//\===========================================================================================================================================
//\ Filename: GameState.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class for the gamestate
//\===========================================================================================================================================

enum GameState
{
	SPLASHSCREEN,
	MAINMENU,
	INGAME,
	PAUSEMENU,
	DEADMENU,
	HIGHSCORESMENU,
	CONTROLSMENU,
	ADDHIGHSCOREMENU
};

#endif //__GAMESTATE_H__