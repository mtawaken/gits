/*
 * =====================================================================================
 *
 *       Filename:  heapsort.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月30日 15时12分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */
void heapify(int*arr,int i,int n){
    int left = i*2;
    int right = left+1;
    int index=0;
    if(left<=n){
        index=left;
    }
    if(right<=n){
        if(arr[left]<arr[right]){
            index=right;
        }
    }
    if(index!=0){
        if(arr[i]<arr[index]){
            swap(arr[i],arr[index]);
            heapify(arr,index,n);
        }
    }
}
void buildheap(int*arr,int n){
    for(int i=n/2;i>=1;i--){
        heapify(arr,i,n);
    }
}
void heapsort(int*arr,int n){
    buildheap(arr,n);
    for(int i=n;i>1;i--){
        swap(arr[i],arr[1]);
        heapify(arr,1,i-1);
    }
}
void f(int*arr,int n){
    int*newarr=new int[n+1];
    for(int i=0;i<n;i++){
        newarr[i+1]=arr[i];
    }
    heapsort(newarr,n);
    for(int i=0;i<n;i++){
        arr[i]=newarr[i+1];
    }
    delete newarr;
}
