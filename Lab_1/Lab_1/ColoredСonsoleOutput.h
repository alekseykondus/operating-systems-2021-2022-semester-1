#pragma once
#include <iostream>
#include <windows.h>

class Colored—onsoleOutput {
public:
	static void out_BLUE_RED(std::string str);
	static void out_RED(std::string str);
	static void out_GREEN(std::string str);
	static void out_BLUE(std::string str);

private:
	inline static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
};