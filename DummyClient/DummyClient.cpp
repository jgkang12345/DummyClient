#include "pch.h"
#include "MyDummyClientApp.h"
#include "DummyConnection.h"
#include "IOCPCore.h"
#include "ThreadManager.h"
unsigned int _stdcall Dispatch(void* Args)
{
	MyDummyClientApp* app = reinterpret_cast<MyDummyClientApp*>(Args);
	while (true)
		app->GetIOCPCore()->Dispatch();
}

int main() 
{
	uint16 enterServer;
	int32 dummyCount;
	printf("� ������ ������ ���Դϱ�?\n 30002=�ʺ����ʵ�, 30004=��������\n");
	scanf_s("%d", &enterServer);
	const char* ip = "127.0.0.1";
	printf("���̴� ��� ���� �� �Դϱ�?\n");
	scanf_s("%d", &dummyCount);
	int32 offset;
	printf("SQ Offset?\n");
	scanf_s("%d", &offset);

	MyDummyClientApp dummyClientApp(dummyCount, ip, enterServer, offset, DummyConnection::MakeGameSession);
	DataManager::GetInstance()->app = &dummyClientApp;

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	int32 threadCount = sysInfo.dwNumberOfProcessors * 2;

	for (int i = 0; i < threadCount; i++)
		ThreadManager::GetInstacne()->Launch(Dispatch, &dummyClientApp);

	dummyClientApp.Start();

	ThreadManager::GetInstacne()->AllJoin();
	return 0;
}