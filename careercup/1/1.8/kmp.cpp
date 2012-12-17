/*
 * =====================================================================================
 *
 *       Filename:  kmp.cpp
 *
 *    Description:  simple kmp,http://blog.csdn.net/yearn520/article/
 *details/6729426
 *
 *        Version:  1.0
 *        Created:  2012年12月06日 19时22分44秒
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
/*next递归思想：在某个不匹配时，在已经匹配的对称串的一部分中（0~k-1）寻找
*更小的整体对称串，取前一部分（0~next[k-1]-1）,重新比较next[k-1]与j
*/
int* getNext(char*T){
    //next[j]表示在index=j上已经对称了next[j]个字母
    int k,i;
    int tLen = strlen(T);
    int* next = new int[tLen+1];
    next[0] = 0;
    for(i=1;i<tLen;i++){
        /*前面（i-1）上已经对称了next[i-1]个，因此要
         * 比较index为next[i-1]和i上的字母
         */
        k = next[i-1];
        //如果i,k上的字母匹配失败，则找更小的对称串
        while(T[i]!=T[k]&&k!=0){
            k = next[k-1];//0~k-1是仍然匹配的部分
        }
        if(T[i]==T[k]){
            next[i]=k+1;
        }else{
            next[i]=0;
        }        
    }
    return next;
}
bool kmp(char*S,char*T){
    int i,j;
    int sLen = strlen(S);
    int tLen = strlen(T);
    int* next = getNext(T);
    for(int i=0;i<tLen;i++){
        cout<<next[i]<<' ';
    }
    cout<<endl;
    i=0;
    j=0;
    while(j<tLen&&i<sLen){
        if(j==0||S[i]==T[j]){
            i++;
            j++;
        }else{            
            j = next[j-1];
        }
    }
    if(j>=tLen)
        return true;
    else 
        return false;
}
int main(){
    char S[]="ABCABCDABABCDABCDABDE";
    char T[]="ABCDAB";
    cout<<kmp(S,T)<<endl;
    return 0;
}
