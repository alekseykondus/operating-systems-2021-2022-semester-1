//Работа с сокетами
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <windows.h>
#include "../testing/probefuncs.hpp"


long double g(double x) {
	return x * x * x;
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
	addr.sin_family = AF_INET;
	int sizeOfAddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeOfAddr) != 0) {
		std::cout << "Error: failed connect to server (G)" << std::endl;
		return 1;
	}
	std::cout << "Connected to G is OK!" << std::endl;
	
	//Получаем данные с сервера
	char xFromServer[100];
	recv(Connection, xFromServer, sizeof(xFromServer), NULL);


	std::variant<os::lab1::compfuncs::hard_fail, os::lab1::compfuncs::soft_fail, int> result = os::lab1::compfuncs::probe_g<os::lab1::compfuncs::INT_SUM>(atof(xFromServer));
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
		sprintf(strToServer, "%f", (float)std::get<2>(result));
		//	std::cout << "(float)std::get<2>(result)" << (float)std::get<2>(result) << std::endl;
	}

	//Считаем результат
/*	long double return_G = g(atof(xFromServer));
	char strToServer[100];
	sprintf(strToServer, "%f", return_G); */

	//Отправляем результат на сервер
	send(Connection, strToServer, sizeof(strToServer), NULL);

	closesocket(Connection);
	WSACleanup();
	return 0;
}

