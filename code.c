#include <stdio.h>
#include <stdlib.h>

struct QueueNode {
    int data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

void initializeQueue(struct Queue* queue) {
    queue->front = queue->rear = NULL;
}

void enqueue(struct Queue* queue, int value) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (newNode) {
        newNode->data = value;
        newNode->next = NULL;

        if (queue->front == NULL) {
            queue->front = queue->rear = newNode;
        } else {
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
    } else {
        // Handle memory allocation failure (if needed)
        fprintf(stderr, "Memory allocation error. Element not enqueued.\n");
    }
}

int dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        fprintf(stderr, "Queue is empty. Dequeue operation failed.\n");
        exit(1);
    } else {
        int frontValue = queue->front->data;
        struct QueueNode* temp = queue->front;

        if (queue->front == queue->rear) {
            queue->front = queue->rear = NULL;
        } else {
            queue->front = queue->front->next;
        }

        free(temp);
        return frontValue;
    }
}

void display(struct Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty.\n");
        return;
    } else {
        printf("Queue elements: ");
        struct QueueNode* current = queue->front;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    struct Queue q;
    initializeQueue(&q);

    int choice, value;

    while (1) {
        printf("\nQueue Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to enqueue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 2:
                if (q.front == NULL) {
                    printf("Queue is empty. Dequeue operation failed.\n");
                } else {
                    printf("Dequeued element: %d\n", dequeue(&q));
                }
                break;
            case 3:
                display(&q);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
