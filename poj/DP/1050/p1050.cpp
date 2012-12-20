/*
 * =====================================================================================
 *
 *       Filename:  p1050.cpp
 *
 *    Description:  to the max
 *
 *        Version:  1.0
 *        Created:  2012年12月20日 19时50分31秒
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
int d[2][101][101];
int num[101];
int res,preindex,cindex,linesum,cmax;
int main(){
    int N;
    cin>>N;
    res = 0;
    preindex=0;
    cindex=1;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>num[j];
        }
        cmax=0;
        for(int m=0;m<N;m++){
            linesum=0;
            for(int n=m;n<N;n++){
                linesum+=num[n];
                if(i==0){
                    d[cindex][m][n]=linesum;
                }else{
                    if(d[preindex][m][n]<=0){
                        d[cindex][m][n] = linesum;
                    }else{
                        d[cindex][m][n] = linesum+d[preindex][m][n];
                    }
                }
            
                if(cmax<d[cindex][m][n]){
                    cmax = d[cindex][m][n];
                }
            }
        }
        if(res<cmax){
            res = cmax;
        }
        preindex=(preindex+1)%2;
        cindex=(cindex+1)%2;
    }
    cout<<res<<endl;
    return 0;
}
