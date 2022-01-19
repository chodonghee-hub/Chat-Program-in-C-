#include "cTcpServer.h"

cTcpServer::cTcpServer()
{
	m_bAcceptThreadStart = false;
	m_bRecvThreadStart = false;

	if (!CheckWinSockVersion()) { return; }
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (!CheckValidSocket(s)) { closesocket(s); }
	if (!BindSocket()) { return; };
	if (!ListenServerSocket()) { return; };
	
	// Init Server 
	cout << " [ Init Server Socket ]  " << endl;

	// Accept 
	CreateAcceptThread();
	// Receive, Send
	// close , WSACleanup 

}

cTcpServer::~cTcpServer()
{
	m_bRecvThreadStart = false;
	m_bAcceptThreadStart = false;
}

bool cTcpServer::CheckValidSocket(SOCKET & s)
{
	if (s != INVALID_SOCKET){
		// Valid Socket
		return true;
	}
	else {
		// Invalid Socket
		cout << "** CheckValidSocket error : " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}	
}

bool cTcpServer::CheckWinSockVersion()
{
	if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0) {
		cout << "** CheckWinSockVersion error : " << WSAGetLastError() << endl;
		WSACleanup();	return false;
	}
	return true;
}

void cTcpServer::CreateAcceptThread()
{
	m_bAcceptThreadStart = true;
	m_thAcceptThread = thread(&AcceptThreadProc, this);	//질문
}

void cTcpServer::CreateRecvThread()
{
	m_bRecvThreadStart = true;
	//m_thRecvThread = thread(RecvThreadProc, this);	//질문
}

bool cTcpServer::BindSocket()
{
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4444);		// PORT : 4444
	addr.sin_addr.S_un.S_addr = htonl(ADDR_ANY);
	if (::bind(s, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		cout << "** BindSocket error : " << WSAGetLastError() << endl;
		WSACleanup();
		closesocket(s);
		return false;
	}
	return true;
}

bool cTcpServer::ListenServerSocket()
{
	if (listen(s, SOMAXCONN) != 0) {
		cout << "** ListenServerSocket error : " << WSAGetLastError() << endl;
		closesocket(s);
		WSACleanup();
		return false;
	}
	return true;
}

void cTcpServer::AcceptThreadProc(LPVOID lp)
{
	// cs = accept(socket, (SOCKADDR*) &addr, sizeof(&addr)
	// CheckValidSocket(cs);

	SOCKET cs;
	cTcpServer *p = (cTcpServer*)lp;
	
	int size = sizeof(p->addr);
	while (p->m_bAcceptThreadStart) {
		cs = accept(p->s, (SOCKADDR*)&p->addr, &size);
		if (cs == INVALID_SOCKET) {
			closesocket(cs);
			WSACleanup();
			return;
		}
	}
	

//	return nullptr;
}

void  cTcpServer::RecvThreadProc(LPVOID lp)
{
//	return nullptr;
}
