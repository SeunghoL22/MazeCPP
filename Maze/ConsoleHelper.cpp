#include "pch.h"
#include "ConsoleHelper.h"

void ConsoleHelper::SetCursorPosition(int32 x, int32 y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE); //커서 포지션 위치 변경
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void ConsoleHelper::SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<int16>(color)); //색상 선택하기
}

void ConsoleHelper::ShowConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo; 
	::GetConsoleCursorInfo(output, &cursorInfo); //현재 커서 정보 받아와서
	cursorInfo.bVisible = flag; //visible만 바꿔서 
	::SetConsoleCursorInfo(output, &cursorInfo); //다시 세팅해주기

}
