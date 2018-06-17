#include "Map.h"

Map::Map()
{
	srand(static_cast<unsigned int>(time(NULL)));
}

int Map::GetXMapSize()
{
	return _mapXSize;
}

int Map::GetYMapSize()
{
	return _mapYSize;
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
	int randomNumberTiles = static_cast<int>(_mapXSize*_mapYSize*0.6);

	for (int x = 0; x < _mapXSize; x++)
	{
		for (int y = 0; y < _mapYSize; y++)
		{
			if (x < _mapBorder || (_mapXSize - x) < _mapBorder
				|| y < _mapBorder || (_mapYSize - y) < _mapBorder)
			{
				SetTile(x, y, _waterTileValue);
			}
			else
			{
				SetTile(x, y, 0);
			}
		}
	}
	
	int randXPos;
	int randYPos;
	while (definedTiles < randomNumberTiles)
	{
		randXPos = rand() % (_mapXSize - _mapBorder) + _mapBorder;
		randYPos = rand() % (_mapYSize - _mapBorder) + _mapBorder;
		if (GetTile(randXPos, randYPos) == 0)
		{
			DefineTile(randXPos, randYPos);
			definedTiles++;
		}
	}

	for (int x = 0; x < _mapXSize; x++)
	{
		for (int y = 0; y < _mapYSize; y++)
		{
			if (GetTile(x, y) == 0)
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

	for (int xDiff = -_influenceDist; xDiff <= _influenceDist; xDiff++)
	{
		for (int yDiff = -_influenceDist; yDiff <= _influenceDist; yDiff++)
		{
			int absDist = abs(xDiff) + abs(yDiff);
			if (absDist != 0)
			{
				int tileValue = GetTile(xPos + xDiff, yPos + yDiff);
				if (tileValue == _grassTileValue)
				{
					grassTiles += static_cast<int>((1 / (float) absDist) * _influenceDist);
				}
				else if (tileValue == _forestTileValue)
				{
					forestTiles += static_cast<int>((1 / (float) absDist) * _influenceDist);
				}
				else if (tileValue == _mountainTileValue)
				{
					mountainTiles += static_cast<int>((1 / (float) absDist) * _influenceDist);
				}
				else if (tileValue == _waterTileValue)
				{
					waterTiles += static_cast<int>((1 / (float)absDist) * _influenceDist);
				}
			}
		}
	}
	
	int highestTileValue = grassTiles;
	int tileType = _grassTileValue;

	if (highestTileValue < forestTiles)
	{
		tileType = _forestTileValue;
		highestTileValue = forestTiles;
	}

	if (highestTileValue < mountainTiles)
	{
		tileType = _mountainTileValue;
		highestTileValue = mountainTiles;
	}

	if (highestTileValue < waterTiles)
	{
		tileType = _waterTileValue;
		highestTileValue = waterTiles;
	}
		
	SetTile(xPos, yPos, tileType);
}