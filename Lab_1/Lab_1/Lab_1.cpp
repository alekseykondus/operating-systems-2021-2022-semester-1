#include "Server.h"
#include "../testing/probefuncs.hpp"


double get_double(const char* msg) {
	char answer[256];
	double x;

	ColoredСonsoleOutput::out_GREEN(msg);
	fgets(answer, sizeof(answer), stdin);

	while (sscanf(answer, "%lf", &x) != 1) {
		ColoredСonsoleOutput::out_RED("Incorrect input.");
		std::cout << " Try again: ";
		fgets(answer, sizeof(answer), stdin);
	}
	std::cout << "x = " << x << std::endl;
	return x;
}
bool AskForCompletion() {
	char ch[100];

	std::cout << "Do you want to continue? (enter the number - 1 or 0)" << std::endl
			  << "1 - Yes" << std::endl << "0 - No" << std::endl << "_______" << std::endl;

	while (std::cin >> ch) {
		if (ch[0] == 48) {
			std::cin.ignore(256, '\n');
			return false;
		}
		else if (ch[0] == 49) {
			std::cin.ignore(256, '\n');
			return true;
		}
		else {
			ColoredСonsoleOutput::out_RED("Incorrect input.");
			std::cout << " Try again: ";
		}
	}
}

#pragma warning(disable: 4996)
int main(int argc, char* argv[])
{
	//implemented advanced version (repeat computation multiple times for different input x)
	bool finish = false;
	while (!finish) {
		double x = get_double("\nEnter the X value (double): ");
		Server server(x);
		server.RunServer();
		server.CloseServer();

		finish = !AskForCompletion();
	}

	return 0;
}

