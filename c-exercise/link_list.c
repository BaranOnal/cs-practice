#include <stdio.h>
#include <stdlib.h>

typedef struct node {

    struct node* next;

    char key;

}node;

void fill_list(node** p_first);
void print_list(node* p_first);
void delete_char(node** p_first, char mykey);


int main()
{
    node* first = NULL;

    fill_list(&first);

    print_list(first);

    putchar('\n');

    delete_char(&first, getchar());
    print_list(first);

    return 0;
}

void fill_list(node** p_first) {

    char key0 = '0';

    node* previous = NULL;
    node* head = NULL;

    if (*p_first != NULL) { exit(1); }

    while (1) {

        key0 = getchar();

        if (key0 == '\n') {

            break;
        }

        if (*p_first == NULL) {

            *p_first = (node*)malloc(sizeof(node)); if (*p_first == NULL) { exit(1); }
            (*p_first)->key = key0;
            (*p_first)->next = NULL;
            previous = (*p_first);

        }

        else {

            head = (node*)malloc(sizeof(node)); if (head == NULL) { exit(1); }
            previous->next = head;
            head->key = key0;
            head->next = NULL;
            previous = head;

        }

    }


}

void print_list(node* first) {

    node* head = first;

    while (head) {

        putchar(head->key);
        head = head->next;

    }

}

void delete_char(node** p_first, char mykey) {

    node* previous = NULL;
    node* current = *p_first;
    node* temp = NULL;

    if (current == NULL) { printf("List is empty.\n"); return; }

    while (current != NULL) {

        if (current == *p_first && current->key == mykey) {

            temp = *p_first;
            *p_first = (*p_first)->next;
            free(temp);
            current = *p_first;
        }

        else if (current->key == mykey) {

            temp = current;
            previous->next = current->next;
            free(temp);
            current = previous->next;

        }

        else {

            previous = current;
            current = current->next;
        }

    }

}
