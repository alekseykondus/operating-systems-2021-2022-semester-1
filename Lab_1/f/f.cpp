//Работа с сокетами
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <windows.h>
//#include <exception>


/*
class memoryAllocationFailed : public std::exception {
public:
	const char* what() const noexcept override {
		return "Exceptional situation: memory allocation failed\n";
	}
};*/

double f(double x) {
	return x * x;
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
		std::cout << "Error: failed connect to server" << std::endl;
		return 1;
	}
	std::cout << "Connected is OK!" << std::endl;

	//Получаем данные с сервера
	char xFromServer[10];
	recv(Connection, xFromServer, sizeof(xFromServer), NULL);

	//Sleep(5000);
	std::cout << xFromServer << " FROM F" << std::endl;

	//Считаем результат
	double return_F = f(atof(xFromServer));

	//Отправляем результат на сервер
	char strToServer[10];
	sprintf(strToServer, "%f", return_F);
	send(Connection, strToServer, sizeof(strToServer), NULL);

	//throw memoryAllocationFailed();
	closesocket(Connection);
	WSACleanup();
	return 0;
}
