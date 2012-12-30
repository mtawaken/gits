/*
 * =====================================================================================
 *
 *       Filename:  insertsort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月30日 13时15分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<iostream>
#include "tool.h"
#include "heapsort.h"
using namespace std;

int main(int argc,char* argv[]){
    int* arr = getArrayByParam(argc,argv);
    if(arr==0)
        return -1;
    f(arr,argc-1);
    for(int i=0;i<argc-1;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}
