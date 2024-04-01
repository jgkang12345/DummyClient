#pragma once
class MyDummyClientApp;
class DataManager
{
public:	
	MyDummyClientApp* app;
	ServerType serverType;
	std::map<ServerType, std::vector<Pos>> startPos;
	CriticalSectionObject cs;
	uint32 index = 0;
public:
	static DataManager* GetInstance()
	{
		static DataManager s_instance;
		return &s_instance;
	}

	DataManager();

	Pos PopStartPos() 
	{
		LockGuard lockGuard(&cs);
		index++;
		index %= 10;
		Pos pos  = startPos[serverType][index];
		return pos;
	}
};

