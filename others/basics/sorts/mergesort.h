/*
 * =====================================================================================
 *
 *       Filename:  mergesort.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月30日 14时08分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */
void mergesort(int*arr,int s,int e){
    if(s>=e)
        return;
    int mid = (s+e)/2;
    mergesort(arr,s,mid);
    mergesort(arr,mid+1,e);
    int i=s,j=mid+1,k=0;
    int*newArr = new int[e-s+1] ;
    while(i<=mid&&j<=e){
        if(arr[i]>arr[j]){
            newArr[k++]=arr[j];
            j++;
        }else{
            newArr[k++]=arr[i];
            i++;
        }
    }
    while(i<=mid){
        newArr[k++]=arr[i++];
    }
    while(j<=e){
        newArr[k++]=arr[j++];
    }
    k=0;
    for(i=s;i<=e;i++){
        arr[i]=newArr[k++];
    }
    delete newArr;
}
void f(int*arr,int n){
    mergesort(arr,0,n-1);
}
