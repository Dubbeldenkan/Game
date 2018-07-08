#include "Draw.h"

Draw::Draw(HWND* hWnd)
{
	_g = new GraphicsNS::Graphics(*hWnd);
}

GraphicsNS::Graphics* Draw::GetGraphics()
{
	return _g;
}

void Draw::DrawScreen(DrawInput* dI)
{
	_g->Clear();
	_g->StartDrawing();
	DrawMap(dI->map, dI->player);
	//TODO lägg till gubbar 
	_g->StopDrawing();
	_g->Flip();
}

void Draw::DrawMap(Map* map, Player* player)
{
	for (int xIndex = player->GetViewPos().x; xIndex < (player->GetViewPos().x + Player::SCREENXSIZE); xIndex++)
	{
		for (int yIndex = player->GetViewPos().y; yIndex < (player->GetViewPos().y + Player::SCREENYSIZE); yIndex++)
		{
			_g->DrawTile(map->GetTileImage(xIndex, yIndex), 
				(xIndex - player->GetViewPos().x)*map->TILESIZE, (yIndex - player->GetViewPos().y)*map->TILESIZE, 0, 0);
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