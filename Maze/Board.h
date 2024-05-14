#pragma once
#include "ConsoleHelper.h" //가벼운 헤더라 헤더에 추가한다
//#include "Player.h" 절대로 여기다가 추가하면 안된다
//전방 선언을 반드시 이용해라
class Player; 

enum
{
	BOARD_MAX_SIZE = 100
}; //상수 표시하는 방법 중 하나인데
//define으로 상수표기는 지양하는게 좋다

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL
};

class Board
{
public:
	Board();
	~Board();

	void			Init(int32 size, class Player* player); //맵 사이즈를 그려주는 함수
	void			Render(); //랜더해서 타일로 그려주는 함수

	void			GenerateMap();//미로 생성 알고리즘
	TileType		GetTileType(Pos pos);//벽인지 비어있는지 알려줌
	ConsoleColor	GetTileColor(Pos pos);

	Pos				GetEnterPos() { return Pos(1, 1); }
	Pos				GetExitPos() { return Pos(_size-2, _size-2); }
	int32			GetSize() {	return _size; }

private:
	TileType		_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE];
	int32			_size=0;
	Player*			_player = nullptr;
};

