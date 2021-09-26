#pragma once

//Работа с сокетами
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <future>

#include <mutex>

#define NUMBER_OF_CLIENTS 2 // Возможно будет использоваться потом, для n функций

#pragma warning(disable: 4996)

class Server
{
public:
	Server(int x);
	~Server();
	void RunServer();
	void SendingData(SOCKADDR_IN addr, int sizeOfAddr);
	void ReceivingData(SOCKET &connectionF, SOCKET &connectionG, double x);
	void CloseServer();

	void RunProcesses();
	void CloseProcesses();
private:
	WSAData m_wsaData;
	SOCKET m_sListen;
	int m_x;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	std::mutex mu;
};

