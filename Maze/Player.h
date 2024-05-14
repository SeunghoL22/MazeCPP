#pragma once
#include "Vector.h"

class Board; //전방선언


class Player
{
	enum
	{
		MOVE_TICK = 100 //100ms 0.1초
	};
public:

	void	Init(Board* board);
	void	Update(uint64 deltaTick);
	//지난프레임과 현재 프레임 사이의 업데이트

	Pos		GetPos();
	void	SetPos(Pos pos) { _pos = pos; }

	bool	CanGo(Pos pos);
	bool	CanTurn(Pos pos);
	

private:
	void	CalculatePath_RightHand();
	void	CalculatePath_BFS();

private:
	Pos		_pos;
	int32	_dir = DIR_UP;
	Board* _board = nullptr;

	vector<Pos> _path; //이동된 경로가 저장됨
	int32		_pathindex=0;
	uint64		_sumTick = 0; //누적 틱
};

