#include <iostream>
#include <vector>
#include <queue>

// Dijikstra = BFS + 양념(cost개념)
// BFS = queue
// Dijikstra = priorty_queue
using namespace std;

struct Vertex
{
	//int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));
	adjacent[0][1] = adjacent[1][0] = 15;
	adjacent[0][3] = adjacent[3][0] = 35;
	adjacent[1][2] = adjacent[2][1] = 5;
	adjacent[1][3] = adjacent[3][1] = 10;
	adjacent[3][4] = adjacent[4][3] = 5;
	adjacent[4][5] = adjacent[5][4] = 5;
}

struct VertexCost
{
	VertexCost(int cost, int vertex):cost(cost), vertex(vertex) { }

	bool operator<(const VertexCost& other) const
	{
		return cost < other.cost;
	}

	bool operator>(const VertexCost& other) const
	{
		return cost > other.cost;
	}

	int cost;
	int vertex;
};

void Dijikstra(int here)
{
	priority_queue<VertexCost, vector<VertexCost>, greater<VertexCost>> pq;
	vector<int> best(6, INT32_MAX); //베스트 케이스를 저장해두는 벡터
	vector<int> parent(6, -1);

	pq.push(VertexCost(0, here)); //cost는 0인 정점 here이 등장
	best[here] = 0; //here를 오는 베스트 케이스는 고민할 필요 없이 자기 자신이므로 0이다
	parent[here] = here;

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다
		VertexCost v = pq.top();
		pq.pop();

		int cost = v.cost;
		here = v.vertex;

		// 큐에 올라간 경로 중 베스트가 새롭게 업데이트되어서 쓸모없어진 경로를 폐기한다 
		// (일단 모든 정점을 BFS처럼 탐색해서 큐에 올리기 때문에 더블 체크과정이 필요하다)
		if (best[here] < cost)
			continue;

		// 방문도장
		cout << "방문! " << here << endl;

		for (int there = 0; there < 6; there++)
		{
			// 연결되지 않았으면 스킵
			if (adjacent[here][there] == -1)
				continue;
			
			// 더 좋은 경로가 이미 저장되어 있다면 스킵
			int nextCost = best[here] + adjacent[here][there];
			if (best[there] <= nextCost)
				continue;

			// 최선의 수치 갱신
			best[there] = nextCost;
			parent[there] = here; // 나중에 갱신될 수 있음

			// 탐색 큐에 넣어준다
			pq.push(VertexCost(nextCost, there));
		}


	}


}
	
int main()
{

	CreateGraph();
	Dijikstra(0);
}

