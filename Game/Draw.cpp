#include "Draw.h"

Draw::Draw(HWND* hWnd)
{
	_g = new GraphicsNS::Graphics(*hWnd);
}

GraphicsNS::Graphics* Draw::GetGraphics()
{
	return _g;
}

void Draw::DrawGameBoard(DrawInput* dI)
{
	_g->Clear();
	_g->StartDrawing();
	DrawMap(dI->map);
	//TODO lägg till gubbar 
	_g->StopDrawing();
	_g->Flip();
}

void Draw::DrawMap(Map* map)
{
	for (int xIndex = 0; xIndex < map->MAPXSIZE; xIndex++)
	{
		for (int yIndex = 0; yIndex < map->MAPYSIZE; yIndex++)
		{
			_g->DrawTile(map->GetTileImage(xIndex, yIndex), xIndex*map->TILESIZE, yIndex*map->TILESIZE, 0, 0);
			//TODO här kan man lägga in olika riktningar på tiles
		}
	}
}

void Draw::DrawMovingObject(MovingObject* mo)
{
	if (mo->GetAnimationDirection() == (int)MovingObject::west)
	{
		_g->DrawAnimation(mo->GetImage(), (int)mo->GetPos().x, (int)mo->GetPos().y,
			(int)mo->GetAnimationState() + 8, true);
	}
	else
	{
		_g->DrawAnimation(mo->GetImage(), (int)mo->GetPos().x, (int)mo->GetPos().y,
			(int)mo->GetAnimationState() + (int)mo->GetAnimationDirection() * 4,
			false);
	}
}

void Draw::DrawGameObject(GameObject* object)
{
	_g->Draw(object->GetImage(), object->GetPos().x, object->GetPos().y, 1);
}