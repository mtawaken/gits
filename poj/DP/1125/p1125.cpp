/*
 * =====================================================================================
 *
 *       Filename:  p1125.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月23日 12时29分05秒
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
int d[101][101];
int main(){
    int n,t,a,dd;
    cin>>n;
    while(n!=0){
        memset(d,1,sizeof(d));
        for(int i=1;i<=n;i++){
            cin>>t;
            for(int j=0;j<t;j++){
               cin>>a>>dd;
               d[i][a]=dd;
            }
            d[i][i]=0;
        }
        for(int k=1;k<=n;k++){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
                }
            }
        }
        int res;
        int index=-1;
        int flag;
        int min_res=10000;
        for(int i=1;i<=n;i++){
            flag=false;
            res=0;
            for(int j=1;j<=n;j++){
                if(d[i][j]<10000){
                    res = max(res,d[i][j]);
                }else{
                    flag=true;
                    break;
                }
            }
            if(flag){
                continue;
            }else{
                if(min_res>res){
                    min_res=res;
                    index=i;
                }
            }
        }
        if(index==-1){
            cout<<"disjoint"<<endl;
        }else{
            cout<<index<<" "<<min_res<<endl;
        }
        cin>>n;
    }
    return 0;
}
