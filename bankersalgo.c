
#include <stdio.h>

int main() {
    // Write C code here
    int numP,numR,i,j,k;
    int max[20][20],alloc[20][20],aval[20],need[20][20];
    int safeSeq[20],work[20],finish[20],ind=0;
    printf("enter the no of processes");
    scanf("%d",&numP);
    printf("enter the no of resources");
    scanf("%d",&numR);
    printf("enter max alliocated");
    for(int i=0;i<numP;i++)
    {
        for(int j=0;j<numR;j++)
        {
            printf("enter max[%d][%d]",i,j);
            scanf("%d",&max[i][j]);
        }
    }
    printf("enter  alliocated");
    for(int i=0;i<numP;i++)
    {
        for(int j=0;j<numR;j++)
        {
            printf("enter alloc[%d][%d]",i,j);
            scanf("%d",&alloc[i][j]);
        }
    }
    printf("enter avaliable resources");
    for(int j=0;j<numR;j++)
        {
            printf("enter aval[%d]",j);
            scanf("%d",&aval[j]);
        }
    for(int i=0;i<numP;i++)
    {
        for(int j=0;j<numR;j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    for(i = 0; i < numP; i++) {
        finish[i] = 0;
    }
    
    
    for(i = 0; i < numR; i++) {
        work[i] = aval[i];
    }
    int count=0;
    while(count<numP)
    {
        int found=0;
        for(int i=0;i<numP;i++)
        {
            if(finish[i]==0)
            {
                int flag=0;
                for(int j=0;j<numR;j++)
                {
                    if(need[i][j]>work[j])
                    {
                        flag=1;
                        break;
                        
                    }
                }
                if(flag==0)
                {
                    safeSeq[ind++]=i;
                    for(k=0;k<numR;k++)
                    {
                        work[k]+=alloc[i][k];
                    }
                    finish[i]=1;
                    found=1;
                    count++;
                }
            }
        }
        if(found==0)
        {
            printf("it is unsafe state");
            return 0;
        }
    }
    printf("\nSystem is in safe state\n");
    printf("Safe sequence: ");
    for(i = 0; i < numP; i++) {
        printf("P%d", safeSeq[i]);
        if(i < numP - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
    
    return 0;
    
    
    
}
