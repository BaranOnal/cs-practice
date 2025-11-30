#include <stdio.h>
#include <stdlib.h>


typedef struct linkedList
{
	int info;
	struct linkedList* previous;
	struct linkedList* next;
}doubly_list;



doubly_list* first = NULL;
doubly_list* last = NULL;



void addNode(int data);

doubly_list* delete(int data);
doubly_list* search(int data);

void printList();

int main() {
	addNode(45);
	addNode(5);
	addNode(11);

	delete(45);

	printList();
	return 0;
}

void addNode(int data)
{
	doubly_list* p = (doubly_list*)malloc(sizeof(doubly_list));

	if (first == NULL)
	{
		p->info = data;
		p->next = NULL;
		p->previous = NULL;
		first = last = p;
	}
	else
	{
		p->info = data;
		p->next = NULL;
		p->previous = last;
		last->next = p;
		last = p;
	}

}

doubly_list* delete(int data)
{

}

doubly_list* search(int data)
{	
	doubly_list* p;
	p = first;
	while (p) {
		if (p->info == data)
			return p;
		p = p->next;
	}
	return NULL;
}




void printList() {
	doubly_list* p = first;
	int i = 0;
	while (p != NULL)
	{
		printf(" %d -->", p->info);

		p = p->next;
		i = 1;
	}
	if (i == 1)
		printf(" NULL\n");

	else
		printf("List is empty!");
}