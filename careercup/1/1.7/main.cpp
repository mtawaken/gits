#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
void set0(int** matrix,int m,int n){
	bool* flagL=new bool[m];
	bool* flagC=new bool[n];
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(matrix[i][j]==0){
				flagL[i]=1;
				flagC[j]=1;
			}
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(flagL[i]==1||flagC[j]==1)
				matrix[i][j]=0;
		}
	}
}
void print(int **matrix,int m,int n){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}
int main(){
	int m=5;
	int n=3;
	int ** matrix = new int*[m];
	srand(time(NULL));
	for(int i=0;i<m;i++){
		matrix[i]=new int[n];
		for(int j=0;j<n;j++){
			matrix[i][j]=(int)(rand()*3.0/RAND_MAX);
		}
	}
	print(matrix,m,n);
	set0(matrix,m,n);
	print(matrix,m,n);
	return 0;
}
