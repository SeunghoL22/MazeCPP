#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// DFS (Depth-First Search) 아무튼 깊이 들어가야한다 
// 그러니까 재귀함수가 편하지 않을까 ? 단 돌아왔던 길을 다시 못 가도록 path를 기록해놔야한다
// DFS = 재귀함수 = 스택 
struct Vertex
{
	//int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

// 내가 방문한 목록 (DFS는 탐색한 곳을 다시 들리면 안 되므로 방문한 목록을 알아야한다고 했죠)
vector<bool> visited;

void CreateGraph()
{
	vertices.resize(6);

	// 인접 리스트
	/*adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };
	*/

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
// 인접 행렬 시간 복잡도 O(V^2); //첫번째 포문에서 V번 그다음 Dfs돌면서 V번

void Dfs(int here) //Dfs는 시작점을 반드시 정해줘야한다. 어디를 기준으로 탐색할진 알아야지
{
	// 방문 도장찍기
	visited[here] = true;
	cout << "visited : " << here << endl;

	for (int there = 0; there < 6; there++)
	{
		// 길은 있는지
		if (adjacent[here][there] == 0)
			continue;

		// 방문한 적은 있는지
		if (visited[there] == false)
			Dfs(there);
		
	}

}

void DfsAll() // 정말 모든 정점을 탐색하길 바란다면 이렇게 할 수 밖에 없다
{
	visited = vector<bool>(6, false);

	for (int i = 0; i < 6; i++)
	{
		if (visited[i] == false)
			Dfs(i);
	}
}

int main()
{
	CreateGraph();

	visited = vector<bool>(6, false);

	Dfs(0);

	//DfsAll();
}