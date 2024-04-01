#include "pch.h"
#include "MyDummyClientApp.h"
#include "DummyConnection.h"
#include "IOCPCore.h"
#include "ThreadManager.h"
#include "DummyConnectionContext.h"
#include "MapManager.h"
unsigned int _stdcall Dispatch(void* Args)
{
	MyDummyClientApp* app = reinterpret_cast<MyDummyClientApp*>(Args);
	while (true)
		app->GetIOCPCore()->Dispatch();
}

unsigned int _stdcall Update(void* Args)
{	
	int32 currentTick = ::GetTickCount64();
	int32 lastTick = 0;
	while (true)
	{
		currentTick = ::GetTickCount64();

		if (lastTick == 0)
			lastTick = currentTick;

		int32 deltaTick = currentTick - lastTick;
		if (deltaTick >= 200)
		{
			DummyConnectionContext::GetInstance()->Update(deltaTick);
			Sleep(200);
			lastTick = currentTick;
		}
	}
}


void NoviceServerInit();
void VillageServerInit();
void InterMediateServerInit();
void HightServerInit();

void HightServerInit()
{
	DataManager::GetInstance()->serverType = ServerType::HIGH;
	MapManager::GetInstance()->MapLoadField(ServerType::HIGH, "map\\HighFieldMap.dat");
}

void NoviceServerInit()
{
	DataManager::GetInstance()->serverType = ServerType::NOVICE;
	MapManager::GetInstance()->MapLoadField(ServerType::NOVICE, "map\\NoviceFieldMap.dat");
}

void InterMediateServerInit()
{
	DataManager::GetInstance()->serverType = ServerType::INTERMEDIATE;
	MapManager::GetInstance()->MapLoadField(ServerType::INTERMEDIATE, "map\\IntermediateFieldMap.dat");
}

void VillageServerInit()
{
	DataManager::GetInstance()->serverType = ServerType::VILLAGE;
	MapManager::GetInstance()->MapLoad(ServerType::VILLAGE, "map\\VillageMap.dat");
}

int main(int argc, char* argv[])
{
	uint16 enterServer = std::atoi(argv[1]); // 30004 ~ 30011
	uint16 dummyCount = std::atoi(argv[2]); // 500
	uint16 offset = 1;

	printf("DummyClient cnt: %d, enterPort: %d \n", dummyCount, enterServer);

	const char* ip = "58.236.130.58";

	switch (enterServer)
	{
	case 30007:
	case 30008:
		NoviceServerInit();
		break;

	case 30004:
	case 30005:
	case 30006:
		VillageServerInit();
		break;

	case 30009:
		InterMediateServerInit();
		break;

	case 30010:
	case 30011:
		HightServerInit();
		break;
	}

	MyDummyClientApp dummyClientApp(dummyCount, ip, enterServer, offset, DummyConnection::MakeGameSession);
	DataManager::GetInstance()->app = &dummyClientApp;

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	int32 threadCount = sysInfo.dwNumberOfProcessors * 2;

	for (int i = 0; i < threadCount; i++)
		ThreadManager::GetInstacne()->Launch(Dispatch, &dummyClientApp);

	dummyClientApp.Start();
	ThreadManager::GetInstacne()->Launch(Update, &dummyClientApp);
	ThreadManager::GetInstacne()->AllJoin();
	return 0;
}