/*
 * =====================================================================================
 *
 *       Filename:  rect-oval-PI.cpp
 *
 *    Description:  MontaCarlo-PI
 *
 *        Version:  1.0
 *        Created:  2012年11月30日 10时13分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 10000000
int main(){
    srand(time(NULL));
    int i,m;
    float x,y;
    m=0;
    for(i=0;i<N;i++){
        x = rand()*2.0/RAND_MAX - 1;
        y = rand()*2.0/RAND_MAX - 1;
        if((x*x+y*y)<=1){
            m++;
        }
    }
    printf("%f\n",m*4.0/N);
    return 0;
}
