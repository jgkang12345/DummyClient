#pragma once
class MyDummyClientApp;
class DataManager
{
public:	
	MyDummyClientApp* app;
	ServerType serverType;
	std::map<ServerType, std::vector<Pos>> startPos;
	CriticalSectionObject cs;

	uint32 count = 30;
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
		count--;
		if (count <= 0)
		{
			count = 30;
			index++;
			index %= 6;
		}
		Pos pos  = startPos[serverType][index];
		return pos;
	}
};

