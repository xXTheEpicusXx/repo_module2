#include "queue.h"
#include <stdio.h>

int main()
{
    Queue *queue = initQueue();
    enqueue(queue, 1, 1);
    enqueue(queue, 254, 1);
    enqueue(queue, 0, 1);
    enqueue(queue, 44, 1);
    enqueue(queue, 10, 1);
    enqueue(queue, 1, 2);
    enqueue(queue, 12, 1);
    enqueue(queue, 55, 1);
    dequeueFirst(queue);
    dequeueByPriority(queue, 10);
    dequeueHigherPriority(queue, 50);
    printf("clearing\n");
    clearQueue(queue);

    return 0;
}
