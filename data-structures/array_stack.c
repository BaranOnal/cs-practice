#include <stdio.h>
#define N 10

int S[N];
int sp = 0;

int push(int item) {
    if (sp >= N) {
        printf("List is full!\n");
        return -1;
    }
    else {
        S[sp] = item;
        sp++;
        return 0;
    }
}

int pop() {
    if (sp <= 0) {
        printf("List is empty!\n");
        return -1;
    }
    else {
        sp--;
        return S[sp];
    }
}

void reset() {
    sp = 0;
}

int top() {
    if (sp > 0)
        return S[sp - 1];
    else {
        printf("List is empty!\n");
        return -1;
    }
}

int size() {
    return sp;
}

int isEmpty() {
    return sp == 0;
}

int main() {
    char c;
    while ((c = getchar()) != '\n') {
        push(c);
    }

    while (sp > 0) {
        printf("%c", pop());
    }

    printf("\n");7

    return 0;
}