#include <stdio.h>
#include <stdlib.h>
#include<omp.h>
int main()
{
    
    int arr[10][10],i,j,m,n,k,count1[10],min_sup,count2[10][10];
    
    printf("Enter the number of transactions\n");
    scanf("%d",&m);
    printf("Number of items that can be transactioned\n");
    scanf("%d",&n);
   // Initializing count to zero
   #pragma omp parallel for
     for(i=0;i<10;i++)
    {
        count1[i]=0;
    }

    for(i=0;i<10;i++)
    {
      #pragma omp parallel for 
        for(j=0;j<10;j++)
        {
            count2[i][j]=0;
        }
    }
    printf("Enter the matrix of transactions with transactions on y-axis and items transactioned on x-axis\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
       {
            scanf("%d",&arr[i][j]);
        }
    }
    printf("The input matrix of transactions in\n");
    for(i=0;i<m;i++)
    {
        #pragma omp parallel for
        for(j=0;j<n;j++)
        {
            printf("%d\t",arr[i][j]);
        }
        printf("\n");
    }
    //STEP-1:calculating the set of frequent-1 item sets
    for(j=0;j<n;j++)
    {
        for(i=0;i<m;i++)
        {
            count1[j]=count1[j]+arr[i][j];
        }
    }
    printf("The set of frequent-1 item sets(Candidate support count)\n");
    for(j=0;j<n;j++)
    {
        printf("count1[%d]=%d\n",j,count1[j]);
    }
    printf("Enter the minimum support count1\n");
    scanf("%d",&min_sup);
    printf("The set after comparing the candidate support count with minimum support count\n");
    #pragma omp parallel for
    for(j=0;j<n;j++)
    {
        if(count1[j]>=min_sup)
        {
           printf("count1[%d]=%d\n",j,count1[j]);
        }
    }
    //STEP-2:Generating two item set frequent pattern
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            printf("%d\t%d\n",i,j);
           #pragma omp parallel for
            for(k=0;k<m;k++)
            {
                if(arr[k][i]==1&&arr[k][j]==1)
                {
                    count2[i][j]=count2[i][j]+1;
                }
            }
        }
    }
     for(i=0;i<m;i++)
    {
       #pragma omp parallel for
        for(j=0;j<n;j++)
        {
            printf("%d",count2[i][j]);
        }
        printf("\n");
    }


    return 0;
}

