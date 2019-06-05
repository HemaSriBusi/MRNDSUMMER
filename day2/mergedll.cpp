#include "iostream"
#include "stdafx.h"

using namespace std;

struct node {
	int data;
	struct node *right;
	struct node *left;
};

void split(struct node *head, struct node *first, struct node *last) {
	struct node *slow = (struct node *)malloc(sizeof(struct node));
	struct node *fast = (struct node *)malloc(sizeof(struct node));
	slow = head;
	fast = head->right;
	while (fast != NULL) {
		fast = fast->right;
		if (fast != NULL) {
			slow = slow->right;
			fast = fast->right;
		}
	}
	first = head;
	last = slow->right;
	slow->right = NULL;
}

struct node *mergesort(struct node *start, struct node *last) {
	if (start == NULL)
		return last;
	if (last == NULL)
		return start;
	struct node *temp = NULL;
	if (start->data < last->data) {
		temp = start;
		temp = mergesort(start->right, last);
	}
	if (last->data < start->data) {
		temp = last;
		temp = mergesort(start, last->right);
	}
	return temp;
}

struct node * merge(struct node *head) {
	if (head == NULL)
		return;
	struct node *start = (struct node *)malloc(sizeof(struct node));
	struct node *last = (struct node *)malloc(sizeof(struct node));
	split(head, start, last);
	start = merge(start);
	last = merge(last);
	head = mergesort(start, last);
	return head;
}