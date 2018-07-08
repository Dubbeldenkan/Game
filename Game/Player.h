#ifndef PLAYER_H
#define PLAYER_H

// TODO dela upp Player i AI och Human

#include "HelpStructs.h"
#include "Map.h"

class Player
{
public:
	static const int SCREENXSIZE = 30; //defined in tiles
	static const int SCREENYSIZE = 20;
	//TODO anv�nd SCREENSIZE f�r att skriva storleken p� f�nstret och sedan att man i varje loop kolla om man ska flytta sk�rmen.
	Player(bool);
	
	enum MoveEnum { east, south, west, north };
	void SetLocalPlayerMovement(Player::MoveEnum, bool);
	void MoveScreen();
	TupleInt GetViewPos();

private:
	const bool _human;
	TupleInt _viewPos;

	MoveEnum _scrollDir;
	bool _scrollingScreen = false;
};

#endif // !PLAYER_H