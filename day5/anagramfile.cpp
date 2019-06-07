#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26
using namespace std;

struct Trie {
	struct Trie *child[26];
	bool leaf = false;
};


void insert(struct Trie *root, char *word) {
	printf("%s\n", word);
	for (int i = 0; word[i] != '\0'; i++) {
		int idx = word[i] - 97;
		if ( root->child[idx] == NULL) {
			root->child[idx] = (struct Trie *)malloc(sizeof(struct Trie));
		}
		root = root->child[idx];
	}
	root->leaf = true;
}

bool shouldSwap(char *inp, int start, int cur) {
	for (int i = start; i < cur; i++) {
		if (inp[i] == inp[cur])
			return false;
	}
	return true;
}

void isAnagram(char *word, struct Trie *root) {
	for (int i = 0; word[i] != '\0'; i++) {
		int idx = word[i] - 97;
		if (root->child[idx] == NULL)
			break;
		root = root->child[idx];
	}
	printf("%s\n", word);
}



void findPermutations(char *inp,int index,int n,struct Trie *root) {
	if (index >= n) {
		isAnagram(inp,root);
	}
	for (int i = index; i < n; i++) {
		if (shouldSwap(inp, index, i)) {
			int temp = inp[index];
			inp[index] = inp[i];
			inp[i] = temp;
			findPermutations(inp, index + 1, n,root);
			int temp2 = inp[i];
			inp[i] = inp[index];
			inp[index] = temp2;
		}
	}
}


int main() {
	struct Trie *root = (struct Trie *)malloc(sizeof(struct Trie));
	char line[20];
	FILE *fp = fopen("words.txt", "r");
	while (fscanf(fp, "%[^\n]%", line) == 1) {
		insert(root, line);
	}
	char *inp = (char *)malloc(sizeof(char) * 20);
	//scanf("%s", inp);
	inp = "abc";
	int n = strlen(inp);
	findPermutations(inp, 0, n,root);
	return 0;
}