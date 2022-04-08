#include "blockchain.h"
#include <stdio.h>

int main() {
    size_t len;
    printf("Enter number of blocks: ");
    scanf("%d", &len);

    BlockChain blockChain = createBlockChain(3, NULL);
    print_block(&blockChain.chain[0]);

    for (int i=1; i<len; i++) {
        addBlock(&blockChain, "some data");
        print_block(&blockChain.chain[i]);
    }

    printf("isValid: %d\n", verifyBlockChain(&blockChain));
    return 0;
}
