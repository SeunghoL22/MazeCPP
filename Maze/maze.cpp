#include "Vector.h"
#include "pch.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player; //NPC

uint64 lastTick = 0; //시간관리

int main()
{
	::srand(static_cast<uint32>(time(nullptr)));//시드값 설정
	
	board.Init(25,&player);
	player.Init(&board);

	while (true) //게임이라는 건 항상 무한루프가 있다
	{	
#pragma region 프레임 관리
		// one loop = 1frame
		const uint64 currentTick = ::GetTickCount64(); //어느 시점을 기준으로 ms단우 시간을 뱉어줌
		const uint64 deltaTick = currentTick - lastTick;//경과된 시간
		lastTick = currentTick;
#pragma endregion

		//게임의 세단계
		//입력
		
		//로직(진행, 업데이트 함수)
		player.Update(deltaTick);

		
		//렌더링(그려주는 단계)
		board.Render(); //매 프레임마다 맵을 찍어줌
	}

}
