#pragma once

// [front/back][][][][]
// [][front][][][back][]

//서버에서 일할때 큐의 원리를 이용하기도 한다
//패킷같은걸 관리할 때 클라에서 계속 요청을 보내는데 그걸 버퍼에 저장해서 야금야금 꺼내먹어야하는데
//그걸 이런식으로 원형의 큐에 저장해놓고 쓰기도 한다.
template<typename T>
class Queue
{
public:
	Queue()
	{
		_container.resize(100);
	}

	void push(const T& value)
	{
		//컨테이너 사이즈와 큐의 사이즈가 같아져버리면 back을 못 옮기므로 문제 발생
		if (_size == _container.size()) 
		{
			_container.reserve(3 * _size);
			_container.resize(2 * _size);

		}

		_container[_back] = value;
		_back = (_back + 1) % _container.size() //나머지 연산은 앞부분으로 보내주는 역할
		//어느 순간 back이 뒤로 밀려나다보면 front의 앞부분으로 오기도 하는 circular한 방식이다
		//ex) [back][][][front][][][]
		_size++;
	}

	void pop()//실제로 데이터를 없애는게 아닌 _front를 앞으로 한칸 조정하는 형식
	{
		_front = (_front +1) % _container.size(); //얘도 앞부분으로 다시 돌아갈 수 있으니 나머지 연산
		_size--;
	}

	T& front()
	{
		return _container[_front];
	}

	bool empty() { return _size == 0; }
	int size() { return _size; }

private:
	Vector<T> _container;

	_front = 0;
	_back = 0;
	_size = 0;
};

