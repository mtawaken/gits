/*
 * =====================================================================================
 *
 *       Filename:  tester.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月29日 20时41分00秒
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
int atoi(char s[]){
    int n=0;
    int i=0;
    int flag=1;
    if(!s[0]){
        return 0;
    }
    if(s[0]=='-'){
        i=1;
        flag=-1;
    }
    while(s[i]){
        n*=10;
        n+=(s[i]-'0');
        i++;
    }
    return n*flag;
}
int main(int argc,char* argv[]){
    cout<<"tester:";
    if(argc==1){
        cout<<"no input!"<<endl;
        return -1;
    }else{
        bool flag=true;
        int i;
        for(i=2;i<argc;i++){
            if(atoi(argv[i])<atoi(argv[i-1])){
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<"sorted!"<<endl;
        }else{
            cout<<"unsorted in No."<<i<<endl;
            for(i=1;i<argc;i++){
                cout<<atoi(argv[i])<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}
