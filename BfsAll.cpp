#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// DFS (Depth-First Search) 아무튼 깊이 들어가야한다 
// 그러니까 재귀함수가 편하지 않을까 ? 단 돌아왔던 길을 다시 못 가도록 path를 기록해놔야한다
// DFS = 재귀함수 = 스택 

// BFS (Breath first search) 너비 = 입구에서 얼마나 떨어져 있는가 ? 
// BFS = 큐

struct Vertex
{
	//int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

void CreateGraph()
{
	vertices.resize(6);

	// 인접 리스트
	/*adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };*/



	// 인접 행렬
	adjacent = vector<vector<int>>
	{
		{ 0,1,0,1,0,0 },
		{ 1,0,1,1,0,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,1,0 },
		{ 0,0,0,0,0,0 },
		{ 0,0,0,0,1,0 },
	};
}

// 용어의 차이 발생
// DFS 방문한 <-> BFS 발견한
vector<bool> discovered;


void Bfs(int here) //탐색 기준지점을 받을 것임
{
	queue<int> q;
	q.push(here); //탐색 예약큐에 넣어준다
	discovered[here] = true;

	while (q.empty() == false)
	{

		here = q.front(); // 예약을 하나 처리할때마다 here을 업데이트 해주자 
		q.pop(); //pop부터 해버리면 front의 값이 바뀌어버려요

		// 방문 도장
		cout << "visited : " << here << endl;

		int size = adjacent[here].size(); //관련된 정점들을 서칭
		for (int there = 0; there < size; there++)
		{
			if (adjacent[here][there] == 0) //연결되어있지 않은 정점들 스킵
				continue;
			if (discovered[there]) // 이미 봤던 정점들도 스킵
				continue;

				q.push(there);
				discovered[there] = true;
			
		}

	}
}

void BfsAll()
{
	discovered = vector<bool>(6, false);
	for (int i = 0; i < 6; i++)
	{
		if (discovered[i] == false)
			Bfs(i);
	}
}

int main()
{
	CreateGraph();
	BfsAll();
}