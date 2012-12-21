/*
 * =====================================================================================
 *
 *       Filename:  p1083.cpp
 *
 *    Description:  corridor
 *
 *        Version:  1.0
 *        Created:  2012年12月21日 13时15分25秒
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
typedef struct NodeT{
    int s,f;
    bool done;
} Node;
Node*list = new Node[201];
void fill(Node&node){
    int f,s;
    cin>>s>>f;
    if(s%2==0){
        s--;
    }
    if(f%2==1){
        f++;
    }
    if(s>f){
        int tmp=f;
        f=s;
        s=tmp;
    }
    node.f=f;
    node.s=s;
    node.done=false;
}
int main(){
    int T,N;
    cin>>T;
    while(T--){
        cin>>N;
        for(int i=0;i<N;i++){
            fill(list[i]);
            int f = list[i].f;
            int s = list[i].s;
            int j;
            for(j=i-1;j>=0;j--){
                if(list[j].s>s){
                    list[j+1].f=list[j].f;
                    list[j+1].s=list[j].s;
                }else{
                    break;
                }
            }
            list[j+1].f=f;
            list[j+1].s=s;
        }
        int times=0;
        bool has = true;
        while(has){
            times++;
            int f=0;         
            has=false;
            for(int i=0;i<N;i++){
                if(list[i].done)
                    continue;
                if(list[i].s<=f){
                    has = true;
                    continue;
                }
                list[i].done=true;
                f=list[i].f;
            }
        }
        cout<<times*10<<endl;
    }
    return 0;
}
