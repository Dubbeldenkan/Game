#include "Game.h"

Game::Game(HWND hWnd)
{
	//init rand
	srand((unsigned int) time(NULL));

	_draw = Draw(&hWnd);
	_map.InitMap(_draw.GetGraphics());

	InitGame();
}

int Game::GetSleepTimeInMs()
{
	return _sleepTimeInMs;
}

void Game::Run()
{
	if(true)
	{
		//TODO
	}
	else
	{
		//game over
		_gameOver = true;
	}
}

void Game::DrawGameBoard()
{
	Draw::DrawInput dI;
	dI.map = &_map;
	_draw.DrawGameBoard(&dI);
}

Draw* Game::GetDraw()
{
	return &_draw;
}

bool Game::GetGameOver()
{
	return _gameOver;
}

void Game::InitGame()
{
	//TODO
}