#include<iostream>
using namespace std;
void swap(int x1, int y1, int x2, int y2, int** matrix) {
	int v = matrix[x1][y1];
	matrix[x1][y1] = matrix[x2][y2];
	matrix[x2][y2] = v;
}
void rotate(int**matrix, int n) {
	for (int shift = 0; shift < n; shift++) {
		for (int j = shift; j < n - shift - 1; j++) {
			//swap(n - shift - 1, j, j, shift, matrix);
			//swap(j, shift, shift, n - j - 1, matrix);
			//swap(shift, n - j - 1, n - j - 1, n - shift - 1, matrix);
			swap(j,n-shift-1,shift,j,matrix);
			swap(shift,j,n-j-1,shift,matrix);
			swap(n-j-1,shift,n-shift-1,n-j-1,matrix);
		}
	}
}
void print(int**matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
int main() {
	int n = 5;
	int **matrix = new int*[5];
	for (int i = 0; i < 5; i++) {
		matrix[i] = new int[5];
		for (int j = 0; j < 5; j++) {
			matrix[i][j] = i * 5 + j;
		}
	}
	print(matrix,n);
	rotate(matrix,n);
	print(matrix,n);
	return 0;
}
