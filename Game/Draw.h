#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <string>
#include <algorithm>

#include "Graphics.h"
#include "Map.h"
#include "GameObject.h"
#include "MovingObject.h"

class Draw
{
public:
	struct DrawInput
	{
		Map* map;
	};
private:
	GraphicsNS::Graphics* _g;
	
public:
	Draw() {};
	Draw(HWND*);
	~Draw() {};

	void DrawGameBoard(DrawInput*);
	GraphicsNS::Graphics* GetGraphics();

private:
	void DrawMap(Map*);
	void DrawGameObject(GameObject*);
	void DrawMovingObject(MovingObject*);
};

#endif // !DRAW_H