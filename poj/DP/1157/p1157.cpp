/*
 * =====================================================================================
 *
 *       Filename:  p1157.cpp
 *
 *    Description: d[i][j] 可以表示第i束花插在第j个花瓶的最大价值,可用滚动数组。d[i][j]也可表示从第i到V个花瓶位置选j个位置放剩余花能产生的最大价值。总之无后效性就可以。第一种方式更容易产生d，第二种方式更像多阶段决策，更直观。
 *
 *        Version:  1.0
 *        Created:  2012年12月22日 16时30分02秒
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
int F,V;
int m[101][101];
int d[101][101];
bool b[101][101];
int get(int index,int count){
   if(count==0){
       return 0;
   }
   if(b[index][count]){
       return d[index][count];
   }
   int max_res,has_set;
   has_set=-1;
   for(int i=index;i<=V-count+1;i++){
        if(has_set==-1){
            has_set=0;
            max_res = m[F-count+1][i]+get(i+1,count-1);
        }else{
            max_res = max(max_res,m[F-count+1][i]+get(i+1,count-1));
        }
   }
   d[index][count]=max_res;
   b[index][count]=1;
   return d[index][count];   
}
int main(){
    memset(b,0,sizeof(b));
    cin>>F>>V;
    for(int i=1;i<=F;i++){
        for(int j=1;j<=V;j++){
            cin>>m[i][j];
        }
    }
    cout<<get(1,F)<<endl;
    return 0;
}
