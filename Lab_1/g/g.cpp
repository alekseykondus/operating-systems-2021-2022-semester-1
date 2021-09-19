//Работа с сокетами
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>


#include <iostream>
#include <windows.h>

#pragma warning(disable: 4996)
int main()
{
    std::cout << "Hello World form п!!!\n" << std::endl;

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
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeOfAddr) != 0) {
		std::cout << "Error: failed connect to server" << std::endl;
		return 1;
	}
	std::cout << "Connected is OK!" << std::endl;

	char strFromServer[256];
	recv(Connection, strFromServer, sizeof(strFromServer), NULL);

	Sleep(3000);
	std::cout << strFromServer << " FROM G" << std::endl;

}
