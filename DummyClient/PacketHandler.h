#pragma once
class DummyConnection;
class PacketHandler
{
public:
	static void HandlePacket(DummyConnection* connection, BYTE* packet, int32 packetSize);
private:
	static void HandlePacket_S2C_LOGIN(DummyConnection* connection, BYTE* packet, int32 packetSize);
	static void HandlePacket_S2C_PLAYERINIT(DummyConnection* connection, BYTE* packet, int32 packetSize);
	static void HandlePacket_S2C_HEARTBIT(DummyConnection* connection, BYTE* packet, int32 packetSize);
};

