/*
 * =====================================================================================
 *
 *       Filename:  prime-PI.cpp
 *
 *    Description:  get PI by prime
 *
 *        Version:  1.0
 *        Created:  2012年12月05日 19时04分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define N 1000
using namespace std;
int gcd(int a,int b){
    int r;
    while(b>0){
        r=a%b;
        a=b;
        b=r;
    }
    return a;
}
int main(){
    srand(time(NULL));
    int n = 1000;
    int m = 0;
    float p;
    int a,b,numofgcd;
    for(int i=0;i<n;i++){
        a = (int)((rand()*1.0*N)/RAND_MAX);
        b = (int)((rand()*1.0*N)/RAND_MAX);
        numofgcd = gcd(a,b);
        if(numofgcd==1)
            m++;
    }
    cout<<sqrt(6.0*n/m)<<endl;
    return 0;
}
