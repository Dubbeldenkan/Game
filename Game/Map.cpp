#include "Map.h"

Map::Map()
{
	srand(static_cast<unsigned int>(time(NULL)));
}

void Map::InitMap(GraphicsNS::Graphics* g)
{
	g->LoadImageFromFile("Map/Farmland.png", &_farmland, TILESIZE, TILESIZE);
	g->LoadImageFromFile("Map/Forest.png", &_forest, TILESIZE, TILESIZE);
	g->LoadImageFromFile("Map/Mountain.png", &_mountain, TILESIZE, TILESIZE);
	g->LoadImageFromFile("Map/Swamp.png", &_swamp, TILESIZE, TILESIZE);
	g->LoadImageFromFile("Map/Water.png", &_water, TILESIZE, TILESIZE);

	CreateMap();
}

int Map::GetTile(int x, int y)
{
	return _matrix[x][y];
}

void Map::SetTile(int x, int y, int tileType)
{
	_matrix[x][y] = tileType;
}

void Map::CreateMap()
{
	int definedTiles = 0;
	int randomNumberTiles = 
		static_cast<int>((MAPXSIZE - 2*_influenceDist)*(MAPYSIZE - 2*_influenceDist)*0.6);

	for (int x = 0; x < MAPXSIZE; x++)
	{
		for (int y = 0; y < MAPYSIZE; y++)
		{
			if (x < _mapBorder || (MAPXSIZE- x) < _mapBorder
				|| y < _mapBorder || (MAPYSIZE- y) < _mapBorder)
			{
				SetTile(x, y, TileType::Water);
			}
			else
			{
				SetTile(x, y, TileType::Undefined);
			}
		}
	}
	
	int randXPos;
	int randYPos;
	while (definedTiles < randomNumberTiles)
	{
		randXPos = rand() % (MAPXSIZE - _mapBorder) + _mapBorder;
		randYPos = rand() % (MAPYSIZE - _mapBorder) + _mapBorder;
		if (GetTile(randXPos, randYPos) == 0)
		{
			DefineTile(randXPos, randYPos);
			definedTiles++;
		}
	}

	for (int x = 0; x < MAPXSIZE; x++)
	{
		for (int y = 0; y < MAPYSIZE; y++)
		{
			if (GetTile(x, y) == Undefined)
			{
				DefineTile(x, y);
			}
		}
	}
}

///Definiera en tile baserad på omkringliggande tiles.
void Map::DefineTile(int xPos, int yPos)
{
	int forestTiles = rand() % _influenceDist;
	int grassTiles = rand() % _influenceDist;
	int mountainTiles = rand() % _influenceDist;
	int waterTiles = rand() % (_influenceDist - 1);

	for (int xDiff = -_influenceDist; xDiff < _influenceDist; xDiff++)
	{
		for (int yDiff = -_influenceDist; yDiff < _influenceDist; yDiff++)
		{
			int absDist = abs(xDiff) + abs(yDiff);
			if (absDist != 0)
			{
				int tileValue = GetTile(xPos + xDiff, yPos + yDiff);
				if (tileValue == TileType::FarmLand)
				{
					grassTiles += static_cast<int>((1 / (float) absDist) * _influenceDist);
				}
				else if (tileValue == TileType::Forest)
				{
					forestTiles += static_cast<int>((1 / (float) absDist) * _influenceDist);
				}
				else if (tileValue == TileType::Mountain)
				{
					mountainTiles += static_cast<int>((1 / (float) absDist) * _influenceDist);
				}
				else if (tileValue == TileType::Water)
				{
					waterTiles += static_cast<int>((1 / (float)absDist) * _influenceDist);
				}
			}
		}
	}
	
	int highestTileValue = grassTiles;
	int tileType = TileType::FarmLand;

	if (highestTileValue < forestTiles)
	{
		tileType = TileType::Forest;
		highestTileValue = forestTiles;
	}

	if (highestTileValue < mountainTiles)
	{
		tileType = TileType::Mountain;
		highestTileValue = mountainTiles;
	}

	if (highestTileValue < waterTiles)
	{
		tileType = TileType::Water;
		highestTileValue = waterTiles;
	}
		
	SetTile(xPos, yPos, tileType);
}

GraphicsNS::Image* Map::GetTileImage(int xPos, int yPos)
{
	GraphicsNS::Image* temp = &_water;

	switch (GetTile(xPos, yPos))
	{
	case TileType::FarmLand:
		temp = &_farmland;
		break;
	case TileType::Forest:
		temp = &_forest;
		break;
	case TileType::Mountain:
		temp = &_mountain;
		break;
	case TileType::Swamp:
		temp = &_swamp;
		break;
	case TileType::Water:
		temp = &_water;
		break;
	default:
		printf("Undefined tiletype");
		break;
	}

	return temp;
}