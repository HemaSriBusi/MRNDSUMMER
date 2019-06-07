#include"stdafx.h"
#include<stdio.h>
#include <stdlib.h>

using namespace std;

void printSort(int range) {
	FILE *fp;
	fp = fopen("input.txt", "r");
	bool *num = (bool *)calloc(sizeof(bool),100000);
	int i = 0;
	int low = range,high = range + 100000; 
	int val;
	while (i < 100000) {
		fscanf(fp, "%d\n", &val);
		int val_idx = val - low;
		if ( val_idx >= 0 && val_idx < 100000)
			num[val_idx] = true;
		i++;
	}
	for (int i = 0; i < 100000; i++) {
		if (num[i] == true)
			printf("%d\t", i + low);
	}
	fclose(fp);
}

/*int main() {
	int i = 0;
	int range = 0;
	while (i < 10) {
		printSort(range);
		range += 100000;
	}
	return 0;
}*/