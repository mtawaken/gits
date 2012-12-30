/*
 * =====================================================================================
 *
 *       Filename:  quicksort.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月30日 14时25分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */
int partition(int*arr,int s,int e){
    int pivot = arr[s];
    int i=s,j=e;
    while(i<j){
        while(i<j&&arr[j]>=pivot){
            j--;
        }
        if(i<j){
            arr[i]=arr[j];
            i++;
        }
        while(i<j&&arr[i]<pivot){
            i++;
        }
        if(i<j){
            arr[j]=arr[i];
            j--;
        }
    }
    arr[i]=pivot;
    return i;
}
void quicksort(int* arr,int s,int e){
    if(s>=e)
        return;
    int p = partition(arr,s,e); 
    quicksort(arr,s,p-1);
    quicksort(arr,p+1,e);
}

void f(int*arr,int n){
    quicksort(arr,0,n-1);
}
