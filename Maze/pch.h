#pragma once

//pre compiled header��� ���� pch�̴�
//�̰��� �׻� ���� ���� header�� ��Ƶθ� �ȴ�
// 
//������Ʈ ��Ŭ��->�Ӽ�->C/C++->�̸������ϵ����->������� ���� / ����� pch.h�� ����
//�׸��� pch.cpp �Ӽ� ���� ���->����� �� �����ϸ� ��.

//�̹� ������� cpp���ϵ鿡�� #include "pch.h"�� �߰��ؾ��Ѵ�.

//������ �ð� ���࿡ �����ϴ�
//�ѹ� �����ϵ� ������� �����Ѵ�

#include "Types.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pos
{
	Pos() {}
	Pos(int32 y, int32 x) :y(y), x(x) {}

	bool operator==(const Pos& other)
	{
		return (y == other.y && x == other.x);
	}

	bool operator!=(const Pos& other)
	{
		return !(*this==other);
	}

	Pos operator+(const Pos& other)
	{
		Pos ret = Pos(this->y + other.y, this->x + other.x);
		return ret;
	}
	
	Pos& operator+=(const Pos& other)
	{
		y += other.y;
		x += other.x;

		return *this;
	}



	int32 y = 0;
	int32 x = 0;
}; //����� �δ°� ���ϴ�

enum Dir //enumŬ���� �Ⱦ� ������ Loop������ ���ϰ� 4�� ������ ���ϴ� ������ �ϱ� ���ؼ���
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4 //LOOP ���� �� �����Ұ��̴�
};

