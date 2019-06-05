#include "iostream"
#include "stdlib.h"


using namespace std;

void printArray(int *a, int n,char *calInv) {
	for (int i = 0; i < n; i++)
		cout << calInv[a[i]];
	cout << endl;
}

void print(int *a, int idx, int n,char *calInv) {
	if (idx == n) {
		printArray(a, n,calInv);
		return;
	}
	for (int i = 0; i <= 9; i++) {
		a[idx] = i;
		print(a, idx + 1, n,calInv);
	}
}

int main() {
	int a[3];
	char calInv[10];
	calInv[0] = '0';
	calInv[1] = '1';
	calInv[2] = '2';
	calInv[3] = 'E';
	calInv[4] = 'h';
	calInv[5] = 'S';
	calInv[6] = '9';
	calInv[7] ='L';
	calInv[8] = '8';
	calInv[9] = '6';
	print(a, 0, 3,calInv);
}
