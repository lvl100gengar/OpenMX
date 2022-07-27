#pragma once

#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"
#include "WpnTypes.h"
#include <cstdint>
#include <sstream>
#include <string>

namespace OpenMX {

#define STREAM_TYPE(typeName) \
    std::ostringstream ss;    \
    ss << "[" #typeName "" << typeName::type
#define STREAM_VAR(variable) << " " #variable "='" << variable << "'"
#define STREAM_END() \
    << ']';          \
    return ss.str();
#define MAKE_CONSTR(typeName) \
    typeName() = default;     \
    typeName(BinaryReader& reader) { decode(reader); }

struct Message {
    virtual void encode(BinaryWriter& writer) const = 0;
    virtual void decode(BinaryReader& reader) = 0;
    virtual std::string describe() const = 0;
};

/**
 * @brief Sent by a chat client upon connection to request entry to the server.
 * @details 100 [ChannelName:N][Speed:2][PriIp:4][PriPort:2][Files:4][UserName:N]
 */
struct ChatLogin : public Message {
    constexpr static wpn_short_t type = 100;

    std::string roomName;
    wpn_short_t lineType;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;
    wpn_int_t sharedFiles;
    std::string userName;

    MAKE_CONSTR(ChatLogin)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(roomName.size() + userName.size() + 14);
        writer.writeString(roomName, true);
        writer.writeShort(lineType);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
        writer.writeInt(sharedFiles);
        writer.writeString(userName, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        roomName = reader.readString();
        lineType = reader.readShort();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
        sharedFiles = reader.readInt();
        userName = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatLogin)
        STREAM_VAR(roomName)
        STREAM_VAR(lineType)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_VAR(sharedFiles)
        STREAM_VAR(userName)
        STREAM_END()
    }
};

/**
 * @brief Send by a chat client to update user information.
 * @details 101 [Speed:2][PriIp:4][PriPort:2][Files:4][UserName:N]
 */
struct ChatRename : public Message {
    constexpr static wpn_short_t type = 101;

    wpn_short_t lineType;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;
    wpn_int_t sharedFiles;
    std::string userName;

    MAKE_CONSTR(ChatRename)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + 13);
        writer.writeShort(lineType);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
        writer.writeInt(sharedFiles);
        writer.writeString(userName, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        lineType = reader.readShort();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
        sharedFiles = reader.readInt();
        userName = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatRename)
        STREAM_VAR(lineType)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_VAR(sharedFiles)
        STREAM_VAR(userName)
        STREAM_END()
    }
};

/**
 * @brief Chat server response to a Chatlogin message indicating sucessful entry.
 * @details 102 (This message has no payload)
 */
struct ChatLoginGranted : public Message {
    constexpr static wpn_short_t type = 102;

    MAKE_CONSTR(ChatLoginGranted)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(0);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatLoginGranted)
        STREAM_END()
    }
};

/**
 * @brief Sent by chat server when a new user has joined the server. The client typically prints a message informing the user in response to this message.
 * @details 110 [UserName:N][PriIp:4][PriPort:2][Speed:2][Files:4]
 */
struct ChatUserJoin : public Message {
    constexpr static wpn_short_t type = 110;

    std::string userName;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;
    wpn_short_t lineType;
    wpn_int_t sharedFiles;

    MAKE_CONSTR(ChatUserJoin)
    explicit ChatUserJoin(ClientData const& dataSource)
    {
        userName = dataSource.name;
        parentAddress = dataSource.parentAddress;
        parentUdpPort = dataSource.parentPort;
        lineType = dataSource.lineType;
        sharedFiles = dataSource.sharedFiles;
    }
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + 13);
        writer.writeString(userName, true);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
        writer.writeShort(lineType);
        writer.writeInt(sharedFiles);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        userName = reader.readString();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
        lineType = reader.readShort();
        sharedFiles = reader.readInt();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatUserJoin)
        STREAM_VAR(userName)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_VAR(lineType)
        STREAM_VAR(sharedFiles)
        STREAM_END()
    }
};

/**
 * @brief Sent by chat server to add a user to the client user list. Typically used to populate a new client's user list at join or with custom join messages.
 * @details 110 [UserName:N][PriIp:4][PriPort:2][Speed:2][Files:4]
 */
struct ChatUserList : public Message {
    constexpr static wpn_short_t type = 111;

    std::string userName;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;
    wpn_short_t lineType;
    wpn_int_t sharedFiles;

    MAKE_CONSTR(ChatUserList)
    explicit ChatUserList(ClientData const& dataSource)
    {
        userName = dataSource.name;
        parentAddress = dataSource.parentAddress;
        parentUdpPort = dataSource.parentPort;
        lineType = dataSource.lineType;
        sharedFiles = dataSource.sharedFiles;
    }
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + 13);
        writer.writeString(userName, true);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
        writer.writeShort(lineType);
        writer.writeInt(sharedFiles);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        userName = reader.readString();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
        lineType = reader.readShort();
        sharedFiles = reader.readInt();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatUserList)
        STREAM_VAR(userName)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_VAR(lineType)
        STREAM_VAR(sharedFiles)
        STREAM_END()
    }
};

/**
 * @brief Sent by chat server when a user's information changes.
 * @details 112 [OldUserName:N][OldPriIp:4][OldPriPort:2][UserName:N][PriIp:4][PriPort:2][Speed:2][Files:4]
 */
struct ChatUserRename : public Message {
    constexpr static wpn_short_t type = 112;

    std::string oldUserName;
    wpn_int_t oldParentAddress;
    wpn_short_t oldParentUdpPort;
    std::string userName;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;
    wpn_short_t lineType;
    wpn_int_t sharedFiles;

    MAKE_CONSTR(ChatUserRename)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(oldUserName.size() + userName.size() + 20);
        writer.writeString(oldUserName, true);
        writer.writeInt(oldParentAddress);
        writer.writeShort(oldParentUdpPort);
        writer.writeString(userName, true);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
        writer.writeShort(lineType);
        writer.writeInt(sharedFiles);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        oldUserName = reader.readString();
        oldParentAddress = reader.readInt();
        oldParentUdpPort = reader.readShort();
        userName = reader.readString();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
        lineType = reader.readShort();
        sharedFiles = reader.readInt();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatUserRename)
        STREAM_VAR(oldUserName)
        STREAM_VAR(oldParentAddress)
        STREAM_VAR(oldParentUdpPort)
        STREAM_VAR(userName)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_VAR(lineType)
        STREAM_VAR(sharedFiles)
        STREAM_END()
    }
};

/**
 * @brief Sent by chat server when a user leaves the server.
 * @details 115 [UserName:N][PriIp:4][PriPort:2]
 */
struct ChatUserPart : public Message {
    constexpr static wpn_short_t type = 115;

    std::string userName;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;

    MAKE_CONSTR(ChatUserPart)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + 7);
        writer.writeString(userName, true);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        userName = reader.readString();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatUserPart)
        STREAM_VAR(userName)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_END()
    }
};

/**
 * @brief A message sent to a chat client after joining the server.
 * @details 120 [Text:N]
 */
struct ChatDailyMessage : public Message {
    constexpr static wpn_short_t type = 120;

    std::string text;

    MAKE_CONSTR(ChatDailyMessage)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        text = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatDailyMessage)
        STREAM_VAR(text)
        STREAM_END()
    }
};

/**
 * @brief Text message sent by a client. Excludes action text and does not support color codes.
 * @details 200 [Text:N]
 */
struct ChatClientText : public Message {
    constexpr static wpn_short_t type = 200;

    std::string text;

    MAKE_CONSTR(ChatClientText)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        text = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatClientText)
        STREAM_VAR(text)
        STREAM_END()
    }
};

/**
 * @brief Action text message sent by a client. Does not support color codes.
 * @details 202 [Text:N]
 */
struct ChatClientAction : public Message {
    constexpr static wpn_short_t type = 202;

    std::string text;

    MAKE_CONSTR(ChatClientAction)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        text = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatClientAction)
        STREAM_VAR(text)
        STREAM_END()
    }
};

/**
 * @brief Text message broadcast sent by a server. Does not support color codes.
 * @details 201 [UserName:N][Text:N]{[Rank:1]}
 */
struct ChatServerText : public Message {
    constexpr static wpn_short_t type = 201;

    std::string userName;
    std::string text;
    wpn_byte_t rank;

    MAKE_CONSTR(ChatServerText)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + text.size() + 3);
        writer.writeString(userName, true);
        writer.writeString(text, true);
        writer.writeByte(rank);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        userName = reader.readString();
        text = reader.readString();

        if (reader.canRead(1))
            rank = reader.readByte();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatServerText)
        STREAM_VAR(userName)
        STREAM_VAR(text)
        STREAM_END()
    }
};

/**
 * @brief Action text message broadcast sent by a server. Does not support color codes.
 * @details 203 [UserName:N][Text:N]
 */
struct ChatServerAction : public Message {
    constexpr static wpn_short_t type = 203;

    std::string userName;
    std::string text;

    MAKE_CONSTR(ChatServerAction)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + text.size() + 2);
        writer.writeString(userName, true);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        userName = reader.readString();
        text = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatServerAction)
        STREAM_VAR(userName)
        STREAM_VAR(text)
        STREAM_END()
    }
};

/**
 * @brief Channel topic sent by server. Typically sent after join and when topic changes.
 * @details 300 [Text:N]
 */
struct ChatTopic : public Message {
    constexpr static wpn_short_t type = 300;

    std::string text;

    MAKE_CONSTR(ChatTopic)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        text = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatTopic)
        STREAM_VAR(text)
        STREAM_END()
    }
};

/**
 * @brief Sent periodically by clients and servers to ensure connection is still active. Includes dummy payload for compatibility with non-compliant 3rd party clients/servers.
 * @details 65000 (This message has no payload)
 */
struct ChatKeepAlive : public Message {
    constexpr static wpn_short_t type = 65000;

    MAKE_CONSTR(ChatKeepAlive)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(4);
        writer.writeInt(65000);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatKeepAlive)
        STREAM_END()
    }
};

// ###################################
// #                                 #
// #   WinMX version 3.53 messages   #
// #                                 #
// ###################################

/**
 * @brief Sent by clients to signal support for messages added in WinMX 3.53.
 * @details 5101 [49]
 */
struct ChatClient353Support : public Message {
    constexpr static wpn_short_t type = 5101;

    MAKE_CONSTR(ChatClient353Support)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(1);
        writer.writeByte(49);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatClient353Support)
        STREAM_END()
    }
};

/**
 * @brief Sent by servers to signal support for messages added in WinMX 3.53.
 * @details 104 (This message has no payload)
 */
struct ChatServer353Support : public Message {
    constexpr static wpn_short_t type = 104;

    MAKE_CONSTR(ChatServer353Support)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(0);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatServer353Support)
        STREAM_END()
    }
};

/**
 * @brief Sent by chat server when a new user has joined the server. The client typically prints a message informing the user in response to this message.
 * @details 113 [UserName:N][PriIp:4][PriPort:2][Speed:2][Files:4][Rank:1]
 */
struct ChatUserJoinRank : public Message {
    constexpr static wpn_short_t type = 113;

    std::string userName;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;
    wpn_short_t lineType;
    wpn_int_t sharedFiles;
    wpn_byte_t rank;

    MAKE_CONSTR(ChatUserJoinRank)
    explicit ChatUserJoinRank(ClientData const& dataSource)
    {
        userName = dataSource.name;
        parentAddress = dataSource.parentAddress;
        parentUdpPort = dataSource.parentPort;
        lineType = dataSource.lineType;
        sharedFiles = dataSource.sharedFiles;
        rank = dataSource.rank;
    }
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + 14);
        writer.writeString(userName, true);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
        writer.writeShort(lineType);
        writer.writeInt(sharedFiles);
        writer.writeByte(rank);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        userName = reader.readString();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
        lineType = reader.readShort();
        sharedFiles = reader.readInt();
        rank = reader.readByte();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatUserJoinRank)
        STREAM_VAR(userName)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_VAR(lineType)
        STREAM_VAR(sharedFiles)
        STREAM_VAR(rank)
        STREAM_END()
    }
};

/**
 * @brief Sent by chat server to populate the client's user list.
 * @details 114 [UserName:N][PriIp:4][PriPort:2][Speed:2][Files:4][Rank:1]
 */
struct ChatUserListRank : public Message {
    constexpr static wpn_short_t type = 114;

    std::string userName;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;
    wpn_short_t lineType;
    wpn_int_t sharedFiles;
    wpn_byte_t rank;

    MAKE_CONSTR(ChatUserListRank)
    explicit ChatUserListRank(ClientData const& dataSource)
    {
        userName = dataSource.name;
        parentAddress = dataSource.parentAddress;
        parentUdpPort = dataSource.parentPort;
        lineType = dataSource.lineType;
        sharedFiles = dataSource.sharedFiles;
        rank = dataSource.rank;
    }
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + 14);
        writer.writeString(userName, true);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
        writer.writeShort(lineType);
        writer.writeInt(sharedFiles);
        writer.writeByte(rank);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        userName = reader.readString();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
        lineType = reader.readShort();
        sharedFiles = reader.readInt();
        rank = reader.readByte();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatUserListRank)
        STREAM_VAR(userName)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_VAR(lineType)
        STREAM_VAR(sharedFiles)
        STREAM_VAR(rank)
        STREAM_END()
    }
};

/**
 * @brief Sent by chat server when a user's information changes.
 * @details 116 [OldUserName:N][OldPriIp:4][OldPriPort:2][UserName:N][PriIp:4][PriPort:2][Speed:2][Files:4][Rank:1]
 */
struct ChatUserRenameRank : public Message {
    constexpr static wpn_short_t type = 116;

    std::string oldUserName;
    wpn_int_t oldParentAddress;
    wpn_short_t oldParentUdpPort;
    std::string userName;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;
    wpn_short_t lineType;
    wpn_int_t sharedFiles;
    wpn_byte_t rank;

    MAKE_CONSTR(ChatUserRenameRank)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(oldUserName.size() + userName.size() + 21);
        writer.writeString(oldUserName, true);
        writer.writeInt(oldParentAddress);
        writer.writeShort(oldParentUdpPort);
        writer.writeString(userName, true);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
        writer.writeShort(lineType);
        writer.writeInt(sharedFiles);
        writer.writeByte(rank);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        oldUserName = reader.readString();
        oldParentAddress = reader.readInt();
        oldParentUdpPort = reader.readShort();
        userName = reader.readString();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
        lineType = reader.readShort();
        sharedFiles = reader.readInt();
        rank = reader.readByte();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatUserRenameRank)
        STREAM_VAR(oldUserName)
        STREAM_VAR(oldParentAddress)
        STREAM_VAR(oldParentUdpPort)
        STREAM_VAR(userName)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_VAR(lineType)
        STREAM_VAR(sharedFiles)
        STREAM_VAR(rank)
        STREAM_END()
    }
};

/**
 * @brief Sent by chat server when a new user has joined the server. The client typically prints a message informing the user in response to this message.
 * @details 117 [UserName:N][PriIp:4][PriPort:2][Speed:2][Files:4][Rank:1][IpAddress:4]
 */
struct ChatUserJoinRankIp : public Message {
    constexpr static wpn_short_t type = 117;

    std::string userName;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;
    wpn_short_t lineType;
    wpn_int_t sharedFiles;
    wpn_byte_t rank;
    wpn_int_t ipAddress;

    MAKE_CONSTR(ChatUserJoinRankIp)
    explicit ChatUserJoinRankIp(ClientData const& dataSource)
    {
        userName = dataSource.name;
        parentAddress = dataSource.parentAddress;
        parentUdpPort = dataSource.parentPort;
        lineType = dataSource.lineType;
        sharedFiles = dataSource.sharedFiles;
        rank = dataSource.rank;
        ipAddress = dataSource.endPoint.address();
    }
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + 25);
        writer.writeString(userName, true);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
        writer.writeShort(lineType);
        writer.writeInt(sharedFiles);
        writer.writeByte(rank);
        writer.writeInt(ipAddress);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        userName = reader.readString();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
        lineType = reader.readShort();
        sharedFiles = reader.readInt();
        rank = reader.readByte();
        ipAddress = reader.readInt();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatUserJoinRankIp)
        STREAM_VAR(userName)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_VAR(lineType)
        STREAM_VAR(sharedFiles)
        STREAM_VAR(rank)
        STREAM_VAR(ipAddress)
        STREAM_END()
    }
};

/**
 * @brief Color text sent by a chat server. Supports color byte codes.
 * @details 210 [Text:N]
 */
struct ChatServerColorText : public Message {
    constexpr static wpn_short_t type = 210;

    std::string text;

    MAKE_CONSTR(ChatServerColorText)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        text = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatServerColorText)
        STREAM_VAR(text)
        STREAM_END()
    }
};

/**
 * @brief Server echo of commands typed by user.
 * @details 211 [Text:N]
 */
struct ChatCommandEcho : public Message {
    constexpr static wpn_short_t type = 211;

    std::string text;

    MAKE_CONSTR(ChatCommandEcho)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        text = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatCommandEcho)
        STREAM_VAR(text)
        STREAM_END()
    }
};

/**
 * @brief Sent by a server when the name of the room changes.
 * @details 301 [Text:N]
 */
struct ChatServerRename : public Message {
    constexpr static wpn_short_t type = 301;

    std::string roomName;

    MAKE_CONSTR(ChatServerRename)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(roomName.size() + 1);
        writer.writeString(roomName, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        roomName = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatServerRename)
        STREAM_VAR(roomName)
        STREAM_END()
    }
};

/**
 * @brief Sent by a server when the room is being redirected to another server.
 * @details 400 [Text:N]
 */
struct ChatServerRedirect : public Message {
    constexpr static wpn_short_t type = 400;

    std::string roomName;

    MAKE_CONSTR(ChatServerRedirect)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(roomName.size() + 1);
        writer.writeString(roomName, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        roomName = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatServerRedirect)
        STREAM_VAR(roomName)
        STREAM_END()
    }
};

/**
 * @brief Sent by a client when it has been redirected from another server.
 * @details 5102 [Text:N]
 */
struct ChatClientRedirect : public Message {
    constexpr static wpn_short_t type = 5102;

    std::string roomName;

    MAKE_CONSTR(ChatClientRedirect)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(roomName.size() + 1);
        writer.writeString(roomName, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        roomName = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatClientRedirect)
        STREAM_VAR(roomName)
        STREAM_END()
    }
};

/**
 * @brief Color text sent by a chat client. Supports color byte codes.
 * @details 5200 [Text:N]
 */
struct ChatClientColorText : public Message {
    constexpr static wpn_short_t type = 5200;

    std::string text;

    MAKE_CONSTR(ChatClientColorText)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        text = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatClientColorText)
        STREAM_VAR(text)
        STREAM_END()
    }
};

// #######################################
// #                                     #
// #   RoboMX messages added by Bender   #
// #                                     #
// #######################################

/**
 * @brief Signals that the channel is hosted by RoboMX.
 * @details 105 (This type has no payload)
 */
struct RobomxChannel : public Message {
    constexpr static wpn_short_t type = 105;

    MAKE_CONSTR(RobomxChannel)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(0);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(RobomxChannel)
        STREAM_END()
    }
};

// ########################################
// #                                      #
// #   WCS messages added by KM/MXTools   #
// #                                      #
// ########################################

/**
 * @brief Signals that the server supports IPSend.
 * @details 39168 (This type has no payload)
 */
struct WcsServerIpSendSupport : public Message {
    constexpr static wpn_short_t type = 39168;

    MAKE_CONSTR(WcsServerIpSendSupport)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(0);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(WcsServerIpSendSupport)
        STREAM_END()
    }
};

/**
 * @brief Signals that the client supports IPSend.
 * @details 39169 (This type has no payload)
 */
struct WcsClientIpSendSupport : public Message {
    constexpr static wpn_short_t type = 39169;

    MAKE_CONSTR(WcsClientIpSendSupport)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(0);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(WcsClientIpSendSupport)
        STREAM_END()
    }
};

/**
 * @brief Sent by chat server to populate the client's user list.
 * @details 39170 [UserName:N][PriIp:4][PriPort:2][Files:2][Speed:2][Rank:1][Ip:N]
 */
struct WcsIpSendEntry : public Message {
    constexpr static wpn_short_t type = 39170;

    std::string userName;
    wpn_int_t parentAddress;
    wpn_short_t parentUdpPort;
    wpn_int_t sharedFiles;
    wpn_short_t lineType;
    wpn_byte_t rank;
    std::string ipAddress;

    MAKE_CONSTR(WcsIpSendEntry)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + ipAddress.size() + 15);
        writer.writeString(userName, true);
        writer.writeInt(parentAddress);
        writer.writeShort(parentUdpPort);
        writer.writeShort(lineType);
        writer.writeInt(sharedFiles);
        writer.writeByte(rank);
        writer.writeString(ipAddress, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        userName = reader.readString();
        parentAddress = reader.readInt();
        parentUdpPort = reader.readShort();
        sharedFiles = reader.readInt();
        lineType = reader.readShort();
        rank = reader.readByte();
        ipAddress = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(ChatUserListRank)
        STREAM_VAR(userName)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentUdpPort)
        STREAM_VAR(sharedFiles)
        STREAM_VAR(lineType)
        STREAM_VAR(rank)
        STREAM_VAR(ipAddress)
        STREAM_END()
    }
};

/**
 * @brief Signals that all IPSend entries have been transmitted to the client.
 * @details 39171 (This type has no payload)
 */
struct WcsIpSendComplete : public Message {
    constexpr static wpn_short_t type = 39171;

    MAKE_CONSTR(WcsIpSendComplete)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(0);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(WcsIpSendComplete)
        STREAM_END()
    }
};

/**
 * @brief Sets the color code format used by the server.
 * @details 39172 [Format:N]
 */
struct WcsColorFormat : public Message {
    constexpr static wpn_short_t type = 39172;

    std::string format;

    MAKE_CONSTR(WcsColorFormat)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(format.size() + 1);
        writer.writeString(format, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        format = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(WcsColorFormat)
        STREAM_VAR(format)
        STREAM_END()
    }
};

/**
 * @brief The name and version of the software used by the remote peer.
 * @details 39173 [Name:N][Version:N]
 */
struct WcsSoftwareName : public Message {
    constexpr static wpn_short_t type = 39173;

    std::string name;
    std::string version;

    MAKE_CONSTR(WcsSoftwareName)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(name.size() + version.size() + 1);
        writer.writeString(name, true);
        writer.writeString(version, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        name = reader.readString();
        version = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(WcsSoftwareName)
        STREAM_VAR(name)
        STREAM_VAR(version)
        STREAM_END()
    }
};

/**
 * @brief Sent by server to signal the start and end of a large block of text.
 * @details 39174 [StartOrEnd:1]
 */
struct WcsFlood : public Message {
    constexpr static wpn_short_t type = 39174;

    wpn_byte_t isStart;

    MAKE_CONSTR(WcsFlood)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(1);
        writer.writeByte(isStart);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        isStart = reader.readByte();
    }
    std::string describe() const
    {
        STREAM_TYPE(WcsFlood)
        STREAM_VAR(isStart)
        STREAM_END()
    }
};

enum WcsMenuMode : wpn_byte_t {
    WcsMenuModeSupport = 0,
    WcsMenuModeUser = 1,
    WcsMenuModeChannel = 2,
    WcsMenuModeScroll = 3
};

enum WcsMenuStyle : wpn_short_t {
    WcsMenuStyleDisabled = 1,
    WcsMenuStyleDisabledNotGray = 2,
    WcsMenuStyleChecked = 8,
    WcsMenuStyleNewColumn = 32,
    WcsMenuStyleNewColumnNoLine = 64,
    WcsMenuStyleSeperator = 2048
};

/**
 * @brief Sent by server to signal the start and end of a large block of text.
 * @details 39175 [Type:1][Title:N][MenuType:2][Command:N]
 */
struct WcsMenu : public Message {
    constexpr static wpn_short_t type = 39175;

    wpn_byte_t mode;
    std::string title;
    wpn_short_t style;
    std::string command;

    MAKE_CONSTR(WcsMenu)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);

        switch (mode) {
        case WcsMenuModeSupport: {
            // Mode only
            writer.writeShort(1);
            writer.writeByte(mode);
            break;
        }
        case WcsMenuModeScroll: {
            // Mode and title
            writer.writeShort(title.size() + 2);
            writer.writeByte(mode);
            writer.writeString(title, true);
            break;
        }
        default: {
            // All fields
            writer.writeShort(title.size() + command.size() + 5);
            writer.writeByte(mode);
            writer.writeString(title, true);
            writer.writeShort(style);
            writer.writeString(command, true);
            break;
        }
        }
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);

        switch (reader.readByte()) {
        case WcsMenuModeScroll: {
            // Only contains a title
            title = reader.readString();
            break;
        }
        case WcsMenuModeChannel:
        case WcsMenuModeUser: {
            // Contains all fields
            title = reader.readString();
            style = reader.readShort();
            command = reader.readString();
            break;
        }
        }
    }
    std::string describe() const
    {
        STREAM_TYPE(WcsMenu)
        STREAM_VAR(mode)
        STREAM_VAR(title)
        STREAM_VAR(style)
        STREAM_VAR(command)
        STREAM_END()
    }
};

// ###################################################
// #                                                 #
// #   EServ/Wpcc messages added by Eagle/Emulator   #
// #                                                 #
// ###################################################

/**
 * @brief Signals server support for Eserv/WPCC chat extensions.
 * @details 0x3400 [00:1]
 */
struct WpccServerSupport : public Message {
    constexpr static wpn_short_t type = 0x3400;

    MAKE_CONSTR(WpccServerSupport)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(1);
        writer.writeShort(0);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(WpccServerSupport)
        STREAM_END()
    }
};

/**
 * @brief Signals client support for Eserv/WPCC chat extensions.
 * @details 0x3470 [00:1]
 */
struct WpccClientSupport : public Message {
    constexpr static wpn_short_t type = 0x3470;

    MAKE_CONSTR(WpccClientSupport)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(1);
        writer.writeShort(0);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(WpccClientSupport)
        STREAM_END()
    }
};

/**
 * @brief Sent by a server when a client is currently typing a message.
 * @details 0x3401 [PrimaryIP:4][PrimaryPort:2][Nick:S]
 */
struct WpccServerTypingBegin : public Message {
    constexpr static wpn_short_t type = 0x3401;

    wpn_int_t parentAddress;
    wpn_short_t parentPort;
    std::string userName;

    MAKE_CONSTR(WpccServerTypingBegin)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + 7);
        writer.writeInt(parentAddress);
        writer.writeShort(parentPort);
        writer.writeString(userName, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        parentAddress = reader.readInt();
        parentPort = reader.readShort();
        userName = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(WpccServerTypingBegin)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentPort)
        STREAM_VAR(userName)
        STREAM_END()
    }
};

/**
 * @brief Sent by a server when a client is stops typing a message.
 * @details 0x3402 [PrimaryIP:4][PrimaryPort:2][Nick:S]
 */
struct WpccServerTypingEnd : public Message {
    constexpr static wpn_short_t type = 0x3402;

    wpn_int_t parentAddress;
    wpn_short_t parentPort;
    std::string userName;

    MAKE_CONSTR(WpccServerTypingEnd)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + 7);
        writer.writeInt(parentAddress);
        writer.writeShort(parentPort);
        writer.writeString(userName, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        parentAddress = reader.readInt();
        parentPort = reader.readShort();
        userName = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(WpccServerTypingEnd)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentPort)
        STREAM_VAR(userName)
        STREAM_END()
    }
};

/**
 * @brief Sent by a client when the user is typing a message.
 * @details 0x3471 [00:1]
 */
struct WpccClientTypingBegin : public Message {
    constexpr static wpn_short_t type = 0x3471;

    MAKE_CONSTR(WpccClientTypingBegin)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(1);
        writer.writeShort(0);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(WpccClientTypingBegin)
        STREAM_END()
    }
};

/**
 * @brief Sent by a client when the user stops typing a message.
 * @details 0x3472 [00:1]
 */
struct WpccClientTypingEnd : public Message {
    constexpr static wpn_short_t type = 0x3472;

    MAKE_CONSTR(WpccClientTypingEnd)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(1);
        writer.writeShort(0);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        STREAM_TYPE(WpccClientTypingEnd)
        STREAM_END()
    }
};

enum WpccStatus {
    Online = 0,
    Busy = 1,
    BeRightBack = 2,
    Away = 3,
    OnPhone = 4,
    AtLunch = 5,
    AtDinner = 6
};

/**
 * @brief Sent by a server when the status of a user changes.
 * @details 0x3411 [Status:2][PrimaryIP:4][PrimaryPort:2][Nick:S]
 */
struct WpccServerStatus : public Message {
    constexpr static wpn_short_t type = 0x3411;

    wpn_short_t status;
    wpn_int_t parentAddress;
    wpn_short_t parentPort;
    std::string userName;

    MAKE_CONSTR(WpccServerStatus)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + 9);
        writer.writeShort(status);
        writer.writeInt(parentAddress);
        writer.writeShort(parentPort);
        writer.writeString(userName, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        status = reader.readShort();
        parentAddress = reader.readInt();
        parentPort = reader.readShort();
        userName = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(WpccServerStatus)
        STREAM_VAR(status)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentPort)
        STREAM_VAR(userName)
        STREAM_END()
    }
};

/**
 * @brief Sent by a client when it's status changes.
 * @details 0x3472 [Status:2]
 */
struct WpccClientStatus : public Message {
    constexpr static wpn_short_t type = 0x3472;

    wpn_short_t status;

    MAKE_CONSTR(WpccClientStatus)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(2);
        writer.writeShort(status);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        status = reader.readShort();
    }
    std::string describe() const
    {
        STREAM_TYPE(WpccClientStatus)
        STREAM_VAR(status)
        STREAM_END()
    }
};

/**
 * @brief Sent by a server when the bio text of a user changes.
 * @details 0x3421 [PrimaryIP:4][PrimaryPort:2][Nick:S][PersonalMessage:N]
 */
struct WpccServerBio : public Message {
    constexpr static wpn_short_t type = 0x3421;

    wpn_int_t parentAddress;
    wpn_short_t parentPort;
    std::string userName;
    std::string bio;

    MAKE_CONSTR(WpccServerBio)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + bio.size() + 8);
        writer.writeInt(parentAddress);
        writer.writeShort(parentPort);
        writer.writeString(userName, true);
        writer.writeString(bio, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        parentAddress = reader.readInt();
        parentPort = reader.readShort();
        userName = reader.readString();
        bio = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(WpccServerBio)
        STREAM_VAR(parentAddress)
        STREAM_VAR(parentPort)
        STREAM_VAR(userName)
        STREAM_VAR(bio)
        STREAM_END()
    }
};

/**
 * @brief Sent by a client when it's bio text changes.
 * @details 0x3491 [PrimaryIP:4][PrimaryPort:2][Nick:S][PersonalMessage:N]
 */
struct WpccClientBio : public Message {
    constexpr static wpn_short_t type = 0x3491;

    std::string bio;

    MAKE_CONSTR(WpccClientBio)
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(bio.size() + 1);
        writer.writeString(bio, true);
    }
    void decode(BinaryReader& reader)
    {
        reader.skip(4);
        bio = reader.readString();
    }
    std::string describe() const
    {
        STREAM_TYPE(WpccClientBio)
        STREAM_VAR(bio)
        STREAM_END()
    }
};

} // namespace OpenMX::protocol