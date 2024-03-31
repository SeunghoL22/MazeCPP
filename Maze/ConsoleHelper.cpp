#include "pch.h"
#include "ConsoleHelper.h"

void ConsoleHelper::SetCursorPosition(int32 x, int32 y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE); //Ŀ�� ������ ��ġ ����
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void ConsoleHelper::SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<int16>(color)); //���� �����ϱ�
}

void ConsoleHelper::ShowConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo; 
	::GetConsoleCursorInfo(output, &cursorInfo); //���� Ŀ�� ���� �޾ƿͼ�
	cursorInfo.bVisible = flag; //visible�� �ٲ㼭 
	::SetConsoleCursorInfo(output, &cursorInfo); //�ٽ� �������ֱ�

}
