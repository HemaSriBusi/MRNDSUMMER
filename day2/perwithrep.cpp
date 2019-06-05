
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

bool shouldSwap(int *inp, int start, int cur) {
	for (int i = start; i < cur; i++) {
		if (inp[i] == inp[cur])
			return false;
	}
	return true;
}

void printArray(int *inp, int n) {
	for (int i = 0; i< n; i++)
		printf("%d", inp[i]);
	printf("\n");
}

void findPermutations(int *inp, int index, int n, int permute_idx) {
	if (index >= n) {
		printArray(inp, n);
	}
	for (int i = index; i < n; i++) {
		if (shouldSwap(inp, index, i)) {
			int temp = inp[index];
			inp[index] = inp[i];
			inp[i] = temp;
			findPermutations(inp, index + 1, n, permute_idx);
			int temp2 = inp[i];
			inp[i] = inp[index];
			inp[index] = temp2;
		}
	}
}


int main() {
	int a[] = { 1, 3, 5, 5 };
	findPermutations(a, 0, 4, 0);

	return 0;
}