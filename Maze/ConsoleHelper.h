#pragma once
//콘솔에 대한 색상같은 것도 변경이 가능하다

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN, //bit wise or
	WHITE = RED | GREEN | BLUE
};

class ConsoleHelper
{
public:
	static void SetCursorPosition(int32 x, int32 y);
	static void SetCursorColor(ConsoleColor color);
	static void ShowConsoleCursor(bool flag); //커서 깜빡 거리는걸 보여주겠느냐
};

