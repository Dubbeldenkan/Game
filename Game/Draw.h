#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <string>
#include <algorithm>

#include "Graphics.h"
#include "Map.h"
#include "GameObject.h"
#include "MovingObject.h"
#include "Player.h"

class Draw
{
public:
	struct DrawInput
	{
		Map* map;
		Player* player;
	};
private:
	GraphicsNS::Graphics* _g;
	
public:
	Draw() {};
	Draw(HWND*);
	~Draw() {};

	void DrawScreen(DrawInput*);
	GraphicsNS::Graphics* GetGraphics();

private:
	void DrawMap(Map*, Player*);
	void DrawGameObject(GameObject*);
	void DrawMovingObject(MovingObject*);
};

#endif // !DRAW_H