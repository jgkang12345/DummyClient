#pragma once
class MyDummyClientApp;
class DataManager
{
public:	
	MyDummyClientApp* app;

public:
	static DataManager* GetInstance()
	{
		static DataManager s_instance;
		return &s_instance;
	}
};

