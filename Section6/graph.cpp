#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//정점이 100개
// -지하철 노선도-> 드문드문 연결 ->인접리스트가 용이할 것
// -페이스북 친구->핵인싸일경우 빽빽하게 연결돼서 
// 100개씩이나 넣어야 한다고 생각하면 인접리스트가 좀 불편할 것이다
// 그래서 이럴땐 행렬방식을 이용하는게 더 편하다


//인접 리스트 : 실제 연결된(인접해 있는) 애들'만' 넣어준다.
void CreateGraph_2()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6);

	vector<vector<int>> adjacent;
	adjacent.resize(6);

	//adjacent[0].push_back(1);
	//adjacent[0].push_back(3);
	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	//Q) 0번->3번 연결되어 있나요 ?
	bool connected = false;

	int size = adjacent[0].size();
	for (int i = 0; i < size; i++)
	{
		if (adjacent[0][i] == 3)
			connected = true;

	}

}

//2번째 방법 : 인접 행렬을 이용한다
void CreateGraph_3()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6);

	// 인접 행렬 : 연결된 목록을 행렬로 관리
	// [x][o][x][o][x][x]
	// [o][x][o][o][x][x]
	// [x][x][x][x][x][x]
	// [x][x][x][x][o][x]
	// [x][x][x][x][x][x]
	// [x][x][x][x][o][x]


	//vector<bool> v(6, false);

	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][1] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	//Q. 0번과 3번 연결되어 있나요 ?

	bool connected = adjacent[0][3] == true;
	// 메모리 소모가 심하지만 빠른 접근이 가능하다는 장점이 있다

	//만약 간선의 가중치에 대한 정보를 포함해야한다면 +일경우는 true -1일 때는 false라고 할 수 있다.
	vector<vector<int>> adjacent2 =
	{
		{-1, 15,-1, 35,-1,-1},
		{15, -1, 5, 10,-1,-1},
		{-1, 5, -1, 35,-1,-1},
		{35, 10, -1,-1, 5,-1},
		{-1, -1, -1, 5,-1, 5},
		{-1, -1, -1,-1, 5,-1},
	};
	
	

}


int main()
{
	vector<int> v;
	//Q. 왜 그래프는 재귀함수로 모든 데이터를 순회할 수 없을까 ?
	// 그래프는 모든 데이터가 평등하기 때문에 계층을 표현하는 height(높이)가 없다.
	// 따라서 재귀함수를 쓰다 보면 이미 옮겨갔던 곳으로 다시 순회하기도 하는 무한 순회문제가 발생할 수 있다
	

}