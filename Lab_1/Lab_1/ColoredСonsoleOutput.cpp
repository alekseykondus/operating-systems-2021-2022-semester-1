#include "Colored—onsoleOutput.h"

void Colored—onsoleOutput::out_RED(std::string str) {
	SetConsoleTextAttribute(console, FOREGROUND_RED);
	std::cout << str;
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Colored—onsoleOutput::out_GREEN(std::string str) {
	SetConsoleTextAttribute(console, FOREGROUND_GREEN);
	std::cout << str;
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Colored—onsoleOutput::out_BLUE_RED(std::string str)
{
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_RED);
	std::cout << str;
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Colored—onsoleOutput::out_BLUE(std::string str)
{
	SetConsoleTextAttribute(console, FOREGROUND_BLUE);
	std::cout << str;
	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
