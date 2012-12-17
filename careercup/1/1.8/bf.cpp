/*
 * =====================================================================================
 *
 *       Filename:  bf.cpp
 *
 *    Description:  plain is_sub_str
 *
 *        Version:  1.0
 *        Created:  2012年12月06日 19时12分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<iostream>
#include<string.h>
using namespace std;
bool bf(char* S,char* T){
    int tLen = strlen(T);
    int sLen = strlen(S);
    if(sLen<tLen||tLen==0)
        return false;
    int i=0;//index in S
    int j=0;//index in T
    while(j<tLen&&i<sLen){
        if(S[i]==T[j]){
            i++;
            j++;
        }else{
            i=i-j+1;
            j=0;
        }
    }
    if(j==tLen)
        return true;
    return false;
}

int main(){
    char S[]="abcdefgh";
    char T[]="fghi";
    cout<<bf(S,T)<<endl;
    return 0;
}
