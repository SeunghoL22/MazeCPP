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

	void push_back(const T& data) //배열에 추가해주는 함수
	{
		if (_size == _capacity)
			return;

		_buffer[_size] = data;
		_size++;
	}

	T& operator[](int index)
	{
		assert(index >=0 && index < _size); //assert : 조건 만족 안할시 바로 crash 내버리는 문법
		
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

