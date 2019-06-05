#include "iostream"
#include "stdafx.h"

using namespace std;

bool rightsearch(int j,int i,int column,int idx,int len,char **a,char *s) {
	int count = 0;
	int k;
	for (k = j; k < column && idx < len; k++) {
		if (s[idx] == a[i][k])
			count++;
		if (count == len) {
			break;
		}
		idx++;
	}
	if (count == len) {
		printf("%d%d", i, j);
		printf("%d%d", i, k);
		return true;
	}
	return false;
}

bool downsearch(int j, int i, int row, int idx, int len, char **a, char *s) {
	int count = 0;
	int k;
	for (k = i; k < row && idx < len; k++) {
		if (s[idx] == a[k][j])
			count++;
		if (count == len) {
			break;
		}
		idx++;
	}
	if (count == len) {
		printf("%d%d", i, j);
		printf("%d%d", k, j);
		return true;
	}
	return false;
}

bool leftdiagonal(int j, int i, int row, int column, int idx, int len, char **a, char *s) {
	int count = 0;
	int r = i, c = j;
	for (r = i, c = j; r < row && c < column && idx < len ; r++, c++) {
		if (s[idx] == a[r][c])
			count++;
		if (count == len) {
			break;
		}
		idx++;
	}
	if (count == len) {
		printf("%d%d", i, j);
		printf("%d%d", r, c);
		return true;
	}
	return false;
}

bool rightdiagonal(int row, int column, int idx, int len, char **a, char *s) {
	int start = row, end = column;
	int count = 0;
	for (start = row,end = column; start >= 0 && end >= 0 ; start--,end--) {
		if (s[idx] == a[start][end]) 
			count++;
		if (count == len) {
			break;
		}
		idx++;
	}
	if (count == len) {
		printf("%d%d", row, column);
		printf("%d%d", start,end);
		return true;
	}
	return false;

}

void searchstr(char **a,int row,int column,int len,char *s) {
	int found = 0;
	for (int i = 0,row_end = row-1; i < row && row_end >= 0 ; i++,row_end--) {
		for (int j = 0,column_end = column - 1 ; j < column && column_end >= 0 ; j++,column_end--) {
			if (rightsearch(j,i,column,0,len,a,s)) {
				found = 1;
				break;
			}
			else if (downsearch(j, i, row, 0, len, a, s)) {
				found = 1;
				break;
			}
			else if (leftdiagonal(j, i, row, column, 0, len, a, s)) {
				found = 1;
				break;
			}
			else if (rightdiagonal(row_end, column_end, 0, len, a, s)) {
				found = 1;
				break;
			}
		}
		if (found == 1)
			break;
	}
}

int main() {
	char *a[] = { "abc", "def", "ghi" };
	char *s = "cf";
	int len = strlen(s);
	searchstr(a, 3, 3, len, s);
}