#include "pch.h"
#include "DummyPlayer.h"
#include "Connection.h"
#include "MapManager.h"
int GetRandom0to8()
{
	thread_local std::mt19937 generator(std::random_device{}());

	std::uniform_int_distribution<int> distribution(0, 8);

	return distribution(generator);
}

int GetRandom0to4()
{
	thread_local std::mt19937 generator(std::random_device{}());

	std::uniform_int_distribution<int32> distribution(0, 3);

	return distribution(generator);
}


DummyPlayer::DummyPlayer(Connection* connection, const Vector3& pos, wchar* playerName, int32 level, int32 hp, int32 mp, int32 damage, float speed, float defense, int32 playerType, int32 playerSQ, int32 exp)
	: Player(connection,pos,playerName,level,hp,mp,damage,speed,defense,playerType,playerSQ,exp)
{
}

void DummyPlayer::Update(int32 deltaTick)
{
	State prevState = _state;

	switch (_state)
	{
	case IDLE:
		UpdateIdle(deltaTick);
		break;
	case MOVE:
		UpdateMove(deltaTick);
		break;
	}

	PlayerSyncMap();

	if (prevState != _state)
		PlayerSyncSend();
}

void DummyPlayer::UpdateIdle(int32 deltaTick)
{
	int32 randomCode = GetRandom0to8();
	if (randomCode == 0)
	{
		BYTE sendBuffer[256] = {};
		BinaryWriter bw(sendBuffer);

		WCHAR buffer[256] = {};
		WCHAR username[256] = {};
		::memcpy(username, _playerName, wcslen(_playerName) * sizeof(WCHAR));

		wsprintf(buffer, L"%s:æ»≥Á«œººø‰.", username);
		int32 chatSize = wcslen(buffer) * sizeof(WCHAR);

		PacketHeader* hedaer = bw.WriteReserve<PacketHeader>();
		bw.Write((int32)0);
		bw.Write(chatSize);
		bw.WriteWString(buffer, chatSize);
		hedaer->_type = PacketProtocol::C2S_PLAYERCHAT;
		hedaer->_pktSize = bw.GetWriterSize();
		_connection->Send(sendBuffer, hedaer->_pktSize);
	}
	else if (randomCode == 6)
	{
		// ¿Ãµø¿∏∑Œ πŸ≤„ø‰ 
		PatrolDestSearch();
	}
}

void DummyPlayer::UpdateMove(int32 deltaTick)
{
	Vector3 dir = Vector3{ _conner[0].x + 0.5f, 0, _conner[0].z + 0.5f } - _pos;
	Vector3 prevDir = _vDir;

	if (dir.x == 0 && dir.y == 0 && dir.z == 0)
		_vDir = _vDir;
	else
		_vDir = dir.Normalized();

	float dist = abs(_conner[0].x + 0.5f - _pos.x) + abs(_conner[0].z + 0.5f - _pos.z);
	float moveDist = _speed * (deltaTick / 1000.f);
	Vector3 nextPos = _pos + (_vDir * moveDist);

	if (dist <= moveDist)
	{
		nextPos = { _conner[0].x + 0.5f ,0 ,_conner[0].z + 0.5f };
		_conner.erase(_conner.begin());
		_prevPos = _pos;
		_pos = nextPos;
		PlayerSyncSend();
		if (_conner.size() == 0)
		{
			_state = IDLE;
			_path.clear();
			_conner.clear();
		}
		return;
	}
	_prevPos = _pos;
	_pos = nextPos;
}

void DummyPlayer::PatrolDestSearch()
{
	int32 x = static_cast<int32>(_pos.x);
	int32 z = static_cast<int32>(_pos.z);

	int32 dx[4] = { 0,5,0,-5 };
	int32 dz[4] = { 5,0,-5,-0 };

	int32 randomDir = GetRandom0to4();

	int32 target_x = x + dx[randomDir];
	int32 target_z = z + dz[randomDir];

	if (MapManager::GetInstance()->CanGo(target_z, target_x) == false)
	{
		_state = State::IDLE;
		return;
	}

	_destPos = Vector3{ target_x + 0.5f, 0, target_z + 0.5f };
	MapManager::GetInstance()->FindPath(_destPos, _pos, _path);

	Vector3 dir = Vector3{ _path[0].x + 0.5f, 0, _path[0].z + 0.5f } - _pos;
	_vDir = dir.Normalized();

	_conner.clear();
	Pos prevPos = { x , z };
	Pos prevDir = prevPos - prevPos;
	for (int32 i = 0; i < _path.size(); i++)
	{
		Pos dir = _path[i] - prevPos;
		if (dir != prevDir)
		{
			_conner.push_back(_path[i]);
		}
		prevPos = _path[i];
		prevDir = dir;
	}

	_conner.push_back(_path[_path.size() - 1]);

	_destPos = Vector3{ _path.back().x + 0.5f, 0, _path.back().z + 0.5f };

	_state = State::MOVE;
}

void DummyPlayer::PlayerSyncSend()
{
	BYTE sendBuffer[256];
	BinaryWriter bw(sendBuffer);
	PacketHeader* pktHeader = bw.WriteReserve<PacketHeader>();

	bw.Write((int32)_playerSQ);
	bw.Write(_state);
	bw.Write(_dir);
	bw.Write(_mouseDir);
	bw.Write(_pos);
	bw.Write(_cameraLocalRotation);

	if (_conner.size() == 0)
	{
		Vector3 target{ 0,0,0 };
		bw.Write(target);
	}
	else
	{
		Vector3 v3 = { _conner.begin()->x + 0.5f, 0, _conner.begin()->z + 0.5f };
		bw.Write(v3);
	}
	bw.Write(_angle);
	bw.Write((byte)1);

	pktHeader->_type = PacketProtocol::C2S_PLAYERSYNC;
	pktHeader->_pktSize = bw.GetWriterSize();
	_connection->Send(sendBuffer, pktHeader->_pktSize);
}

void DummyPlayer::PlayerSyncMap()
{
	int prevPosX = (int)_prevPos.x;
	int prevPosZ = (int)_prevPos.z;

	int nowPosX = (int)_pos.x;
	int nowPosZ = (int)_pos.z;

	if (prevPosX != nowPosX || prevPosZ != nowPosZ)
	{
		// ∏  ¡¬«• µø±‚»≠
		BYTE sendBuffer[256];
		BinaryWriter bw(sendBuffer);
		PacketHeader* pktHeader = bw.WriteReserve<PacketHeader>();


		bw.Write((int32)_playerSQ);
		bw.Write(_state);
		bw.Write(_dir);
		bw.Write(_mouseDir);
		bw.Write(_pos);
		bw.Write(_cameraLocalRotation);
		if (_conner.size() == 0)
		{
			Vector3 target{ 0,0,0 };
			bw.Write(target);
		}
		else
		{
			Vector3 v3 = { _conner.begin()->x + 0.5f, 0, _conner.begin()->z + 0.5f };
			bw.Write(v3);
		}
		bw.Write((byte)1);
		bw.Write(_angle);

		pktHeader->_type = PacketProtocol::C2S_MAPSYNC;
		pktHeader->_pktSize = bw.GetWriterSize();
		_connection->Send(sendBuffer, pktHeader->_pktSize);
		_prevPos = _pos;
	}
}
