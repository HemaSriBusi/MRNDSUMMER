#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void bubblesort(int *arr,int n) {
	for (int i = 0; i < n-1; i++) {   
        for (int j = 0; j < n-i-1; j++)  {
            if (arr[j] > arr[j+1])  {
           		int temp = arr[j];
           		arr[j] = arr[j+1];
           		arr[j+1] = arr[j];
		   }
	}	
}
}

int main() {
	int a[] = {1,0,0,1};
	bubblesort(a,4);
	for ( int i = 0; i < 4;i++)
		cout<<a[i]<<' ';
	cout<<endl;
	return 0;
}
