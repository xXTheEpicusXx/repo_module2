#include "stdint.h"
typedef struct Node Node;

typedef struct Node
{
    uint8_t priority;
    int data;
    Node *next;
} Node;

typedef struct Queue
{
    Node *head;
} Queue;

Node *initNode(uint8_t priority, int data);
Queue *initQueue();
void enqueue(Queue *queue, uint8_t priority, int data);
void dequeueFirst(Queue *queue);
void dequeueByPriority(Queue *queue, uint8_t priority);
void dequeueHigherPriority(Queue *queue, uint8_t priority);
void clearQueue(Queue *queue);
