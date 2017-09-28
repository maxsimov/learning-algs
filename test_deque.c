#include <stdio.h>
#include "deque.h"

void dump_element(union deque_item *item)
{
    printf ("%d", item->value);
}

void test_1()
{
    struct deque que;
    int data;
    
    deque_init(&que);

    printf("Queue tests\n");
    
    printf("1. Empty\n");
    deque_dump(&que, &dump_element);
    
    printf("2. push_back 5\n");
    deque_push_back_int(&que, 5);
    deque_dump(&que, &dump_element);
    
    printf("3. pop_front 5\n");
    deque_pop_front_int(&que, &data);
    deque_dump(&que, &dump_element);

    printf("4. push_back 7 8\n");
    deque_push_back_int(&que, 7);
    deque_push_back_int(&que, 8);
    deque_dump(&que, &dump_element);

    printf("5. pop_front 7\n");
    deque_pop_front_int(&que, &data);
    deque_dump(&que, &dump_element);

    printf("6. pop_front 8\n");
    deque_pop_front_int(&que, &data);
    deque_dump(&que, &dump_element);

    printf("7. push_back 1 2 3 4 5\n");
    deque_push_back_int(&que, 1);
    deque_push_back_int(&que, 2);
    deque_push_back_int(&que, 3);
    printf(" 1 2 3: h=%d t=%d c=%d\n", que.head, que.tail, que.capacity);
    deque_push_back_int(&que, 4);
    printf(" ..4: h=%d t=%d c=%d\n", que.head, que.tail, que.capacity);
    deque_push_back_int(&que, 5);
    printf(" ..5: h=%d t=%d c=%d\n", que.head, que.tail, que.capacity);
    deque_dump(&que, &dump_element);

    printf("8. pop_front 1\n");
    deque_pop_front_int(&que, &data);
    printf(" 1 ..: h=%d t=%d c=%d\n", que.head, que.tail, que.capacity);
    deque_dump(&que, &dump_element);
    deque_pop_front_int(&que, &data);
    printf(" 2 ..: h=%d t=%d c=%d\n", que.head, que.tail, que.capacity);
    deque_dump(&que, &dump_element);
    deque_pop_front_int(&que, &data);
    printf(" 3 ..: h=%d t=%d c=%d\n", que.head, que.tail, que.capacity);
    deque_dump(&que, &dump_element);

    deque_cleanup(&que);

    printf("\n");
}

void test_2()
{
    struct deque que;
    int data;
    
    deque_init(&que);

    printf("Stack tests\n");
    
    printf("1. Empty\n");
    deque_dump(&que, &dump_element);
    
    printf("2. push_front 8\n");
    deque_push_front_int(&que, 8);
    deque_dump(&que, &dump_element);
    
    printf("3. pop_front 8 = ");
    deque_pop_front_int(&que, &data);
    printf("%d\n", data);
    deque_dump(&que, &dump_element);

    printf("4. push_front 7 8\n");
    deque_push_front_int(&que, 7);
    deque_push_front_int(&que, 8);
    deque_dump(&que, &dump_element);

    printf("5. pop_front 8 = ");
    deque_pop_front_int(&que, &data);
    printf("%d\n", data);
    deque_dump(&que, &dump_element);

    printf("6. pop_front 7 = ");
    deque_pop_front_int(&que, &data);
    printf("%d\n", data);
    deque_dump(&que, &dump_element);

    printf("7. push_front 1 2 3 4 5\n");
    deque_push_front_int(&que, 1);
    deque_push_front_int(&que, 2);
    deque_push_front_int(&que, 3);
    printf(" 1 2 3: h=%d t=%d c=%d\n", que.head, que.tail, que.capacity);
    deque_push_front_int(&que, 4);
    printf(" ..4: h=%d t=%d c=%d\n", que.head, que.tail, que.capacity);
    deque_push_front_int(&que, 5);
    printf(" ..5: h=%d t=%d c=%d\n", que.head, que.tail, que.capacity);
    deque_dump(&que, &dump_element);

    printf("8. pop_front 5\n");
    deque_pop_front_int(&que, &data);
    printf(" 5 ..: h=%d t=%d c=%d value=%d\n", que.head, que.tail, que.capacity, data);
    deque_dump(&que, &dump_element);

    deque_pop_front_int(&que, &data);
    printf(" 4 ..: h=%d t=%d c=%d value=%d\n", que.head, que.tail, que.capacity, data);
    deque_dump(&que, &dump_element);
    deque_pop_front_int(&que, &data);
    printf(" 3 ..: h=%d t=%d c=%d value=%d\n", que.head, que.tail, que.capacity, data);
    deque_dump(&que, &dump_element);

    deque_cleanup(&que);

    printf("\n");
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();
    
    return 0;
}
