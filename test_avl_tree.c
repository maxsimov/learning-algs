#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

void test_1()
{
    printf("Print empty tree\n");
    
    struct avl_tree *tree = avl_tree_create();

    avl_tree_display(tree);
    avl_tree_destroy(tree);
}

static
void insert_helper(struct avl_tree *tree, int value)
{
    printf("Inserting %d\n", value);
    avl_tree_insert(tree, value, 0);
    avl_tree_display(tree);
}

void test_2()
{
    printf("Test insertion\n");
    
    struct avl_tree *tree = avl_tree_create();
    insert_helper(tree, 10);
    insert_helper(tree, 5);
    insert_helper(tree, 20);
    insert_helper(tree, 30);
    insert_helper(tree, 40);
    insert_helper(tree, 50);
    insert_helper(tree, 60);

    avl_tree_destroy(tree);
}


void test_3()
{
    printf("Generate random tree\n");
    
    struct avl_tree *tree = avl_tree_random(0x691AFED1, 100, -100, 100);

    avl_tree_display(tree);

    avl_tree_destroy(tree);
}


int main(int argc, char *argv[])
{
    test_1();
    test_2();
    test_3();
    
    return 0;
}
