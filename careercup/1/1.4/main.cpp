#include<iostream>
#include<string.h>
using namespace std;
bool judge(char*a, char*b) {
	if (a == NULL && b == NULL)
		return true;
	int len_a, len_b;
	len_a = strlen(a);
	len_b = strlen(b);
	if (len_a != len_b)
		return false;
	int check[256];
	for (int i = 0; i < 256; i++) {
		check[i] = 0;
	}
	for (int i = 0; i < len_a; i++) {
		check[(int) a[i]]++;
	}
	for (int i = 0; i < len_b; i++) {
		check[(int) b[i]]--;
	}
	for (int i = 0; i < 256; i++) {
		if (check[i] != 0)
			return false;
	}
	return true;

}
int main() {
	char a[]="abdeg";
	char b[]="fdbae";
	cout<<judge(a,b)<<endl;
	return 0;
}
