#include "stdafx.h"
#include "stdlib.h"
#include "iostream"



using namespace std;

struct node {
	int data;
	struct node* next;
};

/*struct node * CN(int data) {
	struct node *newnode = (struct node *)malloc(sizeof(struct node));
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}*/



struct node * reverse(struct node *head) {
	struct node *prev = (struct node *)malloc(sizeof(struct node));
	prev = NULL;
	struct node *next = (struct node *)malloc(sizeof(struct node));
	next = NULL;
	while (head != NULL){
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}
	return prev;
}

void kreverse(struct node *root,int k) {
	struct node *next = (struct node *)malloc(sizeof(struct node));
	struct node *prev = (struct node *)malloc(sizeof(struct node));
	struct node *newroot = (struct node *)malloc(sizeof(struct node));
	struct node *curr = (struct node *)malloc(sizeof(struct node));
	int flag = 1;
	while (root != NULL) {
		int temp = k;
		prev = root;
		while (temp > 1 && root != NULL) {
			root = root->next;
			temp--;
		}
		if (temp == 1) {
			next = root->next;
			root->next = NULL;
			struct node *t = reverse(prev);
			if (flag) {
				newroot = t;
				flag = 0;
			}
			else
				curr->next = t;
		}
		else if (temp != 1) {
			curr->next = prev;
			break;
		}
		curr = prev;
		root = next;
	}
	while (newroot != NULL) {
		cout << newroot->data << ' ';
		newroot = newroot->next;
	}
}

/*int main() {
	int a[] = { 1, 2, 3, 4, 5, 6 };
	int k = 3;
	struct node *head = NULL;
	struct node *root = NULL;
	for (int i = 0; i < 6; i++) {
		if (head == NULL) {
			head = CN(a[i]);
			root = head;
		}
		else {
			head->next = CN(a[i]);
			head = head->next;
		}
	}
	kreverse(root, k);
	return 0;
}*/