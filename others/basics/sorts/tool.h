/*
 * =====================================================================================
 *
 *       Filename:  tool.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月30日 13时17分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

int atoi(char a[]){
    if(a[0]==0){
		return 0;
	}
	int n=0;
    int i=0;
    int flag=1;
    if(a[0]=='-'){
        flag=-1;
        i=1;
    }
    while(a[i]){
        n*=10;
        n+=(a[i]-'0');
        i++;
    }
    return flag*n;
}
int* getArrayByParam(int argc,char* argv[]){
    if(argc==1)
        return NULL;
    int* arr = new int[argc-1];
    for(int i=0;i<argc-1;i++){
        arr[i]=atoi(argv[i+1]);
    }
    return arr;
}
void swap(int&a,int&b){
    a=a^b;
    b=a^b;
    a=a^b;
}
