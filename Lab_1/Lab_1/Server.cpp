#include "Server.h"

Server::Server(int x) : m_x(x) {
}

Server::~Server()
{
}

void Server::RunServer()
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
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	m_sListen = socket(AF_INET, SOCK_STREAM, NULL);

	if (m_sListen == SOCKET_ERROR) {
		std::cout << "Error: socket not created" << std::endl;
	}

	if (bind(m_sListen, (SOCKADDR*)&addr, sizeOfAddr) == SOCKET_ERROR) {
		std::cout << "Error: Socket not bind" << std::endl;
	}

	if (listen(m_sListen, SOMAXCONN) == SOCKET_ERROR) {
		std::cout << "Error: listening errors - " << ntohs(addr.sin_port) << std::endl;
	}

	RunProcesses();
	SendingAndReceivingData(addr, sizeOfAddr);


	CloseServer();
}

void Server::SendingAndReceivingData(SOCKADDR_IN addr, int sizeOfAddr)
{
	SOCKET newConnectionF;
	SOCKET newConnectionG;

	newConnectionF = accept(m_sListen, (SOCKADDR*)&addr, &sizeOfAddr);
	newConnectionG = accept(m_sListen, (SOCKADDR*)&addr, &sizeOfAddr);

	if (newConnectionF == 0 || newConnectionG == 0) {
		std::cout << "Error: The client was unable to connect to the server" << std::endl;
	}
	else {
		std::cout << "Clients connected" << std::endl;
		char strToClient[256] = "Hello. It is my first network program!";
		send(newConnectionF, strToClient, sizeof(strToClient), NULL);
		send(newConnectionG, strToClient, sizeof(strToClient), NULL);
		std::cout << "I SEND" << std::endl << std::endl;

		char strFromF[256];
		char strFromG[256];
		recv(newConnectionF, strFromF, sizeof(strFromF), NULL);
		recv(newConnectionG, strFromG, sizeof(strFromG), NULL);
		std::cout << strFromF << " FROM F" << std::endl;
		std::cout << strFromG << " FROM G" << std::endl;

	}
	
	//Получаем информацию с клиентов!
}

void Server::CloseServer()
{
	CloseProcesses();
	closesocket(m_sListen);
	WSACleanup();
	std::cout << "Server was stoped. You can close app" << std::endl;
}

void Server::RunProcesses()
{
	//запуск процесов!
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	std::wstring czCommandLineF = L"C:\\Users\\Professional\\source\\repos\\Lab_1\\Debug\\f.exe";
	std::wstring czCommandLineG = L"C:\\Users\\Professional\\source\\repos\\Lab_1\\Debug\\g.exe";

	std::future<void> result_F = std::async(std::launch::async, [&]() { CreateProcess(czCommandLineF.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi); });
	std::future<void> result_G = std::async(std::launch::async, [&]() { CreateProcess(czCommandLineG.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi); });
}

void Server::CloseProcesses()
{
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
