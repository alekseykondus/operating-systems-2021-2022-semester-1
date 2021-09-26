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
	addr.sin_family = AF_INET;
	int sizeOfAddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);

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
	SendingData(addr, sizeOfAddr);


	CloseServer();
}

void Server::SendingData(SOCKADDR_IN addr, int sizeOfAddr)
{
	SOCKET newConnectionF;
	SOCKET newConnectionG;

	newConnectionF = accept(m_sListen, (SOCKADDR*)&addr, &sizeOfAddr);
	newConnectionG = accept(m_sListen, (SOCKADDR*)&addr, &sizeOfAddr);

	if (newConnectionF == SOCKET_ERROR || newConnectionG == SOCKET_ERROR) {
		closesocket(newConnectionF);
		closesocket(newConnectionG);
		printf("Unable to connect to server: %ld\n", WSAGetLastError());
		WSACleanup();
	}
	else {
		std::cout << "Clients connected" << std::endl;
		double x = 1.1111111;
		char xSTR[10];
		sprintf(xSTR, "%f", x);

		send(newConnectionF, xSTR, sizeof(xSTR), NULL);
		send(newConnectionG, xSTR, sizeof(xSTR), NULL);

		std::cout << "I SEND" << std::endl << std::endl;

		ReceivingData(newConnectionF, newConnectionG, x);
	}

}

void Server::ReceivingData(SOCKET &connectionF, SOCKET &connectionG, double x)
{
	//Получаем информацию с клиентов!
	std::future<char*> result_F = std::async(std::launch::async, [&]() {
		char strFromF[100];
		int recV = recv(connectionF, strFromF, sizeof(strFromF), NULL);
		mu.lock();
		Sleep(10);
		if (recV > 0)
			std::cout << "strFromF = " << strFromF << std::endl;
		else
			std::cout << "recV = " << recV << std::endl;

		if (recV < 0)
			std::cout << "Error: = recV < 0" << std::endl;
		mu.unlock();
		return strFromF;
		});

	std::future<char*> result_G = std::async(std::launch::async, [&]() {
		char strFromG[100];
		int recV = recv(connectionG, strFromG, sizeof(strFromG), NULL);
		mu.lock();
		Sleep(10);
		if (recV > 0)
			std::cout << "strFromG = " << strFromG << std::endl;
		else
			std::cout << "recV = " << recV << std::endl;

		if (recV < 0)
			std::cout << "Error: = recV < 0" << std::endl;
		mu.unlock();
		return strFromG;
		});

	//std::future_status f1 = result_F.wait_for(std::chrono::milliseconds(1)); //чтобы испытать timeout
	std::future_status f1 = result_F.wait_for(std::chrono::seconds(5));
	std::future_status f2 = result_G.wait_for(std::chrono::seconds(5));

	if (f1 == std::future_status::timeout || f2 == std::future_status::timeout)
		std::cout << "Eror: timeout" << std::endl;


	if (f1 == std::future_status::ready && f2 == std::future_status::ready) {
		//char* F = result_F.get();
		double doubleFromF = atof(result_F.get());
		//char* G = result_G.get();
		double doubleFromG = atof(result_G.get());

		std::cout << doubleFromF << " FROM F" << std::endl;
		std::cout << doubleFromG << " FROM G" << std::endl << std::endl;

		std::cout << "After multiplication: " << doubleFromF * doubleFromG << std::endl << std::endl;
	
//		std::cout << "x * x = " << x * x << std::endl <<
//			"x * x * x =" << x * x * x << std::endl;
	}
	std::cout << "WSAGetLastError() = " << WSAGetLastError() << std::endl << std::endl << std::endl;
	closesocket(connectionF);
	closesocket(connectionG);
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

	CreateProcess(czCommandLineF.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi); 
	Sleep(10);
	CreateProcess(czCommandLineG.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
}

void Server::CloseProcesses()
{
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
