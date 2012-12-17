/*
 * =====================================================================================
 *
 *       Filename:  niddle-PI.cpp
 *
 *    Description:  Buffon-PI
 *
 *        Version:  1.0
 *        Created:  2012年11月30日 11时18分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#define D 1
#define L 0.85
#define N 10000000
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int main(){
    srand(time(NULL));
    float by,ty,a;
    int m,i;
    m=0;
    for(i=0;i<N;i++){
        by = rand()*1.0/RAND_MAX + 1;
        a = rand()*180.0/RAND_MAX;
        ty = by - L*sin(a);
        if(((int)floor(by))!=((int)floor(ty))){
            m++;
        }
    }
    printf("%f\n",2.0*N*L/m); 
    return 0;
}
