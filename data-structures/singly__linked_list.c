#include <stdio.h>
#include <stdlib.h>

typedef struct linkedList
{
	int info;
	struct linkedList* next;
}singly_list;


singly_list* first = NULL;
singly_list* last = NULL;
//singly_list * p = NULL;


void addNode(int data);

singly_list* search(int key);

singly_list* delete(int key);

void printList();

int main() {
	addNode(45);
	addNode(5);
	addNode(11);
	printList();

	//printf("%d\n", search(11)->info);

	delete(45);

	printList();
	return 0;
}



void addNode(int data)
{
	singly_list* p = (singly_list*)malloc(sizeof(singly_list));


	if (first == NULL)
	{
		p->info = data;
		p->next = NULL;
		first = last = p;
	}
	else {
		p->info = data;
		p->next = NULL;
		last->next = p;
		last = p;
	}
}

singly_list* search(int key)
{
	singly_list* p;

	p = first;

	while (p)
	{
		if (key=p->info)
			return p;
		
		p = p->next;
	}

	return NULL;
}

singly_list* delete(int key) {

	singly_list* p, * previous;

	p = first;
	previous = NULL;

	if (p == NULL) { exit(1); }


	while (p)
	{
		if (key == p->info)
			break;
		previous = p;
		p = p->next;
	}


	if (p != NULL)
	{
		if (previous == NULL)
		{
			if (first->next == NULL)
			{
				first = NULL;
				last = NULL;
			}
			else
				first = first->next;
		}
		else
		{
			previous->next = p->next;
			if (previous->next == NULL)
			{
				last = previous;
			}
		}
		

		free(p);
		return p;
	}
	else
		return NULL;

	
}


void printList() {
	singly_list* p = first;
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