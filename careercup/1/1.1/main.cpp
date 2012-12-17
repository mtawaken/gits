#include<iostream>
#include<string>
#include<string.h>
using namespace std;
bool test(string& a){
	char check[256];
	memset(check,0,256);
	for(string::size_type i=0;i<a.length();i++){
		if(check[(int)a[i]]!=0){
			return false;
		}else{
			check[(int)a[i]]=1;
		}
	}
	return true;
}
bool test2(string& a){
	//assume only a-z
	int check = 0;
	for(string::size_type i=0;i<a.size();i++){
		int v = 1<<(a[i]-'a');
		if((v&check)>0){
			return false;
		}else{
			check = check | v;
		}
	}
	return true;
}
bool test3(string&a){
	string::size_type i,j;
	for(i=1;i<a.size();i++){
		char v = a[i];
		for(j=i-1;j>=0;j--){
			if(v<a[j]){
				a[j+1]=a[j];
			}else{
				a[j+1]=v;
				break;
			}
		}
		if(j==-1)
			a[0]=v;
	}
	for(i=1;i<a.size();i++){
		if(a[i]==a[i-1]){
			return false;
		}
	}
	return true;
}
int main(){
	string a = "aegveewcx";
	cout<<test(a)<<endl;
	cout<<test2(a)<<endl;
	cout<<test3(a)<<endl;
	a.~string();
	return 0;
}
