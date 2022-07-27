#pragma once

namespace OpenMX {

/**
 * @brief Named ID constants for the known generators.
 * 
 */
enum class BlockGeneratorId : char {
    Invalid,
    PrimaryClient = 80,
    PrimaryServer = 81,
    SecondaryClient = 82,
    SecondaryServer = 83,
    CacheServer = 84,
    ChatClient = 87,
    ChatServer = 88
};

/**
 * @brief Encrypts and decrypts chunks of data that are part of an overall stream of data.
 *
 */
class StreamEncryption {
private:
    char m_decryptKey[4];
    char m_encryptKey[4];

public:
    /**
     * @brief Decrypts the specified chunk of data.
     *
     * @param buffer pointer to the first byte to be decrypted
     * @param length number of bytes to be decrypted
     */
    void decrypt(char* buffer, size_t length);

    /**
     * @brief Encrypts the specified chunk of data.
     *
     * @param buffer pointer to the first byte to be encrypted
     * @param length number of bytes to be encrypted
     */
    void encrypt(char* buffer, size_t length);

    /**
     * @brief Called by client to parse keys received from server. Sets internal keys used by encrypt and decrypt functions.
     *
     * @param block pointer to a 16 byte key block
     * @param expectedId the generator id that is expected from the server
     * @return true if the block is valid and the generator id matches
     * @return false if the block is invalid or the id does not match
     */
    bool parseServerKeys(char* block, BlockGeneratorId expectedId); // called by client with server generated block, parse and stare

    /**
     * @brief Called by servers to generate a key block and keys. Sets internal keys used by encrypt and decrypt functions.
     *
     * @param block pointer to the location the 16 byte key block will be generated
     * @param generatorId the generator id to be used in key generation
     */
    void generateServerKeys(char* block, BlockGeneratorId generatorId); // called by server, builds block and stores keys
};

/**
 * @brief Decrypts a standalone block of data.
 * 
 * @param buffer pointer to the first byte of data
 * @param length number of bytes to encrypt
 */
void DecryptBlock(char* buffer, size_t length);

/**
 * @brief Encrypts a standalone block of data.
 * 
 * @param buffer pointer to the first byte of data
 * @param length number of bytes to decrypt
 */
void EncryptBlock(char* buffer, size_t length);

/**
 * @brief Processes exactly 132 bytes of ciphered input into 120 bytes of output data.
 * 
 * @param buffer pointer to the first byte of input data
 * @param output pointer to a buffer where the output will be stored
 */
void DecryptCache(char* input, char* output);

/**
 * @brief Modifies a key block using the patch mangle function.
 * 
 * @param block pointer to a 16 byte key block
 */
void MangleKeyBlock(char* block);

/**
 * @brief Generates a key block with the specified ID used in conjunction with stream encryption.
 * 
 * @param block pointer to memory where the block will be stored
 * @param id the ID of the local peer
 */
void GenerateKeyBlock(char* block, BlockGeneratorId id);

/**
 * @brief Gets the ID of the peer that generated the key block. Will try again with MangleKeyBlock if the initial result is Invalid.
 * 
 * @param block pointer to a 16 byte key block
 * @return the ID of the peer that generated the block or BlockGeneratorId::Invalid if the block is invalid
 */
BlockGeneratorId GetKeyBlockGenerator(char* block);

/**
 * @brief Gets the ID of the peer that generated the key block.
 * 
 * @param block pointer to a 16 byte key block
 * @return the ID of the peer that generated the block or BlockGeneratorId::Invalid if the block is invalid
 */
BlockGeneratorId GetKeyBlockGeneratorCore(char const* block);

/**
 * @brief Gets the keys and generator id from the key block.
 * 
 * @param block pointer to a 16 byte key block
 * @param up pointer to 4 bytes where the up key will be stored
 * @param down pointer to 4 bytes where the down key will be stored
 * @return the ID of the peer that generated the block or BlockGeneratorId::Invalid if the block is invalid
 */
BlockGeneratorId ParseKeyBlock(char* block, char* up, char* down);

} // namespace OpenMX