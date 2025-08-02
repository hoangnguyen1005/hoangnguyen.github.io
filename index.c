#include<stdio.h>
int main()
{
    int n;
    printf("nhap n:\n");
    scanf("%d",&n);
    int myABC[n];
    int i=0;
    for(i=0;i<n;i++)
    {
        printf("phan tu thu %d",i+1);
        scanf("%d",&myABC[i]);
    }
   
   for(i=0;i<n;i++)
    {
        printf("%d ",myABC[i]);
    }
return 0;
}