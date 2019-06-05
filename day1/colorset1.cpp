#include "iostream"
#include "stdafx.h"

using namespace std;

void colorsort(int *a,int n) {
	int left = 0,right = n-1;
	while (left < right) {
		if (a[left] == 0 && a[right] == 0)
			left++;
		else if (a[left] == 1 && a[right] == 1)
			right--;
		else if (a[left] == 1 && a[right] == 0) {
			int temp = a[left];
			a[left] = a[right];
			a[right] = temp;
			left++;
			right--;
		}
		else {
			left++;
			right--;
		}
	}
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
}

int main() {
	int a[] = { 0, 1, 0, 0, 1, 1 };
	colorsort(a, 6);
}