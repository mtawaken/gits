/*
 * =====================================================================================
 *
 *       Filename:  p1163.cpp
 *
 *    Description: scrolling array 
 *
 *        Version:  1.0
 *        Created:  2012年12月22日 19时33分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int N,tmp;
    cin>>N;
    int arr[2][101];
    memset(arr,0,sizeof(arr));
    for(int i=1;i<=N;i++){        
        for(int j=1;j<=i;j++){
            cin>>tmp;
            arr[i%2][j]=max(arr[(i-1)%2][j-1]+tmp,arr[(i-1)%2][j]+tmp);
        }
    }
    int max_res=0;
    for(int i=1;i<=N;i++){
        max_res=max(max_res,arr[N%2][i]);
    }
    cout<<max_res<<endl;
}
