//Работа с сокетами
#pragma comment(lib, "ws2_32.lib")
//#include <winsock2.h>


#include <windows.h>
#include <string>
#include <iostream>
#include <future>

SOCKET Connections[2];
int Counter = 0;

#pragma warning(disable: 4996)
int main(int argc, char* argv[])
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

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeOfAddr);
	listen(sListen, SOMAXCONN);

	//+тут походу нужно запускать новый процесс
	//запуск процесов!
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	std::wstring czCommandLineF = L"C:\\Users\\Professional\\source\\repos\\Lab_1\\Debug\\f.exe";
	std::wstring czCommandLineG = L"C:\\Users\\Professional\\source\\repos\\Lab_1\\Debug\\g.exe";

	std::future<void> result_F = std::async(std::launch::async, [&]() { CreateProcess(czCommandLineF.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi); });
	std::future<void> result_G = std::async(std::launch::async, [&]() { CreateProcess(czCommandLineG.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi); });


	//новый соккет, чтобы удерживать соединение с клиентом
	SOCKET newConnection;

	for (size_t i = 0; i < 2; i++) {
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeOfAddr);

		if (newConnection == 0) {
			std::cout << "Error: The client was unable to connect to the server" << std::endl;
		}
		else {
			std::cout << "Client connected" << std::endl;
			char strToClient[256] =  "Hello. It is my first network program!";
			send(newConnection, strToClient, sizeof(strToClient), NULL);
		}
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);


	//запуск процесов!
	/*STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	std::wstring czCommandLineF = L"C:\\Users\\Professional\\source\\repos\\Lab_1\\Debug\\f.exe";
	std::wstring czCommandLineG = L"C:\\Users\\Professional\\source\\repos\\Lab_1\\Debug\\g.exe";

	std::future<void> result_F = std::async(std::launch::async, [&]() { CreateProcess(czCommandLineF.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi); });
	std::future<void> result_G = std::async(std::launch::async, [&]() { CreateProcess(czCommandLineG.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi); });

	/*if (CreateProcess(czCommandLineF.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi) &&
		CreateProcess(czCommandLineG.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi) ) {
		std::cout << "process" << std::endl;
		std::cout << "handle " << pi.hProcess << std::endl;
		Sleep(1000);				// подождать
		TerminateProcess(pi.hProcess, NO_ERROR);	// убрать процесс
	}
	else {
		std::cout << "Error" << std::endl;
		return 0;
	}
	//
	// Close process and thread handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	*/
	return 0;
}

