#pragma once
#include "Player.h"
class DummyPlayer : public Player
{
private:
	Vector3 _destPos;
	Vector3 _vDir;
	std::vector<Pos> _path;
	std::vector<Pos> _conner;
	int32 _heartBeatSumTick = 0;
public:
	DummyPlayer(
		Connection* connection
		, const Vector3& pos
		, wchar* playerName
		, int32 level
		, int32 hp
		, int32 mp
		, int32 damage
		, float speed
		, float defense
		, int32 playerType
		, int32 playerSQ
		, int32 exp);

	virtual ~DummyPlayer() {};

public:
	void Update(int32 deltaTick);

private:
	void UpdateIdle(int32 deltaTick);
	void UpdateMove(int32 deltaTick);
	void PatrolDestSearch();

	void PlayerSyncSend();
	void PlayerSyncMap();
};

