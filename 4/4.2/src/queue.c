#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

Node *initNode(uint8_t priority, int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = data;
    newNode->priority = priority;
    return newNode;
}

Queue *initQueue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->head = NULL;
    return queue;
}

void enqueue(Queue *queue, uint8_t priority, int data)
{
    Node *newNode = initNode(priority, data);
    if (queue->head == NULL)
    {
        queue->head = newNode;
        return;
    }

    Node *tmp = queue->head;
    if (tmp->priority > newNode->priority)
    {
        newNode->next = queue->head;
        queue->head = newNode;
        return;
    }
    Node *prev = tmp;
    while (tmp->next != NULL && tmp->next->priority <= newNode->priority)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    newNode->next = tmp->next;
    tmp->next = newNode;
}

void dequeueFirst(Queue *queue)
{
    Node *tmp = queue->head;
    queue->head = tmp->next;
    printf("Priority: %d Data: %d\n", tmp->priority, tmp->data);
    free(tmp);
}

void dequeueByPriority(Queue *queue, uint8_t priority)
{
    Node *tmp = queue->head;
    Node *prev = tmp;
    while (tmp->priority != priority)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = tmp->next;
    printf("Priority: %d Data: %d\n", tmp->priority, tmp->data);
    free(tmp);
}

void dequeueHigherPriority(Queue *queue, uint8_t priority)
{
    Node *tmp = queue->head;
    while (tmp->next != NULL && tmp->priority <= priority)
    {
        dequeueFirst(queue);
        tmp = queue->head;
    }
}

void clearQueue(Queue *queue)
{
    Node *tmp = queue->head;
    while (queue->head != NULL)
    {
        dequeueFirst(queue);
    }
    free(queue);
}
