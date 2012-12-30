/*
 * =====================================================================================
 *
 *       Filename:  bubblesort.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月30日 13时54分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

void f(int *arr,int n){
    for(int i=0;i<n;i++){
        for(int j=1;j<n-i;j++){
            if(arr[j-1]>arr[j]){
                swap(arr[j-1],arr[j]);
            }
        }
    }
}
