#pragma once

#include "ConnectionManager.h"
#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"
#include "../net/EndPoint.h"

namespace OpenMX {

class MessageHandler {
private:
protected:
    ConnectionManager& m_manager;

    MessageHandler(const ConnectionManager& manager);

public:
    virtual int handleConnect(const EndPoint& remoteEndPoint) = 0;
    virtual void handleDisconnect(int connectionId) = 0;
    virtual void handleMessage(int connectionId, int messageId, BinaryReader message) = 0;
    virtual void tick() = 0;
};

} // namespace OpenMX