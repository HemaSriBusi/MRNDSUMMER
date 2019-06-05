#include "stdio.h"
#include "stdlib.h"
#include "iostream"

using namespace std;

int main() {
	int row, column;
	cin >> row;
	cin >> column;
	int j;
	int a[row][column];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++)
			cin >> a[i][j];
	}
	int res[row*column];
	int idx = 0;
	int row_start = 0, column_start = 0, i;
	while (row_start < row && column_start < column) {
		for (i = column_start; i < column; i++) {
			res[idx++] = a[row_start][i];
		}
		row_start++;
		for (i = row_start; i < row; i++) {
			res[idx++] = a[i][column - 1];
		}
		column--;
		if (row_start < row) {
			for (i = column - 1; i >= 0; i--)
				res[idx++] = a[row - 1][i];
			row--;
		}
		if (column_start < column) {
			for (i = row - 1; i >= row_start; i--)
				res[idx++] = a[i][column_start];
			column_start++;
		}
	}
	for (j = 0; j < idx; j++)
		cout << res[j] << ' ';
	return 0;
}


