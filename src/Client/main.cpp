#include "..\pch.h"

#include "..\Network\TCPConnection.hpp"
#include "..\Debugger.h"

// #include <ws2tcpip.h> // InetPton

int __cdecl main(int argc, char **argv)
{
	WSADATA wsaData; 
	INT     iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		$ERROR(TEXT("WSAStartup failed with error: %d\n"), iResult);

		system("pause");
		return 1;
	}
	$I(TEXT("Startup finished\n"));

	TCPClient client;
	if(!client.init())
		return 1;

	if(!client.connect())
		return 1;

	std::string message(TCP_MESSAGE_LENGTH, { });
	if (argc > 2) // _CRT_SECURE_NO_WARNINGS
	{
		message = argv[2] + std::string(" ") + argv[3];

		client.send(message);
	}
	else
	{
		message = "0 HelloWorld!\0";

		client.send(message);
	}
	SleepEx(1000, FALSE);
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		POINT cursor = { 0 };
		GetCursorPos(&cursor);
		$I(TEXT("%d %d\n"), cursor.x, cursor.y);

		message = "6 " + std::to_string(cursor.x) + " " + std::to_string(cursor.y);
		
		if(!client.send(message))
			break;
		
		SleepEx(3000, FALSE);
		message.clear();
	}

	std::string result(RESULT_LENGTH, { });
	client.recv(result);
	$I(TEXT("Result: %hs\n"), result.c_str());

	WSACleanup();
	system("pause");
	return 0;
}
