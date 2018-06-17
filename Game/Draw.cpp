#include "Draw.h"

const void Draw::DrawMatrix(Map* map)
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
}