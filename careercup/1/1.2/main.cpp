#include<iostream>
#include<string>
#include<string.h>
using namespace std;
void reverse(string&a) {
	string::size_type i, j;
	i = 0;
	j = a.size() - 1;
	while (i < j) {
		char v = a[i];
		a[i] = a[j];
		a[j] = v;
		i++;
		j--;
	}
}
void reverse(char*str) {
	int i, j;
	i = 0;
	j = strlen(str) - 1;
	while (i < j) {
		char v = str[i];
		str[i] = str[j];
		str[j] = v;
		i++;
		j--;
	}
}
int main() {
	string a = "abcde12";
	reverse(a);
	cout << a << endl;
	char str[]="abcde12";
	reverse(str);
	cout<<str<<endl;
	return 0;
}
