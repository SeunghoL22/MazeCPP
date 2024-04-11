#pragma once

// [front/back][][][][]
// [][front][][][back][]

//�������� ���Ҷ� ť�� ������ �̿��ϱ⵵ �Ѵ�
//��Ŷ������ ������ �� Ŭ�󿡼� ��� ��û�� �����µ� �װ� ���ۿ� �����ؼ� �߱ݾ߱� �����Ծ���ϴµ�
//�װ� �̷������� ������ ť�� �����س��� ���⵵ �Ѵ�.
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
		//�����̳� ������� ť�� ����� ������������ back�� �� �ű�Ƿ� ���� �߻�
		if (_size == _container.size()) 
		{
			_container.reserve(3 * _size);
			_container.resize(2 * _size);

		}

		_container[_back] = value;
		_back = (_back + 1) % _container.size() //������ ������ �պκ����� �����ִ� ����
		//��� ���� back�� �ڷ� �з����ٺ��� front�� �պκ����� ���⵵ �ϴ� circular�� ����̴�
		//ex) [back][][][front][][][]
		_size++;
	}

	void pop()//������ �����͸� ���ִ°� �ƴ� _front�� ������ ��ĭ �����ϴ� ����
	{
		_front = (_front +1) % _container.size(); //�굵 �պκ����� �ٽ� ���ư� �� ������ ������ ����
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

