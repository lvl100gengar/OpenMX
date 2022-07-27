#include "../net/Connection.h"
#include "MessageHandler.h"
#include <string>
#include <vector>

#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"

namespace OpenMX {

class ConnectionManager {
private:
    std::vector<MessageHandler> m_handlers;

public:
    void addInstance(MessageHandler handler);

    // Processes connection and determines which server handles this request
    void handleIncomingConnection(Connection* connection);

    void receiveLoop(MessageHandler handler)
    {
        // receive loop is run for each connection handled by handler
    }
};

} // namespace OpenMX