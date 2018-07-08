#include "Player.h"

Player::Player(bool human) : _human(human)
{
	_viewPos = TupleInt(0, 0);
}

void Player::SetLocalPlayerMovement(Player::MoveEnum moveInput, bool keyDown)
{
	_scrollingScreen = keyDown;
	_scrollDir = moveInput;
}

void Player::MoveScreen()
{
	if (_scrollingScreen)
	{
		switch (_scrollDir)
		{
		case Player::east:
			if (_viewPos.x < (Map::MAPXSIZE - SCREENXSIZE))
			{
				_viewPos.x++;
			}
			else 
			{
				_scrollingScreen = false;
			}
			break;
		case Player::south:
			if (_viewPos.y < (Map::MAPYSIZE - SCREENYSIZE))
			{
				_viewPos.y++;
			}
			else
			{
				_scrollingScreen = false;
			}
			break;
		case Player::west:
			if (0 < _viewPos.x)
			{
				_viewPos.x--;
			}
			else
			{
				_scrollingScreen = false;
			}
			break;
		case Player::north:
			if (0 < _viewPos.y)
			{
				_viewPos.y--;
			}
			else
			{
				_scrollingScreen = false;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		_scrollingScreen = false;
	}
}

TupleInt Player::GetViewPos()
{
	return _viewPos;
}