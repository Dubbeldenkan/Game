#include "Draw.h"

Draw::Draw(HWND* hWnd)
{
	_g = new GraphicsNS::Graphics(*hWnd);
	
	_farmland = _g->LoadImage("Farmland.png");
	_forest = _g->LoadImage("Forest.png");
	_mountain = _g->LoadImage("Mountain.png");
	_swamp = _g->LoadImage("Swamp.png");
	_water = _g->LoadImage("Water.png");
}

void Draw::DrawView(Map* map)
{	
	GraphicsNS::Image* temp = &_water;

	_g->Clear();
	_g->StartDrawing();
	for (int x = 0; x < map->GetXMapSize(); x++)
	{
		for (int y = 0; y < map->GetYMapSize(); y++)
		{
			switch (map->GetTile(x, y))
			{
			case map->TileType::FarmLand:
				temp = &_farmland;
				break;
			case map->TileType::Forest:
				temp = &_forest;
				break;
			case map->TileType::Mountain:
				temp = &_mountain;
				break;
			case map->TileType::Swamp:
				temp = &_swamp;
				break;
			case map->TileType::Water:
				temp = &_water;
				break;
			default:
				printf("Undefined tiletype");
				break;
			}
			_g->Draw(temp, x, y, 0.5);
		}
	}
	_g->StopDrawing();
	_g->Flip();
}


/*const void Draw::DrawMatrix(Map* map)
{
	for (int yPos = 0; yPos < map->GetYMapSize(); yPos++)
	{
		std::string row = "";
		for (int xPos = 0; xPos < map->GetXMapSize(); xPos++)
		{
			row = row + static_cast<char>(map->GetTile(xPos, yPos));
		}
		std::cout << row << "\n";
	}
}*/