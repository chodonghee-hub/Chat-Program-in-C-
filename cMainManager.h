#pragma once
#include <iostream>
#include <winsock2.h>

#include "cTcpServer.h"
class cMainManager
{
public :
	cMainManager();
	~cMainManager();
private:
	cTcpServer *m_pTcpServer;
	bool CreateTcpServer();
};

