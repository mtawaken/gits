/*
 * =====================================================================================
 *
 *       Filename:  genran.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月29日 21时04分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
int atoi(char a[]){
    int n=0;
    int i=0;
    int flag=1;
    if(!a[0]){
        return 0;
    }
    if(a[0]=='-'){
        i=1;
        flag=-1;
    }
    while(a[i]){
        n*=10;
        n+=(a[i]-'0');
        i++;
    }
    return n*flag;
}
int main(int argc,char* argv[]){
    if(argc!=4){
        return -1;
    }
    int tmin,tmax,n;
    tmin = atoi(argv[1]); 
    tmax = atoi(argv[2]);
    n = atoi(argv[3]);
    if(tmin==tmax||n<=0){
        return -2;
    }else{
        if(tmin>tmax){
            tmin=tmin^tmax;
            tmax=tmin^tmax;
            tmin=tmin^tmax;
        }
    }
    srand(time(NULL));
    for(int i=0;i<n;i++)
        cout<<tmin+(int)floor((rand()*1.0*(tmax-tmin)/RAND_MAX))<<" ";
    cout<<endl;
    return 0;
}
