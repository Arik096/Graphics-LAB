#include<stdio.h>
#define max 30
int main()
{
    int n,bt[max],ct[max],wt[max],i,j,temp=0,a=0;
    printf("enter the number of process\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&bt[max]);
    }
    for(i=0;i<n;i++)
    {
      for(j=1;j<n;j++)
    {
      if(bt[j-1]>bt[j])
      {
          temp=bt[j-1];
          bt[j-1]=bt[j];
          bt[j]=temp;

      }
    }
    a=bt[i


    ]

    }


}
