#pragma once

//������ � ��������
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <future>

#include <mutex>

#define NUMBER_OF_CLIENTS 2 // �������� ����� �������������� �����, ��� n �������

#pragma warning(disable: 4996)

class Server
{
public:
	Server(double x);
	~Server();
	void RunServer();
	void SendingData(SOCKADDR_IN addr, int sizeOfAddr);
	void ReceivingData(SOCKET &connectionF, SOCKET &connectionG);
	void CloseServer();

	void RunProcesses();
	void CloseProcesses();

	void ProtectedConsoleOutput(std::string str, short b = 0);

private:
	WSAData m_wsaData;
	SOCKET m_sListen;
	double m_x;
	STARTUPINFO si_1;
	STARTUPINFO si_2;
	PROCESS_INFORMATION pi_1;
	PROCESS_INFORMATION pi_2;

	std::mutex mu;
};

