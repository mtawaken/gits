/*
 * =====================================================================================
 *
 *       Filename:  p1018.correction.cpp
 *
 *    Description:  forcely search,for every available brandwidth,there's a lowest sum price which make RATE maxium,compare theses RATEs to find maxium RATE to be the result.
 *
 *        Version:  1.0
 *        Created:  2012年12月17日 09时34分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<stdio.h>
#define min(x,y) (x>y?y:x)
#define max(x,y) (x>y?x:y)
typedef struct NodeT{
    int b;
    int p;
} Node;
int n;//number of devices
Node nodes[101][101];
int m[101];
int minb,maxb,oneminb,onemaxb;
void scan(){
    scanf("%d",&n);
    maxb=0x7fffffff;
    minb=0x7fffffff;
    for(int i=0;i<n;i++){
        scanf("%d",&m[i]);
        oneminb=0x7fffffff;
        onemaxb=0;
        for(int j=0;j<m[i];j++){
            scanf("%d %d",&nodes[i][j].b,&nodes[i][j].p);
            oneminb = min(nodes[i][j].b,oneminb);
            onemaxb = max(nodes[i][j].b,onemaxb);
        }
        minb = min(oneminb,minb);
        maxb = min(onemaxb,maxb);
    }
}
void work(){
    float rate = 0;
    int sump = 0;
    for(int b=minb;b<=maxb;b++){
        for(int i=0;i<n;i++){
            int p=0x7fffffff;
            for(int j=0;j<m[i];j++){
                if(nodes[i][j].b>=b){
                    p=min(p,nodes[i][j].p);
                }
            }
            sump += p;
        }
        rate = max(rate,b*1.0/sump);
        sump = 0;
    }
    printf("%.3f\n",rate);
}
int main(){
    int test;
    scanf("%d",&test);
    while(test--){
        scan();
        work();
    }
    return 0;
}
