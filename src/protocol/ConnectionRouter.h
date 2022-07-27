#pragma once

#include "ConnectionManager.h"
#include "WpnTypes.h"
#include <string>
#include <unordered_map>

namespace OpenMX {

// pri client: primary, secondary server, chat server, chat client, upload, download
// sec client: secondary client, chat client, upload, download
// chat servr: primary, chat server
// cache server: only 1 CM needed

class CacheConnectionRouter {
private:
    ConnectionManager* m_manager;

public:
    CacheConnectionRouter()
        : m_manager(nullptr)
    {
    }
    void setManager(ConnectionManager& manager) { m_manager = &manager; }

    void route(Connection* connection);
};

class ClientConnectionRouter {
private:
    ConnectionManager* m_primary;
    ConnectionManager* m_secondary;
    ConnectionManager* m_chatClient;
    ConnectionManager* m_chatServer;
    ConnectionManager* m_upload;
    ConnectionManager* m_download;

public:
    ClientConnectionRouter()
        : m_primary(nullptr)
        , m_secondary(nullptr)
        , m_chatClient(nullptr)
        , m_chatServer(nullptr)
        , m_upload(nullptr)
        , m_download(nullptr)
    {
    }
    void setPrimary(ConnectionManager& manager) { m_primary = &manager; }
    void setSecondary(ConnectionManager& manager) { m_secondary = &manager; }
    void setChatClient(ConnectionManager& manager) { m_chatClient = &manager; }
    void setChatServer(ConnectionManager& manager) { m_chatServer = &manager; }
    void setUpload(ConnectionManager& manager) { m_upload = &manager; }
    void setDownload(ConnectionManager& manager) { m_download = &manager; }

    void route(Connection* connection);
};

} // namespace OpenMX