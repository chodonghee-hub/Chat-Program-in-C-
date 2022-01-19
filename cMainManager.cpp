#include "cMainManager.h"

cMainManager::cMainManager()
{
	m_pTcpServer = nullptr;
	CreateTcpServer();
}

cMainManager::~cMainManager()
{
	delete m_pTcpServer;
	m_pTcpServer = nullptr;
}

bool cMainManager::CreateTcpServer()
{
	bool bRet = true;
	try {
		m_pTcpServer = new (nothrow)cTcpServer();

		if (m_pTcpServer == nullptr) {
			throw 0;
		}
	}
	catch (int e)
	{
		switch (e)
		{
		case 0:
			cout << "** tcp server error : " << WSAGetLastError() << endl;
			break;
	
		default:
			cout << "** CreateTcpServer error : " << WSAGetLastError() << endl;
			break;
		}
	}
	return false;
}
