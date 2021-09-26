//Работа с сокетами
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <windows.h>


double g(double x) {
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
		std::cout << "Error: failed connect to server" << std::endl;
		return 1;
	}
	std::cout << "Connected is OK!" << std::endl;
	
	//Получаем данные с сервера
	char xFromServer[10];
	recv(Connection, xFromServer, sizeof(xFromServer), NULL);

	//Sleep(3000);
	std::cout << xFromServer << " FROM G" << std::endl;

	//Считаем результат
	double return_G = g(atof(xFromServer));

	//Отправляем результат на сервер
	char strToServer[10];
	sprintf(strToServer, "%f", return_G);
	send(Connection, strToServer, sizeof(strToServer), NULL);

	closesocket(Connection);
	WSACleanup();
	return 0;
}

