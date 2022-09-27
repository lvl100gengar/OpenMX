#include "ChatClientHandler.h"

#include "ChatMessages.h"

#include <iostream>

namespace OpenMX {

    
    // ChatClientHandler::ChatClientHandler() {}

    void ChatClientHandler::onServerMessage(BinaryReader message) {
        wpn_short_t type = message.readShort();
        wpn_short_t length = message.readShort();

        std::cout << "Message from server: type=" << type << " len=" << length << "\n";

        switch (type)
        {
        case Chat::LoginReply::type:
            std::cout << "Login successful!\n";
            break;
        default:
            break;
        }
    }

    void ChatClientHandler::onServerConnect() {
        std::cout << "Connected to server.\n";

        // auto login = new Chat::ClientLogin();
        auto room = RoomName("Pandora_0100007F1A2B");
        auto user = User("Sean117_00000", 0, 0, 7, 1234);
        sendQueue.push_back(std::make_unique<Chat::ClientLogin>(room, user));
    }

    void ChatClientHandler::onServerDisconnect() {
        std::cout << "Disconnected from server.\n";
    }

    void tick(){

    }


} // namespace OpenMX