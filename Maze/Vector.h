#pragma once
#include "assert.h"

//capacity와 size에 대한 개념을 이해하는게 중요하다.

template<typename T=int>
class Vector
{

public:
	explicit Vector() //벡터는 처음에 capacity를 안받는다.
	{
	}

	~Vector()
	{
		if(_buffer) //버퍼가 비어있지 않으면 비워줘야하니까 조건문 추가
			delete[] _buffer;
	}

	void push_back(const T& data) //배열에 추가해주는 함수
	{
		if (_size == _capacity)
		{
			//증설 작업
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity); //capacity를 업데이트하는 함수를 만들어보자
		}

		//데이터 저장
		_buffer[_size] = data;

		//데이터 개수 증가
		_size++;
	}

	void pop_back() //뒤에 있는 데이터를 삭제하는 기능
	{
		//TO DO: 소멸
		_size--; //소멸시킨후 사이즈 감소
	}

	T& back() //뒤에 있는 데이터를 주는 기능
	{
		return _buffer[_size - 1];
	}


	void clear()//클리어 해도 capacity는 줄이지 않고 _size만 줄어든다.
	{
		//TO DO
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = new T[_capacity];
		}
		_size = 0;
	}

	void resize(int size) //capacity는 건들지 않고 _size만 변경한다
	{
		reserve(size);
		_size = size;
	}

	void reserve(int capacity) //메모리 할당 요구
	{
		if (_capacity >= capacity) //더 작은 capacity로의 변경을 요구할경우 거절
			return;
		
		_capacity = capacity;

		//새로운 크기의 배열 생성
		T* newData = new T[_capacity];

		//기존의 데이터 밀어넣기
		for (int i = 0; i < _size; i++)
			newData[i] = _buffer[i];

		//버퍼 교체하기
		if (_buffer)
			delete[] _buffer;
		
		_buffer = newData;
	}

	T& operator[](int index)
	{
		assert(index >= 0 && index < _size); //assert : 조건 만족 안할시 바로 crash 내버리는 문법

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

