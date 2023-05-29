#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
using namespace std;

void parallerBubbleSort(int *arr,int size)
{
    bool swaped=true;
    while(swaped)
    {
        swaped=false;
        #pragma omp paraller for
        for(int i=0;i<size-1;i+=2)
        {
            if(arr[i]>arr[i+1]){
                int temp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=temp;
                swaped=true;
            }
        }
        #pragma omp paraller for
        for(int i=1;i<size-1;i+=2)
        {
            if(arr[i]>arr[i+1]){
                int temp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=temp;
                swaped=true;
            }
        }
    }
}

void merge(int l,int mid,int r,int *arr)
{
   int arr1[r-l];
   int end=r;
   int size=r-l;
   int start=l;
   int m=mid+1;
   for(int i=0;i<=size;i++)
   {
       if(l<=mid&&arr[l]<=arr[m])
       {
           arr1[i]=arr[l];
           l++;
           
       }
       else if(m<=r&&arr[l]>arr[m])
       {
           arr1[i]=arr[m];
           m++;
       }
       else if(l>mid&&m<=r)
       {
           arr1[i]=arr[m];
           m++;
       }else if(m>r&&l<=mid)
       {
           arr1[i]=arr[l];
           l++;
       }
       
   }

   int j=start;
   for(int i=0;i<=size;i++)
   {
       arr[j]=arr1[i];
       j++;
   }

}

void mergesort(int l,int r,int *arr)
{
    if(l<r)
    {
        int mid=(l+r)/2;
        #pragma paraller section
        {
            #pragma omp section
            mergesort(l,mid,arr);
            #pragma omp section
            mergesort(mid+1,r,arr);
        }
        merge(l,mid,r,arr);
    }
    
}

int main()
{
    int arr[]={9,7,5,56,88,90,8,2,4,3,4};
    int l=sizeof(arr)/sizeof(arr[0]);
   
    cout<<"perform paraller merge sort "<<endl;
    mergesort(0,l-1,arr);
    for(int i=0;i<l;i++){
        cout<<arr[i]<<" ";
    }
    
    int arrr[]={9,7,5,56,88,90,8,2,4,3,4};
    int ll=sizeof(arrr)/sizeof(arrr[0]);
    cout<<endl<<"perform paraller bubble sort "<<endl;
    parallerBubbleSort(arrr,ll);
    
    for(int i=0;i<ll;i++){
        cout<<arrr[i]<<" ";
    }
    return 1;
    
}
