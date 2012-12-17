/*
 * =====================================================================================
 *
 *       Filename:  p1018.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月16日 15时32分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<iostream>
#include<iomanip>
#define min(x,y) (x<y?x:y)
using namespace std;
int main(){
    int times;
    cin>>times;
    int devices,cb,cp,number,b,p,tb,tp;
    float cr,tr,tmp;
    while(times--){
        cin>>devices;
        cb=0x7fffffff;
        cp=0;
        cr=0;
        for(int i=0;i<devices;i++){
            cin>>number;
            tr = 0;
            for(int j=0;j<number;j++){
                cin>>b>>p;
                tmp =min(cb,b)*1.0/(p+cp);
                if(tmp>=tr){
                    tr = tmp;
                    tb = b;
                    tp = p;
                }
            }
            cr = tr;
            cb = min(cb,tb);
            cp = tp + cp;
        }
        cout<<fixed<<setprecision(3)<<cr<<endl;
    }
    return 0;
}
