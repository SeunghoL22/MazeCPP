#include "Vector.h"
#include "pch.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player; //NPC

uint64 lastTick = 0; //�ð�����

int main()
{
	::srand(static_cast<uint32>(time(nullptr)));//�õ尪 ����
	
	board.Init(25,&player);
	player.Init(&board);

	while (true) //�����̶�� �� �׻� ���ѷ����� �ִ�
	{	
#pragma region ������ ����
		// one loop = 1frame
		const uint64 currentTick = ::GetTickCount64(); //��� ������ �������� ms�ܿ� �ð��� �����
		const uint64 deltaTick = currentTick - lastTick;//����� �ð�
		lastTick = currentTick;
#pragma endregion

		//������ ���ܰ�
		//�Է�
		
		//����(����, ������Ʈ �Լ�)
		player.Update(deltaTick);

		
		//������(�׷��ִ� �ܰ�)
		board.Render(); //�� �����Ӹ��� ���� �����
	}

}
