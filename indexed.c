
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_BLOCKS 100

struct IndexBlock {
    int data_blocks[MAX_BLOCKS];
};

void initializeIndexBlock(struct IndexBlock* indexBlock) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        indexBlock->data_blocks[i] = -1; 
    }
}

int allocateDataBlock(struct IndexBlock* indexBlock, int blockNumber) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (indexBlock->data_blocks[i] == -1) {
            indexBlock->data_blocks[i] = blockNumber;
            return 1; 
        }
    }
    return 0; 
}

void readData(struct IndexBlock* indexBlock, int fileBlockNumber) {
    int flag = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (indexBlock->data_blocks[i] != -1 && fileBlockNumber == indexBlock->data_blocks[i]) {
            printf("Reading data from block %d\n", indexBlock->data_blocks[i]);
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        printf("Block %d is not allocated.\n", fileBlockNumber);
}



void main()
{
    struct IndexBlock indexBlock;
    int n, blockNumber, choice;

    initializeIndexBlock(&indexBlock);

    
    printf("Enter number of blocks to allocate: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter block number to allocate (%d/%d): ", i + 1, n);
        scanf("%d", &blockNumber);

        if (!allocateDataBlock(&indexBlock, blockNumber)) {
            printf("Failed to allocate block %d. Index block might be full.\n", blockNumber);
        }
    }

  
    printf("\nAllocated Blocks: ");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (indexBlock.data_blocks[i] != -1) {
            printf("%d ", indexBlock.data_blocks[i]);
        }
    }
    printf("\n");

    
    while (1) {
        printf("\nEnter block number to read (or -1 to exit): ");
        scanf("%d", &blockNumber);
        if (blockNumber == -1)
            break;
        readData(&indexBlock, blockNumber);
    }

}
