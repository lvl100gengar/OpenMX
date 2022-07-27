class ChatServerSettings {
private:
public:
    int maxConnections() const;
    int maxConnectionsPerAddress() const;
    
    std::vector<std::string> blockedNames() const;
    std::vector<std::string> blockedWords() const;
    std::vector<std::string> bannedNames() const;
    std::vector<uint32_t> bannedAddresses() const;

    bool containedBlockedName(const std::string& name) const;
    bool containedBlockedWord(const std::string& word) const;
    bool isBanned(const std::string& name) const;
    bool isBanned(uint32_t address) const;

    std::string messageFormat(const std::string& formatName) const;

    bool fancyEntry() const;
    bool fancyExit() const;
};