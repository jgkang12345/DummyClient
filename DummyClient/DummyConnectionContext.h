#pragma once
class DummyConnectionContext
{
private:
	std::map<int32, Connection*> _connectionContext;
	SpinLock					 _spinLock;

public:
	static DummyConnectionContext* GetInstance()
	{
		static DummyConnectionContext s_instance;
		return &s_instance;
	}

public:
	void AddConnetion(int32 connectionId, Connection* connection);
	void RemoveConnection(int32 connectionId);
	Connection* GetConnection(int32 connectionId);
	void Update(int32 deltaTick);
};

