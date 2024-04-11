#pragma once
#include "assert.h"

//capacity�� size�� ���� ������ �����ϴ°� �߿��ϴ�.

template<typename T=int>
class Vector
{

public:
	explicit Vector() //���ʹ� ó���� capacity�� �ȹ޴´�.
	{
	}

	~Vector()
	{
		if(_buffer) //���۰� ������� ������ �������ϴϱ� ���ǹ� �߰�
			delete[] _buffer;
	}

	void push_back(const T& data) //�迭�� �߰����ִ� �Լ�
	{
		if (_size == _capacity)
		{
			//���� �۾�
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity); //capacity�� ������Ʈ�ϴ� �Լ��� ������
		}

		//������ ����
		_buffer[_size] = data;

		//������ ���� ����
		_size++;
	}

	void pop_back() //�ڿ� �ִ� �����͸� �����ϴ� ���
	{
		//TO DO: �Ҹ�
		_size--; //�Ҹ��Ų�� ������ ����
	}

	T& back() //�ڿ� �ִ� �����͸� �ִ� ���
	{
		return _buffer[_size - 1];
	}


	void clear()//Ŭ���� �ص� capacity�� ������ �ʰ� _size�� �پ���.
	{
		//TO DO
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = new T[_capacity];
		}
		_size = 0;
	}

	void resize(int size) //capacity�� �ǵ��� �ʰ� _size�� �����Ѵ�
	{
		reserve(size);
		_size = size;
	}

	void reserve(int capacity) //�޸� �Ҵ� �䱸
	{
		if (_capacity >= capacity) //�� ���� capacity���� ������ �䱸�Ұ�� ����
			return;
		
		_capacity = capacity;

		//���ο� ũ���� �迭 ����
		T* newData = new T[_capacity];

		//������ ������ �о�ֱ�
		for (int i = 0; i < _size; i++)
			newData[i] = _buffer[i];

		//���� ��ü�ϱ�
		if (_buffer)
			delete[] _buffer;
		
		_buffer = newData;
	}

	T& operator[](int index)
	{
		assert(index >= 0 && index < _size); //assert : ���� ���� ���ҽ� �ٷ� crash �������� ����

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

