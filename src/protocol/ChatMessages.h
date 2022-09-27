#pragma once

#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"
#include "Message.h"
#include "RoomName.h"
#include "User.h"
#include "WpnTypes.h"
#include <cstdint>
#include <sstream>
#include <string>

namespace OpenMX::Chat {

struct ClientLogin : public Message {
    constexpr static wpn_short_t type = 100;
    RoomName room;
    User user;
    ClientLogin(RoomName& r, User& u) : room(r), user(u) {
        
    }
    ClientLogin(BinaryReader& reader)
    {
        room.fromBytes(reader);
        user.fromBytesLoginOrder(reader);
    }
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, room.name().size() + user.name().size() + 14);
        room.toBytes(writer);
        user.toBytesLoginOrder(writer);
    }
    void describe(std::ostringstream& ss) const
    {
        ss << "[Login/" << type << " " << room.describe() << " " << user.describe() << "]";
    }
};

struct Rename : public Message {
    constexpr static wpn_short_t type = 101;
    User user;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, user.name().size() + 13);
        user.toBytesLoginOrder(writer);
    }
    void decode(BinaryReader& reader)
    {
        user.fromBytesLoginOrder(reader);
    }
    void describe(std::ostringstream& ss) const
    {
        ss << "[Rename/" << type << " " << user.describe() << "]";
    }
};

struct LoginReply : public Message {
    constexpr static wpn_short_t type = 102;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, 0);
    }
    void decode(BinaryReader& reader)
    {
    }
    void describe(std::ostringstream& ss) const
    {
        ss << "[LoginReply/" << type << "]";
    }
};

struct Server353Support : public Message {
    constexpr static wpn_short_t type = 104;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, 0);
    }
    void decode(BinaryReader& reader)
    {
    }
    void describe(std::ostringstream& ss) const
    {
        ss << "[Server353Support/" << type << "]";
    }
};

struct UserJoin : public Message {
    constexpr static wpn_short_t type = 110;
    User user;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, user.name().size() + 13);
        user.toBytesListOrder(writer, false);
    }
    void decode(BinaryReader& reader)
    {
        user.fromBytesListOrder(reader, false);
    }
    void describe(std::ostringstream& ss) const
    {
        ss << "[UserJoin/" << type << " " << user.describe() << "]";
    }
};

struct UserList : public Message {
    constexpr static wpn_short_t type = 111;
    User user;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, user.name().size() + 13);
        user.toBytesListOrder(writer, false);
    }
    void decode(BinaryReader& reader)
    {
        user.fromBytesListOrder(reader, false);
    }
    void describe(std::ostringstream& ss) const
    {
        ss << "[UserJoin/" << type << " " << user.describe() << "]";
    }
};

struct UserRename : public Message {
    constexpr static wpn_short_t type = 112;
    Username currentInfo;
    User newInfo;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, currentInfo.name().size() + newInfo.name().size() + 20);
        currentInfo.toBytes(writer);
        newInfo.toBytesListOrder(writer, false);
    }
    void decode(BinaryReader& reader)
    {
        currentInfo.fromBytes(reader);
        newInfo.fromBytesListOrder(reader, false);
    }
    void describe(std::ostringstream& ss) const
    {
        // ss << "[UserRename/" << type << " current=" << currentInfo << " new=" << newInfo << "]";
    }
};

struct UserJoinRanked : public Message {
    constexpr static wpn_short_t type = 113;
    User user;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, user.name().size() + 14);
        user.toBytesListOrder(writer, true);
    }
    void decode(BinaryReader& reader)
    {
        user.fromBytesListOrder(reader, true);
    }
    void describe(std::ostringstream& ss) const
    {
        ss << "[UserJoinRanked/" << type << " " << user.describe() << "]";
    }
};

struct UserListRanked : public Message {
    constexpr static wpn_short_t type = 114;
    User user;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, user.name().size() + 14);
        user.toBytesListOrder(writer, true);
    }
    void decode(BinaryReader& reader)
    {
        user.fromBytesListOrder(reader, true);
    }
    void describe(std::ostringstream& ss) const
    {
        ss << "[UserListRanked/" << type << " " << user.describe() << "]";
    }
};

struct UserPart : public Message {
    constexpr static wpn_short_t type = 115;
    Username user;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, user.name().size() + 7);
        user.toBytes(writer);
    }
    void decode(BinaryReader& reader)
    {
        user.fromBytes(reader);
    }
    void describe(std::ostringstream& ss) const
    {
        //ss << "[UserPart/" << type << " " << user.describe() << "]";
    }
};

struct UserRenameRanked : public Message {
    constexpr static wpn_short_t type = 116;
    Username currentInfo;
    User newInfo;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, currentInfo.name().size() + newInfo.name().size() + 20);
        currentInfo.toBytes(writer);
        newInfo.toBytesListOrder(writer, true);
    }
    void decode(BinaryReader& reader)
    {
        currentInfo.fromBytes(reader);
        newInfo.fromBytesListOrder(reader, true);
    }
    void describe(std::ostringstream& ss) const
    {
        // ss << "[UserRenameRanked/" << type << " current=" << currentInfo << " new=" << newInfo << "]";
    }
};

struct UserJoinRankedIp : public Message {
    constexpr static wpn_short_t type = 117;
    User user;
    wpn_int_t ip;
    void encode(BinaryWriter& writer) const
    {
        secondaryHeader(writer, type, user.name().size() + 14);
        user.toBytesListOrder(writer, true);
        writer.writeInt(ip);
    }
    void decode(BinaryReader& reader)
    {
        user.fromBytesListOrder(reader, true);
        ip = reader.readInt();
    }
    void describe(std::ostringstream& ss) const
    {
        ss << "[UserJoinRankedIp/" << type << " " << user.describe() << "]";
    }
};
struct DailyMessage : public Message {
    constexpr static wpn_short_t type = 120;
    std::string text;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        text = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[DailyMessage/" << type << " text=" << text << "]";
        return ss.str();
    }
};
struct ClientText : public Message {
    constexpr static wpn_short_t type = 200;
    std::string text;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        text = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[ClientText/" << type << " text=" << text << "]";
        return ss.str();
    }
};
struct ServerText : public Message {
    constexpr static wpn_short_t type = 201;
    std::string userName;
    std::string text;
    wpn_byte_t rank;
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
        userName = reader.readString();
        text = reader.readString();
        rank = reader.readByte();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[ServerText/" << type << " userName=" << userName << " text=" << text << " rank=" << rank << "]";
        return ss.str();
    }
};
struct ClientAction : public Message {
    constexpr static wpn_short_t type = 202;
    std::string text;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        text = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[ClientAction/" << type << " text=" << text << "]";
        return ss.str();
    }
};
struct ServerAction : public Message {
    constexpr static wpn_short_t type = 203;
    std::string userName;
    std::string text;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + text.size() + 2);
        writer.writeString(userName, true);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        userName = reader.readString();
        text = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[ServerAction/" << type << " userName=" << userName << " text=" << text << "]";
        return ss.str();
    }
};
struct ServerColorText : public Message {
    constexpr static wpn_short_t type = 210;
    std::string text;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        text = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[ServerColorText/" << type << " text=" << text << "]";
        return ss.str();
    }
};
struct CommandEcho : public Message {
    constexpr static wpn_short_t type = 211;
    std::string text;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        text = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[CommandEcho/" << type << " text=" << text << "]";
        return ss.str();
    }
};
struct Topic : public Message {
    constexpr static wpn_short_t type = 300;
    std::string text;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        text = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[Topic/" << type << " text=" << text << "]";
        return ss.str();
    }
};
struct ServerRename : public Message {
    constexpr static wpn_short_t type = 301;
    std::string roomName;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(roomName.size() + 1);
        writer.writeString(roomName, true);
    }
    void decode(BinaryReader& reader)
    {
        roomName = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[ServerRename/" << type << " roomName=" << roomName << "]";
        return ss.str();
    }
};
struct ServerRedirect : public Message {
    constexpr static wpn_short_t type = 400;
    std::string roomName;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(roomName.size() + 1);
        writer.writeString(roomName, true);
    }
    void decode(BinaryReader& reader)
    {
        roomName = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[ServerRedirect/" << type << " roomName=" << roomName << "]";
        return ss.str();
    }
};
struct Client353Support : public Message {
    constexpr static wpn_short_t type = 5101;
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
        std::ostringstream ss;
        ss << "[Client353Support/" << type << " 49=" << 49 << "]";
        return ss.str();
    }
};
struct ClientRedirect : public Message {
    constexpr static wpn_short_t type = 5102;
    std::string roomName;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(roomName.size() + 1);
        writer.writeString(roomName, true);
    }
    void decode(BinaryReader& reader)
    {
        roomName = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[ClientRedirect/" << type << " roomName=" << roomName << "]";
        return ss.str();
    }
};
struct ClientColorText : public Message {
    constexpr static wpn_short_t type = 5200;
    std::string text;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(text.size() + 1);
        writer.writeString(text, true);
    }
    void decode(BinaryReader& reader)
    {
        text = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[ClientColorText/" << type << " text=" << text << "]";
        return ss.str();
    }
};
struct KeepAlive : public Message {
    constexpr static wpn_short_t type = 65000;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(2);
        writer.writeShort(65000);
    }
    void decode(BinaryReader& reader)
    {
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[KeepAlive/" << type << " 65000=" << 65000 << "]";
        return ss.str();
    }
};
struct RobomxChannel : public Message {
    constexpr static wpn_short_t type = 105;
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
        std::ostringstream ss;
        ss << "[Channel/" << type << "]";
        return ss.str();
    }
};
struct WcsServerIpSendSupport : public Message {
    constexpr static wpn_short_t type = 39168;
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
        std::ostringstream ss;
        ss << "[ServerIpSendSupport/" << type << "]";
        return ss.str();
    }
};
struct WcsClientIpSendSupport : public Message {
    constexpr static wpn_short_t type = 39169;
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
        std::ostringstream ss;
        ss << "[ClientIpSendSupport/" << type << "]";
        return ss.str();
    }
};
struct WcsIpSendEntry : public Message {
    constexpr static wpn_short_t type = 39170;
    std::string userName;
    wpn_int_t parentIp;
    wpn_short_t parentUdp;
    wpn_short_t sharedFiles;
    wpn_short_t lineType;
    wpn_byte_t rank;
    std::string ip;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(userName.size() + ip.size() + 13);
        writer.writeString(userName, true);
        writer.writeInt(parentIp);
        writer.writeShort(parentUdp);
        writer.writeShort(sharedFiles);
        writer.writeShort(lineType);
        writer.writeByte(rank);
        writer.writeString(ip, true);
    }
    void decode(BinaryReader& reader)
    {
        userName = reader.readString();
        parentIp = reader.readInt();
        parentUdp = reader.readShort();
        sharedFiles = reader.readShort();
        lineType = reader.readShort();
        rank = reader.readByte();
        ip = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[IpSendEntry/" << type << " userName=" << userName << " parentIp=" << parentIp << " parentUdp=" << parentUdp << " sharedFiles=" << sharedFiles << " lineType=" << lineType << " rank=" << rank << " ip=" << ip << "]";
        return ss.str();
    }
};
struct WcsIpSendComplete : public Message {
    constexpr static wpn_short_t type = 39171;
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
        std::ostringstream ss;
        ss << "[IpSendComplete/" << type << "]";
        return ss.str();
    }
};
struct WcsColorFormat : public Message {
    constexpr static wpn_short_t type = 39172;
    std::string format;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(format.size() + 1);
        writer.writeString(format, true);
    }
    void decode(BinaryReader& reader)
    {
        format = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[ColorFormat/" << type << " format=" << format << "]";
        return ss.str();
    }
};
struct WcsSoftwareName : public Message {
    constexpr static wpn_short_t type = 39173;
    std::string name;
    std::string version;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(name.size() + version.size() + 2);
        writer.writeString(name, true);
        writer.writeString(version, true);
    }
    void decode(BinaryReader& reader)
    {
        name = reader.readString();
        version = reader.readString();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[SoftwareName/" << type << " name=" << name << " version=" << version << "]";
        return ss.str();
    }
};
struct WcsFlood : public Message {
    constexpr static wpn_short_t type = 39174;
    wpn_byte_t isStart;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(1);
        writer.writeByte(isStart);
    }
    void decode(BinaryReader& reader)
    {
        isStart = reader.readByte();
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[Flood/" << type << " isStart=" << isStart << "]";
        return ss.str();
    }
};
struct WcsMenu : public Message {
    constexpr static wpn_short_t type = 39175;
    wpn_byte_t mode;
    std::string title;
    wpn_short_t style;
    std::string command;
    void encode(BinaryWriter& writer) const
    {
        writer.writeShort(type);
        writer.writeShort(title.size() + command.size() + 5);
        writer.writeByte(mode);
        if (mode != 0) {
            writer.writeString(title, true);
            if (mode != 1) {
                writer.writeShort(style);
                writer.writeString(command, true);
            }
        }
    }
    void decode(BinaryReader& reader)
    {
        mode = reader.readByte();
        if (mode != 0) {
            title = reader.readString();
            if (mode != 1) {
                style = reader.readShort();
                command = reader.readString();
            }
        }
    }
    std::string describe() const
    {
        std::ostringstream ss;
        ss << "[Menu/" << type << " mode=" << mode << " title=" << title << " style=" << style << " command=" << command << "]";
        return ss.str();
    }
};
}