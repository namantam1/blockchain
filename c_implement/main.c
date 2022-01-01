#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "sha256.h"


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
    Data    data;
    char    hash[HASH_SIZE];
    char    previousHash[HASH_SIZE];
    time_t  timestamp;
    int     pow;
} Block;

typedef struct {
    Block genesisBlock;
    Block chain[MAX_CHAIN_SIZE];
    int difficulty;
} BlockChain;

BlockChain createBlockChain(int difficulty) {
    Block genesisBlock = {
        .hash="0",
        .timestamp=time(NULL)
    };
    BlockChain blockChain = {
        .genesisBlock=genesisBlock,
        .chain={genesisBlock},
        .difficulty=difficulty
    };
    return blockChain;
}

void calculateHash(Block block, char* hash) {
    char *str = dataToString(&block.data);
}

int main() {
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
    // sha256_update(&foo, str, 13);
    // sha256_final(&foo, hash);
    // for (int i=0; i<32; i++) printf("%x", hash[i]);
    // printf("\n");

    // BlockChain blockChain = createBlockChain(3);
    // printf("%d\n", blockChain.difficulty);
    // printf("%x\n", &blockChain.genesisBlock.data);
}
