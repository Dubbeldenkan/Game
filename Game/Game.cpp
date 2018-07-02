#include "Game.h"

Game::Game(HWND hWnd)
{
	//init rand
	srand(static_cast<unsigned int>(time(NULL)));

	_draw = Draw(&hWnd);
	_map.CreateMap();
}

void Game::Run()
{
	DrawScreen();
	// TODO: PrintDataToLog(tempGameTurn);
}


void Game::DrawScreen()
{

	_draw.DrawView(&_map);
}

void Game::CheckIfGameHasEnded()
{}