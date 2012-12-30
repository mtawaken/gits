/*
 * =====================================================================================
 *
 *       Filename:  insertsort.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月30日 13时48分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */
void f(int*arr,int n){
    int key,i,j;
    for(i=1;i<n;i++){
        key = arr[i];
        for(j=i-1;j>=0;j--){
            if(arr[j]>key){
                arr[j+1]=arr[j];
            }else{
                break;
            }
        }
        arr[j+1]=key;
    }
}
