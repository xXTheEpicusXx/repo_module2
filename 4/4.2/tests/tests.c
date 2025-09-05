#include "../unity/unity.h"
#include "../src/queue.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_initQueue(void)
{
    Queue *queue = initQueue();
    TEST_ASSERT_NOT_NULL(queue);
    TEST_ASSERT_NULL(queue->head);
    free(queue);
}

void test_enqueue_basic(void)
{
    Queue *queue = initQueue();

    enqueue(queue, 5, 100);
    TEST_ASSERT_NOT_NULL(queue->head);
    TEST_ASSERT_EQUAL(5, queue->head->priority);
    TEST_ASSERT_EQUAL(100, queue->head->data);

    enqueue(queue, 3, 200);
    TEST_ASSERT_EQUAL(3, queue->head->priority);
    TEST_ASSERT_EQUAL(200, queue->head->data);

    clearQueue(queue);
}

void test_enqueue_priority_order(void)
{
    Queue *queue = initQueue();

    enqueue(queue, 5, 100);
    enqueue(queue, 3, 200);
    enqueue(queue, 7, 300);
    enqueue(queue, 1, 400);

    TEST_ASSERT_EQUAL(1, queue->head->priority);
    TEST_ASSERT_EQUAL(400, queue->head->data);

    TEST_ASSERT_EQUAL(3, queue->head->next->priority);
    TEST_ASSERT_EQUAL(200, queue->head->next->data);

    TEST_ASSERT_EQUAL(5, queue->head->next->next->priority);
    TEST_ASSERT_EQUAL(100, queue->head->next->next->data);

    TEST_ASSERT_EQUAL(7, queue->head->next->next->next->priority);
    TEST_ASSERT_EQUAL(300, queue->head->next->next->next->data);

    clearQueue(queue);
}

void test_dequeueFirst(void)
{
    Queue *queue = initQueue();

    enqueue(queue, 5, 100);
    enqueue(queue, 3, 200);
    enqueue(queue, 7, 300);

    dequeueFirst(queue);
    TEST_ASSERT_EQUAL(5, queue->head->priority);
    TEST_ASSERT_EQUAL(100, queue->head->data);

    dequeueFirst(queue);
    TEST_ASSERT_EQUAL(7, queue->head->priority);
    TEST_ASSERT_EQUAL(300, queue->head->data);

    clearQueue(queue);
}

void test_dequeueByPriority(void)
{
    Queue *queue = initQueue();

    enqueue(queue, 5, 100);
    enqueue(queue, 3, 200);
    enqueue(queue, 7, 300);
    enqueue(queue, 5, 400);

    dequeueByPriority(queue, 5);
    TEST_ASSERT_EQUAL(3, queue->head->priority);
    TEST_ASSERT_EQUAL(200, queue->head->data);

    TEST_ASSERT_EQUAL(5, queue->head->next->priority);
    TEST_ASSERT_EQUAL(400, queue->head->next->data);

    clearQueue(queue);
}

void test_dequeueHigherPriority(void)
{
    Queue *queue = initQueue();

    enqueue(queue, 5, 100);
    enqueue(queue, 3, 200);
    enqueue(queue, 7, 300);
    enqueue(queue, 2, 400);
    enqueue(queue, 8, 500);

    dequeueHigherPriority(queue, 4);

    TEST_ASSERT_EQUAL(5, queue->head->priority);
    TEST_ASSERT_EQUAL(100, queue->head->data);

    TEST_ASSERT_EQUAL(7, queue->head->next->priority);
    TEST_ASSERT_EQUAL(300, queue->head->next->data);

    TEST_ASSERT_EQUAL(8, queue->head->next->next->priority);
    TEST_ASSERT_EQUAL(500, queue->head->next->next->data);

    clearQueue(queue);
}

void test_clearQueue(void)
{
    Queue *queue = initQueue();

    enqueue(queue, 5, 100);
    enqueue(queue, 3, 200);
    enqueue(queue, 7, 300);

    clearQueue(queue);
    TEST_PASS();
}

void test_enqueue_same_priority(void)
{
    Queue *queue = initQueue();

    enqueue(queue, 5, 100);
    enqueue(queue, 5, 200);
    enqueue(queue, 5, 300);

    TEST_ASSERT_EQUAL(5, queue->head->priority);
    TEST_ASSERT_EQUAL(100, queue->head->data);

    TEST_ASSERT_EQUAL(5, queue->head->next->priority);
    TEST_ASSERT_EQUAL(200, queue->head->next->data);

    TEST_ASSERT_EQUAL(5, queue->head->next->next->priority);
    TEST_ASSERT_EQUAL(300, queue->head->next->next->data);

    clearQueue(queue);
}

void test_comprehensive(void)
{
    Queue *queue = initQueue();

    enqueue(queue, 10, 1);
    enqueue(queue, 5, 2);
    enqueue(queue, 15, 3);
    enqueue(queue, 5, 4);
    enqueue(queue, 20, 5);

    TEST_ASSERT_EQUAL(5, queue->head->priority);
    TEST_ASSERT_EQUAL(2, queue->head->data);

    TEST_ASSERT_EQUAL(5, queue->head->next->priority);
    TEST_ASSERT_EQUAL(4, queue->head->next->data);

    dequeueFirst(queue);
    TEST_ASSERT_EQUAL(5, queue->head->priority);
    TEST_ASSERT_EQUAL(4, queue->head->data);

    dequeueByPriority(queue, 10);
    TEST_ASSERT_EQUAL(5, queue->head->priority);
    TEST_ASSERT_EQUAL(4, queue->head->data);
    TEST_ASSERT_EQUAL(15, queue->head->next->priority);

    clearQueue(queue);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_initQueue);
    RUN_TEST(test_enqueue_basic);
    RUN_TEST(test_enqueue_priority_order);
    RUN_TEST(test_dequeueFirst);
    RUN_TEST(test_dequeueByPriority);
    RUN_TEST(test_dequeueHigherPriority);
    RUN_TEST(test_clearQueue);
    RUN_TEST(test_enqueue_same_priority);
    RUN_TEST(test_comprehensive);

    return UNITY_END();
}
