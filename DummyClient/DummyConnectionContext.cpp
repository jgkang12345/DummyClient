#include "pch.h"
#include "DummyConnectionContext.h"
#include "DummyConnection.h"
void DummyConnectionContext::AddConnetion(int32 connectionId, Connection* connection)
{
    LockGuard lockGuard(&_spinLock);
    _connectionContext.insert({ connectionId, connection });
}

void DummyConnectionContext::RemoveConnection(int32 connectionId)
{
    LockGuard lockGuard(&_spinLock);
    _connectionContext.erase(connectionId);
}

Connection* DummyConnectionContext::GetConnection(int32 connectionId)
{
    Connection* ret = nullptr;
    const auto& connection = _connectionContext.find(connectionId);
    
    if (connection == _connectionContext.end())
        ret = connection->second;

    return ret;
}

void DummyConnectionContext::Update(int32 deltaTick)
{
    LockGuard lockGuard(&_spinLock);
    for (const auto& dummyMap : _connectionContext)
        if (dummyMap.second)
            reinterpret_cast<DummyConnection*>(dummyMap.second)->Update(deltaTick);
}
