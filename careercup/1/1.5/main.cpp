#include<iostream>
using namespace std;
char* convert(char* str){
	int spaceCount = 0;
	char*p = str;
	while(*p){
		if(*p==' ')
			spaceCount++;
		p++;
	}
	int newLength = p-str + spaceCount*2;
	char*newStr = new char[newLength+1];
	int index=0;
	for(int i=0;i<p-str;i++){
		if(str[i]==' '){
			newStr[index++]='%';
			newStr[index++]='2';
			newStr[index++]='0';
		}else{
			newStr[index++]=str[i];
		}
	}
	newStr[newLength]=0;
	return newStr;
}
int main(){
	char a[]="ab ce  gjs 0";
	char*b=convert(a);
	cout<<b<<endl;
	return 0;
}
