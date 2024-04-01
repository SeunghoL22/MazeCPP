#include "pch.h"
#include "Player.h"
#include "Board.h"


void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	CalculatePath();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathindex >= _path.size())
		return;


	_sumTick += deltaTick;

	if (_sumTick >= MOVE_TICK) //MOVE_TICK만큼의 시간이 흘러야 로직 실행
	{
		//로직
		_sumTick = 0;  //틱 초기화
		// 
		_pos = _path[_pathindex];
		_pathindex++;
	}
}

Pos Player::GetPos()
{
	return _pos;
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	if (tileType == TileType::EMPTY)
		return true;
	else
		return false;
}

void Player::CalculatePath() //인공지능
{
	Pos pos = _pos;


	_path.clear();
	_path.push_back(pos);

	//목적지
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos(-1,0), //UP
		Pos(0,-1), //LEFT
		Pos(1,0), //DOWN
		Pos(0,1) //RIGHT
	};

	while (pos != dest)
	{
		Pos nextPos = pos + front[_dir];
		Pos turnPos = pos + front[(_dir-1)%4];
		switch (_dir)
		{
		case DIR_UP:
			if (CanGo(turnPos))
			{
				pos = turnPos;
				_path.push_back(pos);
				_dir = (_dir - 1) % DIR_COUNT;
			}
			else if (CanGo(nextPos))
			{
				pos = nextPos;
				_path.push_back(pos);
			}
			else
				_dir = (_dir + 1) % DIR_COUNT;
				//오른쪽 안되니까 왼쪽으로 도는거에요
			break;

		case DIR_LEFT:
			if (CanGo(turnPos))
			{
				pos = turnPos;
				_path.push_back(pos);
				_dir = (_dir - 1) % DIR_COUNT;
			}
			else if (CanGo(nextPos))
			{
				pos = nextPos;
				_path.push_back(pos);
			}
			else
				_dir = (_dir + 1) % DIR_COUNT;
			break;

		case DIR_DOWN:
			if (CanGo(turnPos))
			{
				pos = turnPos;
				_path.push_back(pos);
				_dir = (_dir - 1) % DIR_COUNT;
			}
			else if (CanGo(nextPos))
			{
				pos = nextPos;
				_path.push_back(pos);
			}
			else
				_dir = (_dir + 1) % DIR_COUNT;
			break;

		case DIR_RIGHT:
			if (CanGo(turnPos))
			{
				pos = turnPos;
				_path.push_back(pos);
				_dir = (_dir - 1) % DIR_COUNT;
			}
			else if (CanGo(nextPos))
			{
				pos = nextPos;
				_path.push_back(pos);
			}
			else
				_dir=(_dir+1)%DIR_COUNT;
			break;
		}

	}
}

