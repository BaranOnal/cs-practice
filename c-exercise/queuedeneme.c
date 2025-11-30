#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}node;

node* front = NULL;
node* rear = NULL;

void enqueue(int data) {

	if(front == NULL)
	{
		node* new = (node*)malloc(sizeof(node));
		new->data = data;
		new->next = NULL;

		front = rear = new;

	}
	else
	{
		node* new = (node*)malloc(sizeof(node));
		new->data = data;
		new->next = NULL;

		
		rear->next = new;
		rear = new;
	}

}

void display() {

	if (front == NULL)
	{
		printf("List is empty");
	}
	else
	{
		node* index = front;
		while (index != NULL)
		{
			printf(" %d -->", index->data);
			index = index->next;
		}
		printf(" NULL\n");
	}

}

int main() {

	enqueue(5);
	enqueue(4);
	enqueue(3);
	enqueue(9);

	display();

	return 0;
}