#include "stdafx.h"
#include "stdlib.h"
#include "iostream"
using namespace std;

struct node {
	int data;
	struct node *next;
	struct node *random;
};

struct node *createNode(int data) {
	struct node *newnode = (struct node *)malloc(sizeof(struct node));
	newnode->data = data;
	newnode->next = NULL;
	newnode->random = NULL;
	return newnode;
}

void removelinks(struct node *clone_head, struct node *root) {
	struct node *next = NULL;
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp = root;
	struct node *clonetemp = clone_head;
	while (root->next != NULL && clone_head->next != NULL) {
		next = root->next->next;
		if (clone_head->next->next != NULL)
			clone_head->next = clone_head->next->next;
		if (root->random != NULL)
			clone_head->random = root->random->next;
		root->next = next;
		root = root->next;
		clone_head = clone_head->next;
	}
	root->next = NULL;
	clone_head = clonetemp;

	while (temp != NULL) {
		if (temp->random != NULL)
			cout << temp->data << temp->random->data << endl;
		else
			cout << temp->data << endl;
		temp = temp->next;
	}
	cout << endl;
	while (clone_head != NULL) {
		if (clone_head->random != NULL)
			cout << clone_head->data << clone_head->random->data << endl;
		else
			cout << clone_head->data << endl;
		clone_head = clone_head->next;
	}
}

void clonell(struct node *root) {
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	struct node *clone_head = (struct node *)malloc(sizeof(struct node));
	temp = root;
	int flag = 1;
	while (root != NULL)  {
		struct node *clone = createNode(root->data);
		if (flag) {
			clone_head = clone;
			flag = 0;
		}
		clone->next = root->next;
		root->next = clone;
		root = clone->next;
	}
	removelinks(clone_head, temp);
}

/*int main() {
	struct node *root = createNode(1);
	root->next = createNode(2);
	root->next->next = root->random = createNode(3);
	root->next->next->next = root->next->random = createNode(4);
	clonell(root);
	return 0;
}*/