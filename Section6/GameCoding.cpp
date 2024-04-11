#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<typename T, typename Predicate = less<T>>
class PriorityQueue
{
public:
	void push(const T& data) //O(log N) Ʈ���� ���̿� �������̹Ƿ� �α��̴�
	{
		_heap.push_back(data);
		int i = static_cast<int>(_heap.size()) - 1; //��ȣ ���

		while (i > 0) //true�� ������ ���� ������ ���ؼ� ��Ʈ�������� ����
		{
			int nextIndex = (i - 1) / 2;
			if(_predicate(_heap[i],_heap[nextIndex]))
				break; //������� ��

			//������ ��ü
			::swap(_heap[i], _heap[nextIndex]);
			i = nextIndex; //������� ���������� ���� ���� ����
				
		}
	}

	void pop() //�ִ� ������ (��Ī ���������) 
	//O(logN) �굵 �ִ� Ʈ���� ���̸�ŭ ����� ���̱� ������ �α�N��
	{
		_heap[0] = _heap.back();
		_heap.pop_back();

		int now = 0;

		while (true)
		{
			int next = now; //next�� ������Ʈ �ϴ½����� ������ ����

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

