#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "sha256.h"

#define DATA_MAX_SIZE 1024
#define MAX_CHAIN_SIZE 100
#define HASH_SIZE 32

typedef struct {
    char    name[255];
    char    email[255];
    double  amount;
} Data;

char *dataToString(Data *data) {
    char* data_str = malloc(sizeof(Data) + 1); 
    sprintf(data_str, "{\"name\":\"%s\", \"email\":\"%s\", \"amount\":\"%lf\"}", data->name, data->email, data->amount);
    return data_str;
}

typedef struct {
    char     data[DATA_MAX_SIZE];
    BYTE  hash[HASH_SIZE];
    BYTE  previousHash[HASH_SIZE];
    time_t   timestamp;
    uint32_t pow;
} Block;

typedef struct {
    Block genesisBlock;
    Block chain[MAX_CHAIN_SIZE];
    int   difficulty;
    int len;
} BlockChain;

void calculateHash(Block* block) {
    SHA256_CTX sha256;
    sha256_init(&sha256);

    sha256_update(&sha256, block->previousHash, HASH_SIZE);
    sha256_update(&sha256, (uint8_t *)block->data, strlen(block->data));

    char buffer[sizeof(time_t) * 8 + 1];
    int size = sprintf(buffer, "%ld", block->timestamp);
    sha256_update(&sha256, (uint8_t *)buffer, size);

    char pow_buffer[sizeof(int) * 8 + 1];
    size = sprintf(pow_buffer, "%d", block->pow);
    sha256_update(&sha256, (uint8_t *)pow_buffer, size);

    sha256_final(&sha256, block->hash);
}

static bool repeat(char* str, char c, int upto) {
    int i, MAX=1000;
    for (i=0; i<upto && str[i] != '\0' && i<MAX; i++ ){
        if (str[i] != c) return false;
    }
    return i == upto;
}

void mine(Block* block, int difficulty) {
    while (!repeat((char *)block->hash, '0', difficulty)) {
        block->pow++;
        calculateHash(block);
    }
}

BlockChain createBlockChain(int difficulty) {
    Block genesisBlock = {
        .hash={'\0'},
        .timestamp=time(NULL)
    };
    BlockChain blockChain = {
        .genesisBlock=genesisBlock,
        .chain={genesisBlock},
        .difficulty=difficulty,
        .len = 1
    };
    return blockChain;
}

void addBlockChain(BlockChain* blockChain, char data[]) {
    Block *latestBlock = &blockChain->chain[blockChain->len - 1];
    Block block;
    strcpy((char *)block.data, (char *)data);
    strcpy((char *)block.previousHash, (char *)latestBlock->hash);
    block.timestamp = time(NULL);
    block.pow = 0;
    mine(&block, blockChain->difficulty);
    // blockChain->chain[blockChain->len++] = block;
    memcpy(&blockChain->chain[blockChain->len++], &block, sizeof(Block));
}

void printDigest(BYTE *bytes) {
    for (int i=0; i<HASH_SIZE && bytes[i]; i++)
        printf("%x", bytes[i]);
    printf("\n");
}

void printBlock(Block* block) {
    printf("data: %s\n", block->data);
    printf("timestamp: %ld\n", block->timestamp);
    printf("pow: %d\n", block->pow);
    printf("pre hash: ");
    printDigest(block->previousHash);
    printf("hash: ");
    printDigest(block->hash);
    printf("--\n");
}

int main() {
    BlockChain blockChain = createBlockChain(2);
    printBlock(&blockChain.chain[0]);

    for (int i=1; i<5; i++) {
        addBlockChain(&blockChain, "my name is naman");
        // printf("%d\n", blockChain.len);
        printBlock(&blockChain.chain[i]);
    }

    // Block block = {
    //     .data = "\0",
    //     .pow = 11,
    //     .previousHash = "\0",
    //     .timestamp = 1000
    // };
    // // printf("%d\n", strlen(block.data));
    // calculateHash(&block);
    // for (int i=0; i<HASH_SIZE; i++) printf("%x", block.hash[i]);

    // printf("%d\n", repeat("", '0', 3));


    // Data data = {
    //     "Naman Tamrakar",
    //     "namantam1@gmail.com",
    //     100.0
    // };
    // char *str = dataToString(&data);
    // printf("data: %s\n", str);
    // free(str);
    // time_t seconds = time(NULL);
    // printf("%ld\n", seconds);

    // const unsigned char str[] = "NamanTamrakar";
    // SHA256_CTX foo;
    // uint8_t hash[SHA256_BLOCK_SIZE];
    // sha256_init(&foo);
    // sha256_update(&foo, (uint8_t *)"Naman", 5);
    // sha256_update(&foo, (uint8_t *)"tam", 3);
    // sha256_final(&foo, hash);
    // for (int i=0; i<32; i++) printf("%x", hash[i]);
    // printf("\n");

    // BlockChain blockChain = createBlockChain(3);
    // printf("%d\n", blockChain.difficulty);
    // printf("%x\n", &blockChain.genesisBlock.data);

    // time_t t = 2147483647;
    // char buffer[sizeof(time_t) * 8 + 1];
    // int r = sprintf(buffer, "%l", t);
    // printf("%s\n%d\n", buffer, r);
    
    // int pow = 1000;
    // char pow_buffer[sizeof(int) * 8 + 1];
    // char *c = itoa(pow, pow_buffer, 10);
    // printf("%s\n%s\n%d\n", pow_buffer, c, strlen(pow_buffer));

    
}
