#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

void test_queue_1()
{
    struct queue *q = queue_create(4);

    printf("Trivial test, enqueue 1 2 3\n");

    queue_enque(q, 1);
    queue_enque(q, 2);
    queue_enque(q, 3);
    queue_print(q);

    queue_destroy(q);
}

void test_queue_2()
{
    struct queue *q = queue_create(4);
    intptr_t value;

    printf("Trivial test 2, enqueue 1 2 3, deque and enque 4\n");

    queue_enque(q, 1);
    queue_enque(q, 2);
    queue_enque(q, 3);
    
    if (queue_deque(q, &value))
        printf("dequeued %d\n", (int)value);
    queue_enque(q, 4);

    queue_print(q);

    queue_destroy(q);
}

void test_queue_3()
{
    struct queue *q = queue_create(4);
    intptr_t value;

    printf("Trivial test 3, enqueue 1 2 3, deque and enque 4 5\n");

    queue_enque(q, 1);
    queue_enque(q, 2);
    queue_enque(q, 3);
    
    if (queue_deque(q, &value))
        printf("dequeued %d\n", (int)value);
    queue_enque(q, 4);
    queue_enque(q, 5);

    queue_print(q);

    queue_destroy(q);
}

/*
void test_darray_3()
{
    struct darray *a = darray_create(16);
    
    const int defseed = 0x71AFDE51;
    const int maxnum = 1670232;

    printf("inserting %d items\n", maxnum);
    srandom(defseed);
    for (int i=0; i<maxnum; ++i)
        darray_add(a, random());
    printf("verify %d items\n", maxnum);
    srandom(defseed);
    for (int i=0; i<maxnum; ++i)
        if (darray_get(a, i) != random())
            {
                printf(" ! FAILED!\n");
                return;
            }
    printf("all %d values are correct!\n", maxnum);

    darray_destroy(a);
}

void test_darray_4()
{
    struct darray *a = darray_create(16);

    printf("darrary test 4\n");
    for (int i=0; i<17; ++i)
        darray_add(a, i);
    printf(" "); darray_dump(a); printf("\n");
    darray_truncate(a, 7);
    printf(" "); darray_dump(a); printf("\n");

    darray_destroy(a);
}
*/

int main(int argc, char *argv[])
{
    test_queue_1();
    test_queue_2();
    test_queue_3();

    return 0;
}
