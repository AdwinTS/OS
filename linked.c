// Online C compiler to run C program online
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct Block
{
    int block_number;
    struct Block *next;
};
// void fileconfig(struct File* file1,int start,int count)
// {
//     strcpy(file1->filename,"file.txt");
//     file->startblock=start;
//     file->noofblocks=count;
// }
struct Block* alloacteblock(int block_number)
{
   struct Block* block1=(struct Block*)malloc(sizeof(struct Block));
   block1->block_number=block_number;
   block1->next=NULL;
   return block1;
}

void main() {
    int n, blockNumber;
    struct Block* head = NULL;
    struct Block* current = NULL;
    printf("Enter the number of blocks to allocate: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("No blocks to allocate.\n");
        return ;
    }
    for(int i=0;i<n;i++)
    {
        printf("pls enter the block %d",i+1);
        scanf("%d",&blockNumber);
        struct Block* newblock=alloacteblock(blockNumber);
    if(head==NULL)
    {
        head=newblock;
        current=head;
    }
    else
    {
        current->next=newblock;
        current=current->next;
    }
        
    }
    
    printf("allocated blocks");
    current=head;
    while(current!=NULL)
    {
        printf("%d ",current->block_number);
        current=current->next;
    }
    printf("\n");
    current=head;
    while(current!=NULL)
    {
        struct Block* temp=current;
        current=current->next;
        free(temp);
    }
    // Write C code here
    // struct File file1;
    // int a1,a2;
    // printf("enter the starting block");
    // scanf("%d",&a1);
    // printf("enter the no of blocks");
    // scanf("%d",&a1);
    // fileconfig(&file1,a1,a2);
    
    // printf("File Name: %s\n", file1.filename);
    // printf("Start Block: %d\n", file1.startblock);
    // printf("Number of Blocks: %d\n", file1.noofblocks);
}
