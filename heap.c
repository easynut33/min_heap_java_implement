#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

void init_heap(MinHeap *heap);
void free_heap(MinHeap *heap);
void resize_heap(MinHeap *heap);
void swap(int *a, int *b);
void push(MinHeap *heap, int value);
int pop(MinHeap *heap);

int main(void)
{
    int n;
    int value;
    MinHeap heap;

    printf("=== Minimum Heap Program ===\n");
    printf("Enter a positive number to insert it into the heap.\n");
    printf("Enter 0 to remove and print the smallest number.\n\n");
    printf("Enter the number of operations (n): ");

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    init_heap(&heap);

    printf("Enter %d value(s):\n", n);

    for (int i = 0; i < n; i++) {
        printf("%d/%d > ", i + 1, n);
        scanf("%d", &value);

        if (value == 0) {
            printf("Minimum value: %d\n", pop(&heap));
        } else {
            push(&heap, value);
        }
    }

    free_heap(&heap);
    return 0;
}

void init_heap(MinHeap *heap)
{
    heap->size = 0;
    heap->capacity = INITIAL_CAPACITY;
    heap->data = malloc(sizeof(int) * (heap->capacity + 1));

    if (heap->data == NULL) {
        exit(EXIT_FAILURE);
    }
}

void free_heap(MinHeap *heap)
{
    free(heap->data);
}

void resize_heap(MinHeap *heap)
{
    int new_capacity = heap->capacity * 2;
    int *new_data = realloc(heap->data, sizeof(int) * (new_capacity + 1));

    if (new_data == NULL) {
        free_heap(heap);
        exit(EXIT_FAILURE);
    }

    heap->data = new_data;
    heap->capacity = new_capacity;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap *heap, int value)
{
    int child;

    if (heap->size == heap->capacity) {
        resize_heap(heap);
    }

    heap->size++;
    child = heap->size;
    heap->data[child] = value;

    while (child > 1) {
        int parent = child / 2;

        if (heap->data[parent] <= heap->data[child]) {
            break;
        }

        swap(&heap->data[parent], &heap->data[child]);
        child = parent;
    }
}

int pop(MinHeap *heap)
{
    int result;
    int parent;

    if (heap->size == 0) {
        return 0;
    }

    result = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    parent = 1;

    while (parent * 2 <= heap->size) {
        int left = parent * 2;
        int right = left + 1;
        int smaller = left;

        if (right <= heap->size && heap->data[right] < heap->data[left]) {
            smaller = right;
        }

        if (heap->data[parent] <= heap->data[smaller]) {
            break;
        }

        swap(&heap->data[parent], &heap->data[smaller]);
        parent = smaller;
    }

    return result;
}
