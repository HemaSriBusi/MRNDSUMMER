#include "iostream"
#include "stdlib.h"
#include "stdio.h"
using namespace std;

struct node {
	int data;
	struct node* next;
};

struct node * CN(int data) {
	struct node *newnode = (struct node *)malloc(sizeof(struct node));
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}

struct node *loopdetect(struct node *head) {
	if (head == NULL)
		return NULL;
	struct node *slow_ptr = head;
	struct node *fast_ptr = head;
	while (slow_ptr != NULL && fast_ptr != NULL && fast_ptr->next != NULL) {
		slow_ptr = slow_ptr->next;
		fast_ptr = fast_ptr->next->next;
		if (slow_ptr == fast_ptr)
			return slow_ptr;	
	}
	return NULL;
}


int main() {
	struct node *head = CN(2);
	head->next = CN(4);
	head->next->next = CN(3);
	head->next->next->next = CN(7);
	head->next->next->next->next = head->next;
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp = head;
	struct node *commonPoint = loopdetect(head);
	while ( commonPoint != NULL && head != NULL ) {
		if ( commonPoint == head )
			break;
		commonPoint = commonPoint->next;
		head = head->next;
	}
	printf("%d\n",commonPoint->data);
	return 0;
}

