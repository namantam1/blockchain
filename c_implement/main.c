#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "sha256.h"

#define MAX_DATA_SIZE 1024
#define MAX_CHAIN_SIZE 100
#define string_length(type) sizeof(type) * 8 + 1

typedef struct {
    BYTE data[MAX_DATA_SIZE];
    size_t data_len;
    BYTE hash[SHA256_BLOCK_SIZE];
    BYTE previousHash[SHA256_BLOCK_SIZE];
    time_t timestamp;
    uint32_t pow;
} Block;

typedef struct {
    Block chain[MAX_CHAIN_SIZE];
    size_t difficulty;
    size_t len;
} BlockChain;

Block createBlock(BYTE *previous_hash, char *data);
void calculateHash(Block *block);
void mine(Block* block, int difficulty);
void print_hash(BYTE hash[]);
void print_block(Block* block);

BlockChain createBlockChain(size_t difficulty);
void addBlock(BlockChain* blockChain, char *data);

static bool repeat(const char* str, char c, int upto);
static size_t len(const char *str, int max);

int main() {
    BlockChain blockChain = createBlockChain(2);
    print_block(&blockChain.chain[0]);

    for (int i=1; i<25; i++) {
        addBlock(&blockChain, "some data");
        print_block(&blockChain.chain[i]);
    }
    return 0;
}

static size_t len(const char* str, int max) {
    size_t i=0;
    while(str && i<max && str[i++]);
    return i - 1;
}

BlockChain createBlockChain(size_t difficulty) {
    Block block = createBlock(NULL, NULL);
    mine(&block, 2);
    BlockChain blockChain = {
        .difficulty = difficulty,
        .len = 1
    };
    blockChain.chain[0] = block;
    return blockChain;
}

void addBlock(BlockChain* blockChain, char* data) {
    Block *prevBlock = &blockChain->chain[blockChain->len - 1];
    Block newBlock = createBlock(prevBlock->hash, data);
    mine(&newBlock, blockChain->difficulty);
    blockChain->chain[blockChain->len++] = newBlock;
}

void calculateHash(Block *block) {
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

    sha256_final(&ctx, block->hash);
}

static bool repeat(const char* str, char c, int upto) {
    int i, MAX=1000;
    for (i=0; i<upto && i<MAX; i++ ){
        if (str[i] != c) return false;
    }
    return i == upto;
}

void mine(Block* block, int difficulty) {
    calculateHash(block);
    while (!repeat((char *)block->hash, 0, difficulty)) {
        block->pow++;
        calculateHash(block);
    }
}

void print_hash(BYTE hash[]) {
    for (int i=0; i<SHA256_BLOCK_SIZE; i++) {
        printf("%x", hash[i]);
    }
    printf("\n");
}

Block createBlock(BYTE* previous_hash, char* data) {
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

    calculateHash(&block);
    return block;
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
