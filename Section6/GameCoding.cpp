#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<typename T, typename Predicate = less<T>>
class PriorityQueue
{
public:
	void push(const T& data) //O(log N) 트리의 높이에 의존적이므로 로그이다
	{
		_heap.push_back(data);
		int i = static_cast<int>(_heap.size()) - 1; //번호 기억

		while (i > 0) //true도 좋은데 버그 방지를 위해서 루트노드까지로 하자
		{
			int nextIndex = (i - 1) / 2;
			if(_predicate(_heap[i],_heap[nextIndex]))
				break; //도장깨기 끝

			//데이터 교체
			::swap(_heap[i], _heap[nextIndex]);
			i = nextIndex; //도장깨기 성공했으니 위로 시점 변경
				
		}
	}

	void pop() //최댓값 꺼내기 (별칭 역도장깨기) 
	//O(logN) 얘도 최대 트리의 높이만큼 계산할 것이기 때문에 로그N임
	{
		_heap[0] = _heap.back();
		_heap.pop_back();

		int now = 0;

		while (true)
		{
			int next = now; //next를 업데이트 하는식으로 진행할 예정

			int left = (2 * now) + 1;
			int right = (2 * now) + 2;

			if (left< static_cast<int>(_heap.size()) && _predicate(_heap[next], _heap[left]))
				next = left;

			if (right< static_cast<int>(_heap.size()) && _predicate(_heap[next], _heap[right]))
				next = right;

			if (next == now)
				break;
			else
			{
				::swap(_heap[next], _heap[now]);
				now = next;
			}

		}
	}

	T& top() // O(0)
	{
		return _heap[0];
	}

	bool empty() //O(0)
	{
		return _heap.empty();
	}


private:
	vector<T> _heap;
	Predicate _predicate;
};

int main()
{
	PriorityQueue<int, greater<int>> a;
	a.push(32);
	a.push(26);
	a.push(15);
	a.push(19);
	a.push(14);
	a.push(6);
	a.push(13);
	a.push(1);
	a.push(10);
	a.push(31);
	//a.pop();

	int value = a.top();
}

