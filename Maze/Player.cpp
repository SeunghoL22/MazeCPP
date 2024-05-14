#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>


void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	//CalculatePath_RightHand(); //우수법
	CalculatePath_BFS();
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

void Player::CalculatePath_RightHand() //인공지능
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
		Pos turnPos = pos + front[(_dir - 1) % 4];
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
				_dir = (_dir + 1) % DIR_COUNT;
			break;
		}

	}
}

void Player::CalculatePath_BFS()
{
	Pos pos = _pos;
	Pos dest = _board->GetExitPos(); //목적지

	Pos front[4] =
	{
		Pos(-1,0), //UP
		Pos(0,-1), //LEFT
		Pos(1,0), //DOWN
		Pos(0,1) //RIGHT
	};

	_path.clear();
	_path.push_back(pos);

	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));
	vector<vector<int>> dist(size, vector<int>(size, -1));
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));


	queue<Pos> q;
	q.push(pos);
	dist[pos.y][pos.x] = 0;
	parent[pos.y][pos.x] = pos; //시작점은 자기 자신에 의해서 발견된다
	discovered[pos.y][pos.x] = true;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		if (pos == dest) //도착점을 기준으로는 계산하지 않는다
			break;

		for (int32 dir = 0; dir < 4; dir++) //동서남북 체크
		{
			Pos there = pos + front[dir];
			if (CanGo(there) == false) //갈 수 없는 블럭은 continue
				continue;
			if (discovered[there.y][there.x] == true) //이미 발견했으면 continue
				continue;

			q.push(there);
			discovered[there.y][there.x] = true; //발견도장 찍어줍시다
			parent[there.y][there.x] = pos;
			dist[there.y][there.x] = dist[pos.y][pos.x] + 1;
		}
	}

	_path.clear();
	pos = dest; //거꾸로 path에 기록

	while (true)
	{
		_path.push_back(pos);
		if (pos == parent[pos.y][pos.x])
			break;
		pos = parent[pos.y][pos.x];
	}

	//std::reverse(_path.begin(), _path.end()); 이렇게 하면 큐 뒤집어져서 간단히 해결
	vector<Pos> temp(_path.size());
	for (int i = 0; i < _path.size(); i++)
	{
		temp[i] = _path[_path.size() - 1 - i];
	}
	_path = temp;




	/*
	* 스택으로 해결
	Pos test = _board->GetExitPos();
	stack<Pos> reverse_path;

	while (test != _board->GetEnterPos())
	{
		reverse_path.push(test);
		test = parent[test.y][test.x];
	}

	while (reverse_path.empty() == false)
	{
		_path.push_back(reverse_path.top());
		reverse_path.pop();
	}*/

}

