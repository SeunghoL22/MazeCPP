#pragma once
#include "Vector.h"

class Board; //���漱��


class Player
{
	enum
	{
		MOVE_TICK = 100 //100ms 0.1��
	};
public:

	void	Init(Board* board);
	void	Update(uint64 deltaTick);
	//���������Ӱ� ���� ������ ������ ������Ʈ

	Pos		GetPos();
	void	SetPos(Pos pos) { _pos = pos; }

	bool	CanGo(Pos pos);
	bool	CanTurn(Pos pos);
	

private:
	void	CalculatePath();

private:
	Pos		_pos;
	int32	_dir = DIR_UP;
	Board* _board = nullptr;

	Vector<Pos> _path; //�̵��� ��ΰ� �����
	int32		_pathindex=0;
	uint64		_sumTick = 0; //���� ƽ
};

