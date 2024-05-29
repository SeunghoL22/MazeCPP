#include <iostream>
#include <vector>
#include <queue>

// Dijikstra = BFS + ���(cost����)
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
	vector<int> best(6, INT32_MAX); //����Ʈ ���̽��� �����صδ� ����
	vector<int> parent(6, -1);

	pq.push(VertexCost(0, here)); //cost�� 0�� ���� here�� ����
	best[here] = 0; //here�� ���� ����Ʈ ���̽��� ����� �ʿ� ���� �ڱ� �ڽ��̹Ƿ� 0�̴�
	parent[here] = here;

	while (pq.empty() == false)
	{
		// ���� ���� �ĺ��� ã�´�
		VertexCost v = pq.top();
		pq.pop();

		int cost = v.cost;
		here = v.vertex;

		// ť�� �ö� ��� �� ����Ʈ�� ���Ӱ� ������Ʈ�Ǿ ��������� ��θ� ����Ѵ� 
		// (�ϴ� ��� ������ BFSó�� Ž���ؼ� ť�� �ø��� ������ ���� üũ������ �ʿ��ϴ�)
		if (best[here] < cost)
			continue;

		// �湮����
		cout << "�湮! " << here << endl;

		for (int there = 0; there < 6; there++)
		{
			// ������� �ʾ����� ��ŵ
			if (adjacent[here][there] == -1)
				continue;
			
			// �� ���� ��ΰ� �̹� ����Ǿ� �ִٸ� ��ŵ
			int nextCost = best[here] + adjacent[here][there];
			if (best[there] <= nextCost)
				continue;

			// �ּ��� ��ġ ����
			best[there] = nextCost;
			parent[there] = here; // ���߿� ���ŵ� �� ����

			// Ž�� ť�� �־��ش�
			pq.push(VertexCost(nextCost, there));
		}


	}


}
	
int main()
{

	CreateGraph();
	Dijikstra(0);
}

