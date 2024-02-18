#pragma once
#include "DummyClientApp.h"
class TCPConnector;

class MyDummyClientApp : public DummyClientApp
{
private:
	TCPConnector* _loginServerConnection;
	TCPConnector* _villageServerConnection;
	int32 _offset;

public:
	MyDummyClientApp(
		int32 maxDummyConnection
		, const char* ip
		, uint16 enterPort
		, int32 offset
		, tConnectionFactroy tConnectionFactoryFunc
	);

	virtual ~MyDummyClientApp();

public:
	virtual void Start() override;
	void EnterServer(int32 playerSQ);
};

