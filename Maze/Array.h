#pragma once
#include "assert.h"

class Array
{
	using T = int;

public:
	explicit Array(int capacity = 100) : _capacity(capacity)
	{
		_buffer = new T[capacity];
	}

	~Array()
	{
		delete[] _buffer;
	}

	void push_back(const T& data) //�迭�� �߰����ִ� �Լ�
	{
		if (_size == _capacity)
			return;

		_buffer[_size] = data;
		_size++;
	}

	T& operator[](int index)
	{
		assert(index >=0 && index < _size); //assert : ���� ���� ���ҽ� �ٷ� crash �������� ����
		
		return _buffer[index];
		//TO DO
	}

	int size() { return _size; }
	int capacity() { return _capacity; }

private:
	T* _buffer = nullptr;
	int _size = 0;
	int _capacity = 0;
};

