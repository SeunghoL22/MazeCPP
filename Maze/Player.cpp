#include "pch.h"
#include "Player.h"
#include "Board.h"

Pos front[4] =
{
	Pos(-1,0), //UP
	Pos(0,-1), //LEFT
	Pos(1,0), //DOWN
	Pos(0,1) //RIGHT
};

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

bool Player::CanTurn(Pos pos)
{
	Pos turnPos = pos + front[_dir - 1];

	switch (_dir) 
	{
	case DIR_UP:
		if (CanGo(turnPos))
			return true;
		return false;
		break;

	case DIR_LEFT:
		if (CanGo(turnPos))
			return true;
		return false;
		break;

	case DIR_DOWN:
		if (CanGo(turnPos))
			return true;
		return false;
		break;

	case DIR_RIGHT:
		if (CanGo(turnPos))
			return true;
		return false;
		break;
	}
	
}

void Player::CalculatePath() //인공지능
{
	Pos pos = _pos;


	_path.clear();
	_path.push_back(pos);

	//목적지
	Pos dest = _board->GetExitPos();

	//for (int i = 0; i < 10; i++)
	//{
	//	pos += Pos(1, 0);
	//	_path.push_back(pos);
	//}

	while (pos != dest)
	{
		

		Pos nextPos = pos + front[_dir];
		Pos turnPos; //이거 지우고CanTurn 메소드를 만드는게 낫다
		switch (_dir)
		{
		case DIR_UP:
			turnPos = pos + Pos(0, -1);
			if (CanTurn(pos))
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
				_dir = (_dir - 1) % DIR_COUNT;
			break;

		case DIR_LEFT:
			turnPos = pos + Pos(+1, 0);
			if (CanTurn(pos))
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
				_dir = (_dir - 1) % DIR_COUNT;
			break;

		case DIR_DOWN:
			turnPos = pos + Pos(0, +1);
			if (CanTurn(pos))
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
				_dir = (_dir - 1) % DIR_COUNT;
			break;

		case DIR_RIGHT:
			turnPos = pos + Pos(-1, 0);
			if (CanTurn(pos))
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
				_dir=(_dir-1)%DIR_COUNT;
			break;
		}

	}
}

