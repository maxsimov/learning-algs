#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

void test_graph_1()
{
    struct graph *g = graph_create(adjacency_list, 16);

    printf("graph test 1 (empty)\n");
    graph_print(g);

    graph_destroy(g);
}

void test_graph_2()
{
    struct graph *g = graph_create(adjacency_list, 16);

    printf("graph test 1 (2)\n");
    graph_add_vertex(g, 2);
    graph_print(g);

    graph_destroy(g);
}

void test_graph_3()
{
    struct graph *g = graph_create(adjacency_list, 16);

    printf("graph test 1 (2 3 4 5)\n");
    graph_add_vertex(g, 2);
    graph_add_vertex(g, 3);
    graph_add_vertex(g, 4);
    graph_add_vertex(g, 5);
    graph_print(g);

    graph_destroy(g);
}

void test_graph_4()
{
    struct graph *g = graph_create(adjacency_list, 16);

    printf("graph test 1 (16)\n");
    graph_add_vertex(g, 16);
    graph_print(g);

    graph_destroy(g);
}

void test_graph_5()
{
    struct graph *g = graph_create(adjacency_list, 16);

    printf("graph test 1 (1 3 6)\n");
    graph_add_vertex(g, 1);
    graph_add_vertex(g, 3);
    graph_add_vertex(g, 6);
    graph_add_edge(g, 1, 3);
    graph_add_edge(g, 3, 6);
    graph_add_edge(g, 6, 1);
    graph_print(g);

    graph_destroy(g);
}


int main(int argc, char *argv[])
{
    test_graph_1();
    test_graph_2();
    test_graph_3();
    test_graph_4();
    test_graph_5();

    return 0;
}
