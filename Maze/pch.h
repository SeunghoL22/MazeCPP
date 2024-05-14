#pragma once

//pre compiled header라는 듯의 pch이다
//이곳엔 항상 쓸거 같은 header를 모아두면 된다
// 
//프로젝트 우클릭->속성->C/C++->미리컴파일된헤더->사용으로 변경 / 헤더명 pch.h로 변경
//그리고 pch.cpp 속성 들어가서 사용->만들기 로 변경하면 끝.

//이미 만들어진 cpp파일들에는 #include "pch.h"를 추가해야한다.

//컴파일 시간 단축에 용이하다
//한번 컴파일된 결과물을 재사용한다

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
}; //만들어 두는게 편하다

enum Dir //enum클래스 안쓴 이유는 Loop문에서 더하고 4로 나머지 구하는 식으로 하기 위해서다
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4 //LOOP 돌릴 때 용이할것이다
};

