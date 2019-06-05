#include "stdio.h"
#include "stdafx.h"
#include "iostream"
using namespace std;

void strcompress(char *s) {
	int start = 0;
	int end = 1;
	int idx = 0;
	while (end <= strlen(s)) {
		if (s[start] != s[end]) {
			s[idx++] = s[start];
			if (end - start < 9 && end - start > 1) {
				s[idx++] = end - start + '0';
			}
			else if (end - start > 1){
				int len = end - start;
				int temp = len;
				long long int dig = 1;
				while (temp > 1) {
					dig *= 10;
					temp = temp / 10;
				}
				while (len > 0) {
					s[idx++] = (len / dig) + '0';
					len = len % dig;
					dig = dig / 10;
				}
			}
			start = end;
			end++;
		}
		else
			end++;
	}
	s[idx] = '\0';
}

/*int main() {
	char s[30] = "aaaaabbaaaabcd";
	strcompress(s);
	printf("%s\n", s);
	return 0;
}*/