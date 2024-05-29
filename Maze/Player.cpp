#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>


void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	//CalculatePath_RightHand(); //우수법
	//CalculatePath_BFS();
	CalculatePath_AStar();
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
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));


	queue<Pos> q;
	q.push(pos);
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


// BFS 다익스트라는 목적지의 개념이 없음

// 채점 기준
// -입구에서 얼마나 떨어져있는지
// - 출구에서 얼마나 떨어져있는지

struct PQNode
{
	PQNode(int32 f, int32 g, Pos pos) : f(f), g(g), pos(pos) { }
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const {return f > other.f;}
	
	int32 f;
	int32 g;
	Pos pos;
};

void Player::CalculatePath_AStar() //다익스트라에 출구의 개념이 추가가 됨.
{
	// F = G + H 이러한 점수 매기기 방식은 유동적이며 언제든지 기호에 따라서 수정할 수 있음
	// F = 최종 점수 (작을 수록 좋음)
	// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용, 이 g만 고려 되었던게 다익스트라라고 할 수 있다
	// H = 목적지에서 해당 좌표까지 이동하는데 드는 비용

	Pos start = _pos;
	Pos dest = _board->GetExitPos(); //목적지

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
	
	// best[y][x] : (y,x)까지 가는데 가장 좋은 비용은 얼마인지를 저장한다
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	// ClosedList -> closed[y][x] -> (y,x)에 방문을 했는지 여부를 저장
	// Option) 안 써도 그만인 옵션인데 공식 문서에는 이게 항상 있어서 헷갈린다.
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	// 부모 추적 용도
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	//1) 예약 시스템 구현
	//2) 뒤늦게 발견되는 더 좋은 경로 예외처리해야함 (다익스트라)
	
	//OpenList -> 지금까지 '발견'된 목록 (발견과 방문은 다르다)
	priority_queue<PQNode,vector<PQNode>,greater<PQNode>> pq;

	// 초기값 세팅 끝
	{
		int32 g = 0; // 이 g만 고려됐었던게 다익스트라라고 할 수 있다
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x)); // 언제든지 바꿀 수 있는 공식

		pq.push(PQNode(g + h, g, start));
		best[start.y][start.x] = g + h;
		parent[start.y][start.x] = start;
	}


	while (pq.empty()==false)
	{
		//제일 좋은 후보 뽑기
		PQNode node=pq.top(); // 예약 처리 시작
		pq.pop();

		// 동일한 좌표를 여러 경로를 탐색해서
		// 더 빠른 경로로 인해서 이미 방문(closed)된 경우 탐색을 스킵해준다 (솔직히 아래 best에서 걸러져서 필요없음)
		if (closed[node.pos.y][node.pos.x])
			continue;
		// 기껏 큐에 등록했더니 더 우수한 후보가 있는 경우.. 바로 폐기처분한다
		// 우수한 후보가 나중에 큐에 올라갔더라도 우선순위 큐니까 최솟값이라 먼저 '방문'됐을 수 있다.
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// 이제 방문을 해보자
		// 방문을 했다는 건 큐에 등록된 이후, 방문해서 탐색까지 진행하는 노드라는 뜻이다
		closed[node.pos.y][node.pos.x] = true; 

		// 목적지에 도착했으면 바로 종료
		if (node.pos == dest)
			break;

		//방문 후 탐색과정
		for (int32 dir = 0; dir < 8; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			
			if (CanGo(nextPos) == false)
				continue;
			if (closed[nextPos.y][nextPos.x] == true) // 큐에 등록해줘도 여기서 걸리면 어차피 아웃이니까 미리 체크
				continue;

			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;
			
			// 일단 이놈이 best로 확인 되었으니 예약 진행
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
