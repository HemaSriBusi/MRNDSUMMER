#include "iostream"
#include "stdafx.h"

using namespace std;

int arr_sum(int *a,int n) {
	if (n == 0)
		return a[0];
	return a[n] + arr_sum(a, n - 1);
}

int main() {
	int *a = (int *)malloc(sizeof(int) * 5);
	a = { 1, 3, 4, 5 };
	printf("%d\n", arr_sum(a, 5));
}
