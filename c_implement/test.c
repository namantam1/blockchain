#include <stdio.h>
#include <string.h>

typedef struct {
    int tag;
} Block;

typedef struct {
    Block chain[100];
    int len;
} BlockChain;

void addBlock(BlockChain* blockChain) {
    Block block;
    block.tag = 10 + blockChain->len;
    blockChain->chain[blockChain->len++] = block;
    // memcpy(&blockChain->chain[blockChain->len++], &block, sizeof(Block));
}

int main() {
    BlockChain blockChain;
    blockChain.len = 0;
    for (int i=0; i<1000; i++) {
        addBlock(&blockChain);
        printf("chain size: %d\n", blockChain.len);
        printf("block tag: %d\n", blockChain.chain[i].tag);
    }
    return 0;
}