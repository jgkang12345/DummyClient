#include "pch.h"
#include "PacketHandler.h"
#include "MyDummyClientApp.h"
#include "DummyConnection.h"
#include "DummyConnectionContext.h"
#include "DummyPlayer.h"
void PacketHandler::HandlePacket(DummyConnection* connection, BYTE* packet, int32 packetSize)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(packet);
	BYTE* dataPtr = packet + sizeof(PacketHeader);
	int32 dataSize = packetSize - sizeof(PacketHeader);

	switch (header->_type)
	{
	case PacketProtocol::S2C_PLAYERINIT:
		HandlePacket_S2C_PLAYERINIT(connection, packet, packetSize);
		break;

	case PacketProtocol::S2C_LOGIN:
		HandlePacket_S2C_LOGIN(connection, dataPtr, dataSize);
		break;
	}
}

void PacketHandler::HandlePacket_S2C_LOGIN(DummyConnection* connection, BYTE* packet, int32 packetSize)
{
	int32 playerSQ;
	int32 canLogin;
	BinaryReader br(packet);
	br.Read(canLogin);
	br.Read(playerSQ);
	
	if (canLogin != 9999)
		return;

	DataManager::GetInstance()->app->EnterServer(playerSQ);
}

void PacketHandler::HandlePacket_S2C_PLAYERINIT(DummyConnection* connection, BYTE* packet, int32 packetSize)
{
	S2C_PLAYERINIT_PACKET* playerInitPacket = reinterpret_cast<S2C_PLAYERINIT_PACKET*>(packet);
	DummyPlayer* dummyPlayer = new DummyPlayer(
		static_cast<Connection*>(connection)
		, playerInitPacket->playerPos
		, playerInitPacket->playerName
		, playerInitPacket->level
		, playerInitPacket->hp
		, playerInitPacket->mp
		, playerInitPacket->damage
		, playerInitPacket->speed
		,0
		,playerInitPacket->playerType
		,playerInitPacket->sessionId
		,playerInitPacket->exp
	);
	connection->SetPlayer(dummyPlayer);
	connection->SetConnectionId(playerInitPacket->sessionId);
	DummyConnectionContext::GetInstance()->AddConnetion(playerInitPacket->sessionId, connection);
}
