// Online C compiler to run C program online
#include <stdio.h>
struct Process
{
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int pid;
    
};
void main() {
    // Write C code here
    int n;
    
    printf("enter the no of processes");
    scanf("%d",&n);
    struct Process p[n];
    for(int i=0;i<n;i++)
    {
        printf("enter the arrival time");
        scanf("%d",&p[i].at);
        printf("enter the burst time");
        scanf("%d",&p[i].bt);
        p[i].pid=i;
        
    }
    int time1=0;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(p[i].at>p[j].at)
            {
                struct Process temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(time1<p[i].at)
        {
            time1=p[i].at;
        }
        p[i].ct=time1+p[i].bt;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        time1+=p[i].bt;
    }
    printf("\tpid\tat\tbt\tct\ttat\twt\n");
    for(int i=0;i<n;i++)
    {
        
        printf("\t%d\t%d\t%d\t%d\t%d\n",p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("\n");
    printf("\n");
    printf("|");
    for(int i=0;i<n;i++)
    {
        printf("\tp[%d]\t|",p[i].pid);
    }
    printf("\n");
    printf("0");
    for(int i=0;i<n;i++)
    {
        printf("\t\t\t%d",p[i].ct);
    }
    
   
    
    
    
    
}