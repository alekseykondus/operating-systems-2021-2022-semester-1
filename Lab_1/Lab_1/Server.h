#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <future>
#include <mutex>
#include "Colored—onsoleOutput.h"


#pragma warning(disable: 4996)
class Server
{
public:
	Server(double x);
	~Server();
	void RunServer();
	void SendingData(SOCKADDR_IN addr, int sizeOfAddr);
	void ReceivingData(SOCKET &connectionF, SOCKET &connectionG, SOCKADDR_IN &addr);
	void CloseServer();

	void RunProcesses();
	void CloseProcesses();

	void ProtectedConsoleOutput(std::string str, short b = 0);

	//implemented advanced version (Initiate cancellation dialog by the special key - ESC)
	std::future<void> DialogByESC(std::future<char*> &result_F, std::future<char*> &result_G);
	char* RecalculationF(SOCKET& connectionF, SOCKADDR_IN& addr, bool& isFCalculationsDone);
	char* RecalculationG(SOCKET& connectionG, SOCKADDR_IN& addr, bool& isGCalculationsDone);
private:
	WSAData				m_wsaData;
	SOCKET				m_sListen;
	double				m_x;
	STARTUPINFO			si_1;
	STARTUPINFO			si_2;
	PROCESS_INFORMATION pi_1;
	PROCESS_INFORMATION pi_2;

	bool				m_userCanceledCalculations;
	std::mutex			mu;
};

