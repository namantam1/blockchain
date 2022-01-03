#ifndef __BLOCKCHAIN_H__
#define __BLOCKCHAIN_H__

#ifdef __cplusplus
extern "C"
{
#endif // __cpluscplus

#include "sha256.h"
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_DATA_SIZE 1024
#define MAX_CHAIN_SIZE 100

    typedef struct
    {
        BYTE data[MAX_DATA_SIZE];
        size_t data_len;
        BYTE hash[SHA256_BLOCK_SIZE];
        BYTE previousHash[SHA256_BLOCK_SIZE];
        time_t timestamp;
        uint32_t pow;
    } Block;

    typedef struct
    {
        Block chain[MAX_CHAIN_SIZE];
        size_t difficulty;
        size_t len;
    } BlockChain;

    /**
     * Create a new block chain
     * 
     * @param difficulty Difficulty of hash to generate for each block
     * @param init_data Initial data string. (NULLABLE)
     * @return BlockChain struct
    */
    BlockChain createBlockChain(size_t difficulty, char* init_data);

    /**
     * Add a new block with given data to block chain
     * 
     * @param blockChain Pointer to blockChain
     * @param data Data string to be used to add a block
    */
    void addBlock(BlockChain *blockChain, char *data);

    /**
     * Verify if blockchain created is valid by verifying hash generated
     * 
     * @param blockChain Pointer to blockchain
     * @return (Bool)
    */
    bool verifyBlockChain(BlockChain *blockChain);

    /**
     * Create a new block using previous hash and data string passed
     * 
     * @param difficulty Difficulty of hash
     * @param previous_hash Hash of prevoius block. Pass NULL if first block
     * @param data Data string to create block (NULLABLE)
     * @return Block struct
    */
    Block createBlock(size_t difficulty, BYTE *previous_hash, char *data);

    /**
     * Generate hash for the passed block
     * 
     * @param block Pointer to block
     * @param hash Mutable hash with 32 bit size allocated
    */
    void calculateHash(const Block *block, BYTE hash[]);

    /**
     * Mine a block with given difficulty to generate a valid hash
     * 
     * @param block Pointer to block
     * @param difficulty Difficulty of hash generated
    */
    void mine(Block *block, int difficulty);

    /**
     * Print a 32-bit has in hex
     * 
     * @param hash Hash to be printed
    */
    void print_hash(BYTE hash[]);

    /**
     * Print a block
     * 
     * @param block Pointer to block
    */
    void print_block(Block *block);

#ifdef __cplusplus
}
#endif // __cpluscplus
#endif // __BLOCKCHAIN_H__
