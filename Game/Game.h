#ifndef GAME_H
#define GAME_H

#define NOMINMAX

#include "Draw.h"
#include "Graphics.h"

#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>

#include <map>
#include <vector>
#include <string>

class Game
{

private:
	Draw _draw = Draw();
	Map _map = Map();

public:
	Game(HWND);
	~Game() {};

	void Run();

private:
	void CheckIfGameHasEnded();

	void DrawScreen();
};

#endif // !GAME_H