#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>


void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	//CalculatePath_RightHand(); //�����
	//CalculatePath_BFS();
	CalculatePath_AStar();
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
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));


	queue<Pos> q;
	q.push(pos);
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


// BFS ���ͽ�Ʈ��� �������� ������ ����

// ä�� ����
// -�Ա����� �󸶳� �������ִ���
// - �ⱸ���� �󸶳� �������ִ���

struct PQNode
{
	PQNode(int32 f, int32 g, Pos pos) : f(f), g(g), pos(pos) { }
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const {return f > other.f;}
	
	int32 f;
	int32 g;
	Pos pos;
};

void Player::CalculatePath_AStar() //���ͽ�Ʈ�� �ⱸ�� ������ �߰��� ��.
{
	// F = G + H �̷��� ���� �ű�� ����� �������̸� �������� ��ȣ�� ���� ������ �� ����
	// F = ���� ���� (���� ���� ����)
	// G = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ���, �� g�� ��� �Ǿ����� ���ͽ�Ʈ���� �� �� �ִ�
	// H = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ���

	Pos start = _pos;
	Pos dest = _board->GetExitPos(); //������

	Pos front[8] =
	{
		Pos(-1,0), //UP
		Pos(0,-1), //LEFT
		Pos(1,0), //DOWN
		Pos(0,1), //RIGHT
		Pos(-1,-1), //UP_LEFT
		Pos(1,-1), //DOWN_LEFT
		Pos(1,1), //DOWN_RIGHT
		Pos(-1,1) //UP_RIGHT

	};

	int32 cost[] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14,
	};

	const int32 size = _board->GetSize();
	
	// best[y][x] : (y,x)���� ���µ� ���� ���� ����� �������� �����Ѵ�
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	// ClosedList -> closed[y][x] -> (y,x)�� �湮�� �ߴ��� ���θ� ����
	// Option) �� �ᵵ �׸��� �ɼ��ε� ���� �������� �̰� �׻� �־ �򰥸���.
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	// �θ� ���� �뵵
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	//1) ���� �ý��� ����
	//2) �ڴʰ� �߰ߵǴ� �� ���� ��� ����ó���ؾ��� (���ͽ�Ʈ��)
	
	//OpenList -> ���ݱ��� '�߰�'�� ��� (�߰߰� �湮�� �ٸ���)
	priority_queue<PQNode,vector<PQNode>,greater<PQNode>> pq;

	// �ʱⰪ ���� ��
	{
		int32 g = 0; // �� g�� ����ƾ����� ���ͽ�Ʈ���� �� �� �ִ�
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x)); // �������� �ٲ� �� �ִ� ����

		pq.push(PQNode(g + h, g, start));
		best[start.y][start.x] = g + h;
		parent[start.y][start.x] = start;
	}


	while (pq.empty()==false)
	{
		//���� ���� �ĺ� �̱�
		PQNode node=pq.top(); // ���� ó�� ����
		pq.pop();

		// ������ ��ǥ�� ���� ��θ� Ž���ؼ�
		// �� ���� ��η� ���ؼ� �̹� �湮(closed)�� ��� Ž���� ��ŵ���ش� (������ �Ʒ� best���� �ɷ����� �ʿ����)
		if (closed[node.pos.y][node.pos.x])
			continue;
		// �ⲯ ť�� ����ߴ��� �� ����� �ĺ��� �ִ� ���.. �ٷ� ���ó���Ѵ�
		// ����� �ĺ��� ���߿� ť�� �ö󰬴��� �켱���� ť�ϱ� �ּڰ��̶� ���� '�湮'���� �� �ִ�.
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// ���� �湮�� �غ���
		// �湮�� �ߴٴ� �� ť�� ��ϵ� ����, �湮�ؼ� Ž������ �����ϴ� ����� ���̴�
		closed[node.pos.y][node.pos.x] = true; 

		// �������� ���������� �ٷ� ����
		if (node.pos == dest)
			break;

		//�湮 �� Ž������
		for (int32 dir = 0; dir < 8; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			
			if (CanGo(nextPos) == false)
				continue;
			if (closed[nextPos.y][nextPos.x] == true) // ť�� ������൵ ���⼭ �ɸ��� ������ �ƿ��̴ϱ� �̸� üũ
				continue;

			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;
			
			// �ϴ� �̳��� best�� Ȯ�� �Ǿ����� ���� ����
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode(g + h, g, nextPos));
			parent[nextPos.y][nextPos.x] = node.pos;
		}
	}

	_path.clear();

	Pos pos = dest;

	while (true)
	{
		_path.push_back(pos);
		if (parent[pos.y][pos.x] == pos)
			break;
		pos = parent[pos.y][pos.x];
	}
	
	reverse(_path.begin(), _path.end());

}
