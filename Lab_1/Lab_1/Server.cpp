#include "Server.h"

Server::Server(double x) : m_x(x) {
}

Server::~Server()
{
	closesocket(m_sListen);
	WSACleanup();
	std::cout << "Server was stoped. You can close app." << std::endl << std::endl
		<< "Program finished: " << (WSAGetLastError() ? "with error: " + WSAGetLastError() : "without errors") << std::endl;
}

void Server::RunServer()
{
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
		std::cout << std::endl << "Clients connected" << std::endl << std::endl;
		char xSTR[100];
		sprintf(xSTR, "%f", (float)m_x);

		send(newConnectionF, xSTR, sizeof(xSTR), NULL);
		send(newConnectionG, xSTR, sizeof(xSTR), NULL);

		//std::cout << "I SEND" << std::endl << std::endl;

		ReceivingData(newConnectionF, newConnectionG);
	}
}

void Server::ProtectedConsoleOutput(std::string str, short b) {
	mu.lock();
	std::cout << str;
	for (short i = 0; i < b; i++)
		std::cout << std::endl;
	mu.unlock();
}

void Server::ReceivingData(SOCKET &connectionF, SOCKET &connectionG)
{
	//Получаем информацию с клиентов!
	std::future<char*> result_F = std::async(std::launch::async, [&]() {
		char strFromF[100];

		int recV = recv(connectionF, strFromF, sizeof(strFromF), NULL);
		Sleep(10);
/*		mu.lock();
		if (recV > 0)
			std::cout << "strFromF = " << strFromF << std::endl;
		else
			std::cout << "recV = " << recV << std::endl;

		if (recV < 0)
			std::cout << "Error: = recV < 0" << std::endl;
		mu.unlock();
*/
		return strFromF;
		});

	std::future<char*> result_G = std::async(std::launch::async, [&]() {
		char strFromG[100];
		int recV = recv(connectionG, strFromG, sizeof(strFromG), NULL);
		Sleep(10);
/*		mu.lock();
		if (recV > 0) 
			std::cout << "strFromG = " << strFromG << std::endl;
		else
			std::cout << "recV = " << recV << std::endl;

		if (recV < 0)
			std::cout << "Error: = recV < 0" << std::endl;
		mu.unlock();
*/
		return strFromG;
		});

	std::future<void> resultOfUserInput = std::async(std::launch::async, [&]() {
		while (result_F.valid() || result_G.valid()) {
			if (GetAsyncKeyState(27) & 0x0001) {
//				mu.lock();
				ProtectedConsoleOutput("Please confirm that computation should be stopped y(es, stop)/n(ot yet): ");
				
				char userInput;	
				bool isThereTime = true;

				std::future<void> userInputFuture = std::async([&]() {
					
//					auto begin = std::chrono::steady_clock::now();
//					auto end = std::chrono::steady_clock::now();
//					while (end - begin < std::chrono::seconds(5)) {
					while (isThereTime) {
						if (GetAsyncKeyState(89) & 0x0001) {
							userInput = 'y';
							std::cout << 'y' << std::endl;
							break;
						}
						else if (GetAsyncKeyState(78) & 0x0001) {
							userInput = 'n';
							std::cout << 'n' << std::endl;
							break;
						}
//						end = std::chrono::steady_clock::now();
					}
					return;
				});

				std::future_status userInputWait = userInputFuture.wait_for(std::chrono::seconds(5));
				isThereTime = false;
				if (userInputWait == std::future_status::ready) {
					if (userInput == 'y') {
						ProtectedConsoleOutput("Overridden by system", 2);
						TerminateProcess(pi_1.hProcess, 0);
						TerminateProcess(pi_2.hProcess, 0);
					}
					else if (userInput == 'n') {
						ProtectedConsoleOutput("Proceeding...", 2);
						//do nothing, continue to count 
					}
					else {
						ProtectedConsoleOutput("You entered the uncorrect value! The calculations continue ... ", 2);
					}
				}
				else if (userInputWait == std::future_status::timeout){
					ProtectedConsoleOutput("Action is not confirmed within 5 second.Proceeding...", 2);
				}
//				mu.unlock();
			}
		}
		return;
	});

	std::future_status fWait = result_F.wait_for(std::chrono::seconds(10));
	closesocket(connectionF);
	std::future_status gWait = result_G.wait_for(std::chrono::seconds(10));
	closesocket(connectionG);


	bool FisValid = result_F.valid();
	bool GisValid = result_G.valid();
	char* F = result_F.get();
	char* G = result_G.get();
	resultOfUserInput.wait();


	if (fWait == std::future_status::timeout) {
		ProtectedConsoleOutput("Result F: timeout error", 1);
	}
	if (gWait == std::future_status::timeout) {
		ProtectedConsoleOutput("Result G: timeout error", 1);
	}

//	if (WSAGetLastError() == 1460)
//		std::cout << "ERROR: timeout" << std::endl;
	if (fWait == std::future_status::ready || gWait == std::future_status::ready) {
		
		if (FisValid && (!(strcmp(F, "hard fail")) || !(strcmp(F, "soft fail"))))
			ProtectedConsoleOutput(std::string("Result F :") + F, 1);
		else if (fWait == std::future_status::ready) {
			ProtectedConsoleOutput(std::string("Result F :") + F, 1);
			FisValid = false;
		}

		if (GisValid && (!(strcmp(G, "hard fail")) || !(strcmp(G, "soft fail"))))
			ProtectedConsoleOutput(std::string("Result G :") + G, 1);
		else if (gWait == std::future_status::ready) {
			ProtectedConsoleOutput(std::string("Result G :") + G, 1);
			GisValid = false;
		}

		if (!FisValid && !GisValid)
			ProtectedConsoleOutput(std::string("After summation: ") + std::to_string(atof(F) + atof(G)), 2);
	}
//	closesocket(connectionF);
//	closesocket(connectionG);
}

void Server::CloseServer()
{
	CloseProcesses();
}

void Server::RunProcesses()
{
	//запуск процесов!
	ZeroMemory(&si_1, sizeof(si_1));
	ZeroMemory(&si_2, sizeof(si_2));
	si_1.cb = sizeof(si_1);
	si_2.cb = sizeof(si_2);
	ZeroMemory(&pi_1, sizeof(pi_1));
	ZeroMemory(&pi_2, sizeof(pi_2));

	std::wstring czCommandLineF = L"C:\\Users\\Professional\\source\\repos\\Lab_1\\Debug\\f.exe";
	std::wstring czCommandLineG = L"C:\\Users\\Professional\\source\\repos\\Lab_1\\Debug\\g.exe";

	CreateProcess(czCommandLineF.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si_1, &pi_1); 
	Sleep(10);
	CreateProcess(czCommandLineG.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si_2, &pi_2);
}

void Server::CloseProcesses()
{
	CloseHandle(pi_1.hProcess);
	CloseHandle(pi_2.hProcess);
	CloseHandle(pi_1.hThread);
	CloseHandle(pi_2.hThread);
}
