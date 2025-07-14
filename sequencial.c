
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct File
{
    char filename[200];
    int startblock;
    int noofblocks;
};
void fileconfig(struct File* file1,int start,int count)
{
    strcpy(file1->filename,"file.txt");
    file1->startblock=start;
    file1->noofblocks=count;
}
void main() {
    
    struct File file1;
    int a1,a2;
    printf("enter the starting block");
    scanf("%d",&a1);
    printf("enter the no of blocks");
    scanf("%d",&a1);
    fileconfig(&file1,a1,a2);
    
    printf("File Name: %s\n", file1.filename);
    printf("Start Block: %d\n", file1.startblock);
    printf("Number of Blocks: %d\n", file1.noofblocks);
}
