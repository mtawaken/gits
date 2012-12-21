/*
 * =====================================================================================
 *
 *       Filename:  p1088.cpp
 *
 *    Description:  snowy
 *
 *        Version:  1.0
 *        Created:  2012年12月21日 16时29分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<iostream>
using namespace std;
int m[101][101];
int d[101][101];
int C,R;
int count(int i,int j){
    if(d[i][j]>0)
        return d[i][j];
    int res=0;
    if(i>0){
        if(m[i-1][j]<m[i][j]){
            res = max(count(i-1,j),res);
        }
    }
    if(j>0){
        if(m[i][j-1]<m[i][j]){
            res = max(count(i,j-1),res);
        }
    }
    if(j<C-1){
        if(m[i][j+1]<m[i][j]){
            res = max(count(i,j+1),res);
        }
    }
    if(i<R-1){
        if(m[i+1][j]<m[i][j]){
            res = max(count(i+1,j),res);
        }
    }
    res=res+1;
    d[i][j]=res;
    return res;
}
int main(){
    cin>>R>>C;
    for(int i=0;i<101;i++){
        for(int j=0;j<101;j++){
            d[i][j]=0;
        }
    }
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            cin>>m[i][j];
        }
    }
    int res=-1;
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            res = max(count(i,j),res);
        }
    }
    cout<<res<<endl;
    return 0;
}
