#include "sha256.h"
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_DATA_SIZE 1024
#define MAX_CHAIN_SIZE 100

#define string_length(type) ((sizeof(type) / 2) * 3 + sizeof(type)) + 2

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

static size_t len(const char* str, int max) {
    size_t i=0;
    while(str && i<max && str[i++]);
    return i - 1;
}

static bool repeat(const char* str, char c, int upto) {
    int i, MAX=1000;
    for (i=0; i<upto && i<MAX; i++ ){
        if (str[i] != c) return false;
    }
    return i == upto;
}

static bool hashComp(BYTE *hash1, BYTE *hash2) {
    for (size_t i=0; i<SHA256_BLOCK_SIZE; i++){
        if (hash1[i] != hash2[i]) return false;
    }
    return true;
}

void calculateHash(const Block *block, BYTE *hash) {
    int size;
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, block->previousHash, SHA256_BLOCK_SIZE);
    sha256_update(&ctx, block->data, block->data_len);

    char timestamp_str[string_length(time_t)];
    size = sprintf(timestamp_str, "%ld", block->timestamp);
    sha256_update(&ctx, (BYTE *)timestamp_str, size);

    char pow_str[string_length(int)];
    size = sprintf(pow_str, "%d", block->pow);
    sha256_update(&ctx, (BYTE *)pow_str, size);

    sha256_final(&ctx, hash);
}

void mine(Block* block, int difficulty) {
    calculateHash(block, block->hash);
    while (!repeat((char *)block->hash, 0, difficulty)) {
        block->pow++;
        calculateHash(block, block->hash);
    }
}

Block createBlock(size_t difficulty, BYTE* previous_hash, char* data) {
    Block block = {
        .timestamp=time(NULL),
        .pow=0
    };
    if (previous_hash)
        memcpy(block.previousHash, previous_hash, SHA256_BLOCK_SIZE);
    if (data)
        memcpy(
            block.data, 
            (BYTE *)data, 
            block.data_len=len(data, MAX_DATA_SIZE)
        );
    mine(&block, difficulty);
    return block;
}


BlockChain createBlockChain(size_t difficulty, char *init_data) {
    Block block = createBlock(difficulty, NULL, init_data);
    BlockChain blockChain = {
        .difficulty = difficulty,
        .len = 1
    };
    blockChain.chain[0] = block;
    return blockChain;
}

void addBlock(BlockChain* blockChain, char* data) {
    Block *prevBlock = &blockChain->chain[blockChain->len - 1];
    Block newBlock = createBlock(blockChain->difficulty, prevBlock->hash, data);
    blockChain->chain[blockChain->len++] = newBlock;
}

bool verifyBlockChain(BlockChain *blockChain) {
    if (!blockChain || blockChain->len <= 0) {
        return false;
    }

    BYTE hash[SHA256_BLOCK_SIZE];
    calculateHash(&blockChain->chain[0], hash);
    if (!hashComp(hash, blockChain->chain[0].hash)) {
        return false;
    }

    for (size_t i=1; i<blockChain->len; i++) {
        if (!hashComp(blockChain->chain[i].previousHash, blockChain->chain[i - 1].hash)) {
            return false;
        }

        calculateHash(&blockChain->chain[i], hash);
        if (!hashComp(hash, blockChain->chain[i].hash)) {
            return false;
        }
    }

    return true;
}

void print_hash(BYTE hash[]) {
    for (int i=0; i<SHA256_BLOCK_SIZE; i++) {
        printf("%x", hash[i]);
    }
    printf("\n");
}

void print_block(Block* block) {
    printf("---\n");
    printf("pow: %d\n", block->pow);
    printf("timestamp: %ld\n", block->timestamp);
    printf("hash: ");
    print_hash(block->hash);
    printf("previousHash: ");
    print_hash(block->previousHash);
    printf("data: %s\n", block->data);
}

int main() {
    // Block block = createBlock(2, NULL, NULL);
    // print_block(&block);
    BlockChain blockChain = createBlockChain(2, NULL);
    print_block(&blockChain.chain[0]);

    for (int i=1; i<3; i++) {
        addBlock(&blockChain, "some data");
        print_block(&blockChain.chain[i]);
    }

    printf("Block Chain is %s", verifyBlockChain(&blockChain) ? "True" : "False");
}
