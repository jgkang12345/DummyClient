#include "pch.h"
#include "DummyConnection.h"
#include "ConnectionContext.h"
#include "PacketHandler.h"
DummyConnection::DummyConnection(const SOCKET& socket, const SOCKADDR_IN& sockAddrIn)
	:Connection(socket, sockAddrIn)
{
}

DummyConnection::~DummyConnection()
{
}

void DummyConnection::OnRecv(Connection* connection, byte* dataPtr, int32 dataLen)
{
	PacketHandler::HandlePacket(static_cast<DummyConnection*>(connection), dataPtr, dataLen);
}

void DummyConnection::OnDisconnect()
{
	ConnectionContext::GetInstance()->RemoveConnection(_connectionId);
}

void DummyConnection::OnConnect()
{
}

void DummyConnection::RequestLogin(int32 sq)
{
	BYTE sendBuffer[256] = {};
	BinaryWriter bw(sendBuffer);
	PacketHeader* pktHeader = bw.WriteReserve<PacketHeader>();

	WCHAR userId[256] = {};
	WCHAR userPw[256] = L"1234";
	swprintf_s(userId, L"dummy%d", sq);

	int32 userIdLen = wcslen(userId) * sizeof(WCHAR);
	int32 userPwLen = 4 * 2;

	bw.Write((int32)userIdLen);
	bw.WriteWString(userId, userIdLen);
	bw.Write((int32)userPwLen);
	bw.WriteWString(userPw, userPwLen);

	pktHeader->_type = PacketProtocol::C2S_LOGIN;
	pktHeader->_pktSize = bw.GetWriterSize();
	Send(sendBuffer, pktHeader->_pktSize);
}
