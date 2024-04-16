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
	adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

}

void Dfs(int here) //Dfs는 시작점을 반드시 정해줘야한다. 어디를 기준으로 탐색할진 알아야지
{
	// 방문 도장찍기
	visited[here] = true;
	cout << "visited : " << here << endl;

    // 인접 리스트 : 시간 복잡도 O(V+E)
    // V는 Vertex E는 Edge(간선의 '총' 개수)

	// 인접한 길을 체크하기
	const int size = adjacent[here].size();
	for (int i = 0; i < size; i++)
	{
		int there = adjacent[here][i];
		if (visited[there] == false) // 처음 방문일 경우에만 방문하기
			Dfs(there);
	}

}

int main()
{
	CreateGraph();

	visited = vector<bool>(6, false);

	Dfs(0);
}