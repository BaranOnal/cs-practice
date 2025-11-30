#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int value;
    int priority;
} MinHeapNode;

typedef struct {
    MinHeapNode data[MAX_SIZE];
    int size;
} MinHeap;

// Initialize the heap
void initHeap(MinHeap* heap) {
    heap->size = 0;
}

// Get the index of the parent, left child, and right child
int parent(int i) {
    return (i - 1) / 2;
}
int leftChild(int i) {
    return 2 * i + 1;
}
int rightChild(int i) {
    return 2 * i + 2;
}

// Heapify the heap at a given index
void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < heap->size && heap->data[left].priority < heap->data[smallest].priority) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right].priority < heap->data[smallest].priority) {
        smallest = right;
    }

    if (smallest != i) {
        MinHeapNode temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;
        heapify(heap, smallest);
    }
}

// Enqueue: Insert a new element into the heap
void enqueue(MinHeap* heap, int value, int priority) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap overflow!\n");
        return;
    }

    heap->data[heap->size].value = value;
    heap->data[heap->size].priority = priority;
    int current = heap->size;
    heap->size++;

    // Move up to maintain heap property
    while (current > 0 && heap->data[current].priority < heap->data[parent(current)].priority) {
        MinHeapNode temp = heap->data[current];
        heap->data[current] = heap->data[parent(current)];
        heap->data[parent(current)] = temp;
        current = parent(current);
    }
}

// Dequeue: Remove and return the element with the highest priority (smallest priority value)
MinHeapNode dequeue(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap underflow!\n");
        return (MinHeapNode) { -1, -1 };
    }

    MinHeapNode root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    // Move down to maintain heap property
    heapify(heap, 0);

    return root;
}

// Print the heap
void printHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("(Value: %d, Priority: %d) ", heap->data[i].value, heap->data[i].priority);
    }
    printf("\n");
}

int main() {
    MinHeap heap;
    initHeap(&heap);

    enqueue(&heap, 10, 3);
    enqueue(&heap, 5, 1);
    enqueue(&heap, 20, 4);
    enqueue(&heap, 2, 0);

    printf("Heap: ");
    printHeap(&heap);

    MinHeapNode node = dequeue(&heap);
    printf("Dequeued: (Value: %d, Priority: %d)\n", node.value, node.priority);

    printf("Heap after dequeue: ");
    printHeap(&heap);

    return 0;
}
