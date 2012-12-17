#include<iostream>
#include<string.h>
using namespace std;
void removeDup(char*str){
	//mark char that has occured to 0,and at last deal with 0s
	//O(2*N)
	if(str==NULL)
		return;
	bool check[256];
	int i;
	for(i=0;i<256;i++)
		check[i]=0;
	i=0;
	while(str[i]){
		if(check[(int)str[i]]!=0){
			str[i]=0;
		}else{
			check[(int)str[i]]=1;
		}
		i++;
	}
	int end = i;
	int toFil=0;
	while(str[toFil]!=0){
		toFil++;
	}
	int pick = toFil+1;
	while(str[pick]==0){
		pick++;
	}
	while(pick<end){
		if(str[pick]==0){
			pick++;
			continue;
		}else{
			str[toFil]=str[pick];
			while(toFil<end&&str[toFil]!=0){
				toFil++;
			}
			pick++;
		}
	}
}
void reDu(char* str){
	//use tail rather than fill blanks at one time
	if(str==NULL)
		return;
	int len = strlen(str);
	if(len<3)
		return;
	bool check[256];
	for(int i=0;i<256;i++){
		check[i]=0;
	}
	int tail = 1;
	check[(int)str[0]]=1;
	for(int i=1;i<len;i++){
		if(check[(int)str[i]]==0){
			str[tail]=str[i];
			check[(int)str[i]]=1;
			tail++;
		}
	}
	str[tail]=0;
}
int main(){
	char str[]="abcdaaaeb3";
	reDu(str);
	cout<<str<<endl;
	return 0;
}
