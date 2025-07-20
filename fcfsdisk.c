// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

#define MAXREQUEST 100 

int calculatetotal(int requests[MAXREQUEST],int n,int start)
{
    int currenttrack=start;
    //int seektrack=0;
    int totalseek=0;
    for(int i=0;i<n;i++)
    {
        int seektrack=abs(currenttrack-requests[i]);
        currenttrack=requests[i];
        totalseek+=seektrack;
    }
    return totalseek;
}
void main() {
    
    int n,start;
    printf("Enter the no of requests");
    scanf("%d",&n);
    if(n<=0 || n>MAXREQUEST)
    {
        printf("error");
        return ;
    }
    int requests[n];
    for(int i=0;i<n;i++)
    {
        printf("Enter the request[%d]",i);
        scanf("%d",&requests[i]);
    }
    printf("eneter the start track");
    scanf("%d",&start);
    int totalseek=calculatetotal(requests,n,start);
    printf("total_seek:%d",totalseek);
    
}
