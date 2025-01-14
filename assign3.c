#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
 
void bubbleSort(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
 
void displayArr(int arr[],int n)
{
    printf("\n Displaying Array Elements:\n");
    for(int i=0;i<n;i++)
    {
        printf(" %d ",arr[i]);
    }
    printf("\n Display Complete \n");
}
 
// 0 - Zombie State
// 1 - Orphan State
void main(int argc, char *argv[])
{
    printf("\n \n IM \n");
    int cpid = fork();
 
    int arr[] = {10,5,1,60,20};
    int n = 5;


    int ch = atoi(argv[1]);
 
    printf("\n\n Ch: %d \n",ch);
    printf("\nCPID: %d\n",cpid);
    if(cpid > 0)
    {
        printf("\n\n Parent is Running\n It's ID: %d \n PPID: %d \n",getpid(),getppid());
        printf("\n Parent is calling BubbleSort:\n");
        printf("\n Parent Displaying Array Before Sort:\n");
        displayArr(arr,n);
        printf("\n Parent is Starting Sorting:\n");
        bubbleSort(arr,n);
        printf("\n\n Parent is going to Sleep!\n");
         
        if(ch == 0)
        {
            //printf("\n\n Parent Zombie State \n");
            sleep(10);
            wait(NULL); // To collect the child exit status
        }
        else
        {
            //printf("\n\n Parent Orphan State \n");
            sleep(1);
        }
 
        printf("\n\n Parent Woke's Up");
        printf("\n\n Parent Displaying Array After Sort:\n");
        displayArr(arr,n);
        if(ch == 1)
        {
            printf("\n Parent is Exiting!\n");
        }
    }
    else if(cpid == 0)
    {
        printf("\n\n Child is Running \n It's ID: %d \n PPID: %d \n",getpid(),getppid());
        printf("\n Child is calling BubbleSort:\n");
        printf("\n Child Displaying Array Before Sort:\n");
        displayArr(arr,n);
        printf("\n Child is Starting Sorting:\n");
        bubbleSort(arr,n); 
        if(ch == 1)
        {
            printf("\n Child is goint to Sleep \n");
            sleep(10);
            printf("\n\n Child Orphan State \n It's ID: %d \n PPID: %d \n",getpid(),getppid());
        }
 
        printf("\n Child Displaying Array After Sort:\n");
        displayArr(arr,n);
        printf("\n Child Exiting!\n\n");
         
        if(ch == 0)
        {
            printf("\n\n Child Zombie State \n");
        }
    }
}