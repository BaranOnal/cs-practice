#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* next;

}node;

bool exits = 0;

void push(node** top, int data) {

	if (*top == NULL)
	{
		node* new = (node*)malloc(sizeof(node));

		new->data = data;
		new->next = NULL;

		*top = new;
	}
	else
	{
		node* new = (node*)malloc(sizeof(node));

		new->data = data;
		new->next = *top;

		*top = new;

	}

}

void printList(node* top) {
	node* index = top;

	
	while (index != NULL)
	{
		printf(" %d -->", index->data);

		index = index->next;
	}
	printf(" NULL\n");

}

int pop(node** top) {

	if (*top == NULL)
	{
		printf("Empty");
		exit(1);
	}

	node* temp;

	temp = *top;
	*top = (*top)->next;
	free(temp);
	return 1;
}

int main() {
	
	node* top = NULL;

	printList(top);

	push(&top,5);
	push(&top,3);
	push(&top,5);
	push(&top,1);
	push(&top,68);

	printList(top);

	pop(&top);
	pop(&top);
	pop(&top);
	pop(&top);
	pop(&top);
	pop(&top);
	pop(&top);
	pop(&top);
	pop(&top);

	printList(top);

}