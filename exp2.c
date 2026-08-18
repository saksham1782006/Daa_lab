#include<stdio.h>

int linearSearch(int arr[],int n, int key){
    for (int i=0;i<n;i++){
        if(arr[i]==key){return i;}
    }
    return -1;
}
int binarySearch(int arr[],int n, int key){
    int l=0
    int h=n-1
    while (l<=h){
        int mid=l+(h-l)/2;
        if(arr[mid]==key){
            return mid;
        }
        else if(arr[mid]<key){
            l=mid+1;
            }
        else{
            h=mid-1;
        }
        
    }
    return -1;
}
int main(){
    int arr[]={10,20,30,40,50,60,70,80,90,100};
    int n=sizeof(arr)/sizeof(arr[0]);
    int key;
    printf("Enter element to search: ");
    scanf("%d",&key);
    int linearresult=linearSearch(arr,n,key);
    if(linearresult==-1)
{
    printf("Element not found in linear search\n");
}
int binaryresult=binarySearch(arr,n,key);
if(binaryresult==-1)
{
    printf("Element not found in binary search\n");
}
else
{
    printf("Element found at index %d in binary search\n", binaryresult);
}
}
