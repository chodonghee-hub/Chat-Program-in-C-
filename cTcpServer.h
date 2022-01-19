#pragma once
#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <thread>
#include <WinSock2.h>
#include <windows.h>
#include <queue>


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "ws2_32.lib")


//#define RECV_MAX 1024

const static unsigned int RECV_MAX = 1024;

using namespace std;

class cTcpServer
{
public :
	cTcpServer();
	~cTcpServer();
private:
	WSADATA		wsaData;
	SOCKET		s;
	SOCKADDR_IN	addr;
	char Buffer[RECV_MAX + 1];

	thread m_thAcceptThread;
	thread m_thRecvThread;

	bool m_bAcceptThreadStart;
	bool m_bRecvThreadStart;
	bool CheckValidSocket(SOCKET &s);
	bool BindSocket();
	bool CheckWinSockVersion();
	bool ListenServerSocket();
	
	void CreateAcceptThread();
	void CreateRecvThread();

	static void AcceptThreadProc(LPVOID lp);
	static void RecvThreadProc(LPVOID lp);
};

