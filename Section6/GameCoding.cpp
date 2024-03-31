#include <iostream>

using namespace std;

template<typename T=int, int SIZE=100>
class RandomBox
{
public:
	T GetRandomData()
	{
		int index = rand() % SIZE;
		return data[index];
	}
public:
	T data[SIZE];
};

int main()
{
	RandomBox<int,100> rb1;
	RandomBox<float,100> rb2;
}

 