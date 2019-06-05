#include "iostream"
#include "stdlib.h"

using namespace std;

void printArray(int *a, int n) {
	for (int i = 0; i < n; i++)
		cout << a[i];
	cout << endl;
}

void printPermute(int *a, int n, int idx) {
	if (idx == n) {
		printArray(a, idx);
		return;
	}
	printPermute(a, n, idx + 1);
	for (int i = idx + 1; i < n; i++) {
		int temp = a[i];
		a[i] = a[idx];
		a[idx] = temp;
		printPermute(a, n, idx + 1);
		int temp2 = a[i];
		a[i] = a[idx];
		a[idx] = temp2;
	}
}

/*int main() {
	int a[3] = { 1, 3, 5 };
	printPermute(a, 3, 0);
}*/
