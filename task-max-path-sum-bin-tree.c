#include <stdio.h>
#include <stdio.h>
#include <assert.h>
#include "bin-tree.h"
#include "deque.h"

/* 
  http://www.geeksforgeeks.org/find-maximum-path-sum-in-a-binary-tree/
  
  Given a binary tree, find the maximum path sum. 
  The path may start and end at any node in the tree.

*/

struct find_max_result
{
    struct deque max_path;
    int max_path_sum;
};

static
void find_max_result_init(struct find_max_result *r)
{
    deque_init(&r->max_path);
    r->max_path_sum = 0;
}

static
void find_max_result_cleanup(struct find_max_result *r)
{
    deque_cleanup(&r->max_path);
}

void update_max_path(struct find_max_result *result, struct find_max_result *local)
{
    if (deque_empty(&local->max_path))
        return;
        
    if (deque_empty(&result->max_path) || result->max_path_sum < local->max_path_sum)
    {
        deque_copy(&result->max_path, &local->max_path);
        result->max_path_sum = local->max_path_sum;
    }
}

void add_path(struct bin_tree *tree, struct find_max_result *result, struct find_max_result *local)
{
    if (deque_empty(&local->max_path))
    {
        deque_push_front_ptr(&local->max_path, tree);
        local->max_path_sum = tree->key;
        update_max_path(result, local);
        return;
    }

    int new_path_sum = local->max_path_sum + tree->key;
    
    if (new_path_sum > tree->key)
    {
        deque_push_front_ptr(&local->max_path, tree);
        local->max_path_sum = new_path_sum;
        update_max_path(result, local);
    } else {
        deque_clear(&local->max_path);
        deque_push_front_ptr(&local->max_path, tree);
        local->max_path_sum = tree->key;
        update_max_path(result, local);
    }
}

void find_max_path_sum(struct bin_tree *tree, struct find_max_result *result, struct find_max_result *local)
{
    assert( deque_empty(&local->max_path) );
    
    if (!tree->left)
    {
        if (tree->right)
            find_max_path_sum(tree->right, result, local);

        add_path(tree, result, local);
        return;
    }

    if (!tree->right)
    {
        if (tree->left)
            find_max_path_sum(tree->left, result, local);
        
        add_path(tree, result, local);
        return;
    }

    struct find_max_result left_result, right_result;
    
    find_max_result_init(&left_result);
    find_max_result_init(&right_result);
    
    find_max_path_sum(tree->left, result, &left_result);
    find_max_path_sum(tree->right, result, &right_result);
    
    assert( !deque_empty(&left_result.max_path) );
    assert( !deque_empty(&right_result.max_path) );

    int connection_sum = left_result.max_path_sum + right_result.max_path_sum + tree->key;
    if (connection_sum > result->max_path_sum)
    {
        result->max_path_sum = connection_sum;
        
        deque_copy(&result->max_path, &left_result.max_path);
        deque_push_front_ptr(&result->max_path, tree);
        
        struct deque temp;
        deque_init(&temp);
        deque_copy(&temp, &right_result.max_path);
        
        void *ptr;
        while (deque_pop_front_ptr(&temp, &ptr))
            deque_push_back_ptr(&result->max_path, ptr);
        
        deque_cleanup(&temp);
    }
    
    if (left_result.max_path_sum < right_result.max_path_sum)
        deque_copy(&local->max_path, &right_result.max_path);
    else
        deque_copy(&local->max_path, &left_result.max_path);

    add_path(tree, result, local);

    find_max_result_cleanup(&right_result);
    find_max_result_cleanup(&left_result);
}

void find_max_exec(struct bin_tree *tree, const char *msg)
{
    printf("Finding max sum in %s\n", msg);
    bin_tree_display(tree);

    struct find_max_result result, local;

    find_max_result_init(&result);
    find_max_result_init(&local);
    find_max_path_sum(tree, &result, &local);
    
    printf("Max path sum = %d\n", result.max_path_sum);
    
    printf("Path:");
    struct bin_tree *node = 0;
    while (deque_pop_front_ptr(&result.max_path, (void **)&node))
        printf(" %d", node->key);
    printf("\n");
    
    find_max_result_cleanup(&result);
    find_max_result_cleanup(&local);
}

void test_1()
{
    struct bin_tree *tree;
    
    tree = bin_tree_create(5, 0);
    tree->left = bin_tree_create(2, 0);
        tree->left->right = bin_tree_create(1, 0);
    tree->right = bin_tree_create(6, 0);
    
    find_max_exec(tree, "Find max path sum in simple tree ...");

    bin_tree_destroy(tree);
}

void test_2()
{
    struct bin_tree *tree = bin_tree_random2(0xAEFE89AE, 10, -10, 10);

    find_max_exec(tree, "Find max path sum in random tree 2 ...");
    bin_tree_destroy(tree);
}

void test_3()
{
    struct bin_tree *tree = bin_tree_random2(0xAEFE89AE, 100, -100, 100);

    find_max_exec(tree, "Find max path sum in random tree 3...");
    bin_tree_destroy(tree);
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();
    test_3();

    return 0;
}
