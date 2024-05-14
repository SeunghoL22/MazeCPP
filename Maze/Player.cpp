#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>


void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	//CalculatePath_RightHand(); //�����
	CalculatePath_BFS();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathindex >= _path.size())
		return;


	_sumTick += deltaTick;

	if (_sumTick >= MOVE_TICK) //MOVE_TICK��ŭ�� �ð��� �귯�� ���� ����
	{
		//����
		_sumTick = 0;  //ƽ �ʱ�ȭ
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

void Player::CalculatePath_RightHand() //�ΰ�����
{
	Pos pos = _pos;


	_path.clear();
	_path.push_back(pos);

	//������
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
			//������ �ȵǴϱ� �������� ���°ſ���
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
	Pos dest = _board->GetExitPos(); //������

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
	parent[pos.y][pos.x] = pos; //�������� �ڱ� �ڽſ� ���ؼ� �߰ߵȴ�
	discovered[pos.y][pos.x] = true;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		if (pos == dest) //�������� �������δ� ������� �ʴ´�
			break;

		for (int32 dir = 0; dir < 4; dir++) //�������� üũ
		{
			Pos there = pos + front[dir];
			if (CanGo(there) == false) //�� �� ���� ���� continue
				continue;
			if (discovered[there.y][there.x] == true) //�̹� �߰������� continue
				continue;

			q.push(there);
			discovered[there.y][there.x] = true; //�߰ߵ��� ����ݽô�
			parent[there.y][there.x] = pos;
			dist[there.y][there.x] = dist[pos.y][pos.x] + 1;
		}
	}

	_path.clear();
	pos = dest; //�Ųٷ� path�� ���

	while (true)
	{
		_path.push_back(pos);
		if (pos == parent[pos.y][pos.x])
			break;
		pos = parent[pos.y][pos.x];
	}

	//std::reverse(_path.begin(), _path.end()); �̷��� �ϸ� ť ���������� ������ �ذ�
	vector<Pos> temp(_path.size());
	for (int i = 0; i < _path.size(); i++)
	{
		temp[i] = _path[_path.size() - 1 - i];
	}
	_path = temp;




	/*
	* �������� �ذ�
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

