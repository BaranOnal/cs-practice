#include <stdio.h>
#include <stdlib.h>

typedef struct node {

	char data;
	struct node* next;
	
}node;

void insert(node** f, char value);
void printList(node* currentNode);
char delete(node** f, char value);
int isEmpty(node* f);


int main() {

	node* firstNode = NULL;
	int choice = 0;
	char item = 0;

	printf("Enter your choice:\n"
		" 1 to insert an element into the list.\n"
		" 2 to delete an element from the list.\n"
		" 3 to end.\n");

	scanf_s("%d", &choice);

	while (choice != 3)
	{
		switch (choice){
		case 1:
			printf("Enter a character  ");
			scanf_s("\n%c", &item);
			insert(&firstNode, item);
			printList(firstNode);
			break;	
		case 2:
			if (!isEmpty(firstNode)) {

				printf("Enter character to be deleted: ");
				scanf_s("\n%c", &item);
				if (delete(&firstNode, item))
				{
					printf("%c deleted.\n", item);
					printList(firstNode);
				}
				else {

					printf("%c not found.\n\n", item);
				}
			}
			else
			{
				printf("List is empty.\n");
			}
			break;
		default:
			printf("Invalid choice.\n\n");
			break;
		}
		printf("Enter your choice:\n"
			" 1 to insert an element into the list.\n"
			" 2 to delete an element from the list.\n"
			" 3 to end.\n");

		scanf_s("%d", &choice);
	}
	return 0;
}

void insert(node** fNode, char value)
{
	node* newNode = NULL;
	node* previosNode = NULL;
	node* currentNode = NULL;

	newNode = (node*)malloc(sizeof(node));

	if (newNode != NULL)
	{
		newNode->data = value;
		newNode->next = NULL;
		previosNode = NULL;
		currentNode = *fNode;

		while (currentNode != NULL && value > currentNode->data)
		{
			previosNode = currentNode;
			currentNode = currentNode->next;
		}
		if (previosNode == NULL)
		{
			newNode->next = *fNode;
			*fNode = newNode;
		}
		else
		{
			previosNode->next = newNode;
			newNode->next = currentNode;
		}
	}
	else
	{
		printf("%c not inserted. No memory available.\n", value);
	}
}

void printList(node* currentNode)
{
	if (currentNode == NULL)
	{
		printf("List is empty.\n");
	}
	else
	{
		printf("*LIST*\n");
		while (currentNode != NULL)
		{
			printf("%c --> ", currentNode->data);
			currentNode = currentNode->next;
		}
		printf("NULL\n");
	}
}

char delete(node** f, char value) {


	node* previousNode = NULL;
	node* currentNode = NULL;
	node* tempNode = NULL;

	if (value == (*f)->data)
	{
		tempNode = *f;
		*f = (*f)->next;
		free(tempNode);

		return value;
	}
	else {
		previousNode = *f;
		currentNode = (*f)->next;

		while (value != currentNode->data)
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
		if (currentNode != NULL)
		{
			tempNode = currentNode;
			previousNode->next = currentNode->next;
			free(tempNode);
			return value;
		}

	}

	return '\0';
}


int isEmpty(node* f)
{
	return f == NULL;
}
