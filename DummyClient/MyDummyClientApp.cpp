#include "pch.h"
#include "MyDummyClientApp.h"
#include "TCPConnector.h"
#include "DummyConnection.h"
#include "IOCPCore.h"
#include "DummyPlayer.h"
MyDummyClientApp::MyDummyClientApp(int32 maxDummyConnection, const char* ip, uint16 enterPort, int32 offset, tConnectionFactroy tConnectionFactoryFunc)
	:DummyClientApp(maxDummyConnection, ip, tConnectionFactoryFunc), _offset(offset)
{
	_loginServerConnection = new TCPConnector(ip, 30003, tConnectionFactoryFunc);
	_villageServerConnection = new TCPConnector(ip, enterPort, tConnectionFactoryFunc);
}

MyDummyClientApp::~MyDummyClientApp()
{
}

void MyDummyClientApp::Start()
{
	wprintf(L"Dummy total : %d\n", _maxDummyConnection);
	try
	{
		for (int i = _offset; i <= _maxDummyConnection; i++)
		{
			DummyConnection* loginNewConnection = reinterpret_cast<DummyConnection*>(_loginServerConnection->Connect());
			if (loginNewConnection != nullptr)
			{
				_iocpCore->RegisterIOCP(loginNewConnection);
				loginNewConnection->RequestLogin(i);
			}

			if (i % 100 == 0)
				Sleep(10000);

		}
	}
	catch (std::wstring error)
	{
		wprintf(L"Dummy Error\n");
	}
}

void MyDummyClientApp::EnterServer(int32 playerSQ)
{
	Connection* newSession = _villageServerConnection->Connect();
	if (newSession != nullptr)
	{
		_iocpCore->RegisterIOCP(newSession);
		newSession->OnConnect();
		// TODO INIT PACEKT ø‰√ª
		BYTE sendBuffer[256] = {};
		BinaryWriter bw(sendBuffer);
		PacketHeader* pktHeader = bw.WriteReserve<PacketHeader>();
		bw.Write((int32)playerSQ);
		bw.Write((int32)playerSQ);
		Pos startPos = DataManager::GetInstance()->PopStartPos();
		bw.Write((float)startPos.x);
		bw.Write((float)0);
		bw.Write((float)startPos.z);
		bw.Write(DataManager::GetInstance()->serverType);
		pktHeader->_type = PacketProtocol::C2S_PLAYERINIT;
		pktHeader->_pktSize = bw.GetWriterSize();
		reinterpret_cast<DummyConnection*>(newSession)->DummySend(sendBuffer, bw.GetWriterSize());
	}
}
