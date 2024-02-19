#pragma once
#include "Connection.h"
class DummyPlayer;
class DummyConnection : public Connection
{
private:
	WCHAR _username[50] = {};
	int32 _lastServerPort;

public:
	static Connection* MakeGameSession(const SOCKET& socket, const SOCKADDR_IN& sockAddr) { return new DummyConnection(socket, sockAddr); }

public:
	DummyConnection(const SOCKET& socket, const SOCKADDR_IN& sockAddrIn);
	virtual ~DummyConnection();

public:
	virtual void	OnRecv(Connection* connection, byte* dataPtr, int32 dataLen);
	virtual void	OnDisconnect();
	virtual void    OnConnect();

public:
	void RequestLogin(int32 sq);
	void Update(int32 deltaTick);
};

