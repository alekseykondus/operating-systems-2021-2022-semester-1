//Работа с сокетами
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <windows.h>
//#include <exception>
#include "../testing/probefuncs.hpp"

/*
class memoryAllocationFailed : public std::exception {
public:
	const char* what() const noexcept override {
		return "Exceptional situation: memory allocation failed\n";
	}
};*/

#include <sstream>

long double f(double x) {
	return x * x;
}

std::string LDToStr(long double one)
{
	std::stringstream ss;
	ss << one;
	return ss.str();
}

#pragma warning(disable: 4996)
int main()
{
	//Сокеты
	//WSAStartup

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error: The library did not load!" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeOfAddr = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeOfAddr) != 0) {
		std::cout << "Error: failed connect to server (F)" << std::endl;
		return 1;
	}
	std::cout << "Connected to F is OK!" << std::endl;

	//Получаем данные с сервера
	char xFromServer[100];
	recv(Connection, xFromServer, sizeof(xFromServer), NULL);

	std::variant<os::lab1::compfuncs::hard_fail, os::lab1::compfuncs::soft_fail, double> result = os::lab1::compfuncs::probe_f < os::lab1::compfuncs::DOUBLE_SUM > (atof(xFromServer));

	//Sleep(5000);
	//std::cout << xFromServer << " FROM F" << std::endl;

	//Считаем результат
	char strToServer[100];
	if (std::holds_alternative<os::lab1::compfuncs::hard_fail>(result)) {
		sprintf(strToServer, "%s", "hard fail");
	//	std::cout << "hard fail" << std::endl;
	}
	else if (std::holds_alternative<os::lab1::compfuncs::soft_fail>(result)) {
		sprintf(strToServer, "%s", "soft fail");
	//	std::cout << "soft fail" << std::endl;
	}
	else {
		strcpy(strToServer, LDToStr((long double)std::get<2>(result)).c_str());
	}

	//Отправляем результат на сервер
	//std::cout << "Sent to the server from F: " << strToServer << std::endl;
	send(Connection, strToServer, sizeof(strToServer), NULL);


	//throw memoryAllocationFailed();
	closesocket(Connection);
	WSACleanup();
	return 0;
}
