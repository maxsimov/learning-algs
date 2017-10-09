#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "queue.h"

/* 
  http://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/
  
  Simple breadth first graph traversal 
*/

struct sgraph
{
    int vertices;
    int matrix[];
};

struct sgraph *sgraph_create(int vertices)
{
    int vertices_size = sizeof(int[vertices][vertices]);
    struct sgraph *g = malloc(sizeof(*g) + vertices_size);
    
    if (!g)
        return 0;
    
    g->vertices = vertices;
    memset(g->matrix, 0, vertices_size);
    
    return g;
}

void sgraph_destroy(struct sgraph *g)
{
    free(g);
}

void sgraph_bfs(struct sgraph *g, int start)
{
    bool *visited = malloc(sizeof(bool[g->vertices]));
    int (*m)[g->vertices] = (void *)g->matrix;

    for (int i=0; i<g->vertices; ++i)
        visited[i] = false;
        
    struct queue *q = queue_create(4);

    queue_enque(q, start);
    
    intptr_t cur;
    
    printf("BFS:");
    
    while (queue_deque(q, &cur))
    {
        if (visited[cur])
            continue;
        printf(" %d", (int)cur);
        visited[cur] = true;
        for (int j=0; j<g->vertices; ++j)
            if (!visited[j] && m[cur][j])
            {
                queue_enque(q, j);
            }
    }
    printf("\n");
    
    queue_destroy(q);
    free(visited);
}

void test_1()
{
    struct sgraph *g = sgraph_create(8);
    int (*m)[g->vertices] = (void *)g->matrix;

    m[0][1] = 1;
    m[0][2] = 1;
    m[1][2] = 1;
    m[2][0] = 1;
    m[2][3] = 1;
    m[3][3] = 1;

    sgraph_bfs(g, 2);
    
    sgraph_destroy(g);
}

void test_2()
{
    struct sgraph *g = sgraph_create(8);
    int (*m)[g->vertices] = (void *)g->matrix;
    
    m[0][1] = 1;
    m[0][4] = 1;
    m[1][0] = 1;
    m[1][2] = 1;
    m[1][3] = 1;
    m[1][4] = 1;
    m[2][1] = 1;
    m[2][3] = 1;
    m[3][1] = 1;
    m[3][2] = 1;
    m[3][4] = 1;
    m[4][0] = 1;
    m[4][1] = 1;
    m[4][3] = 1;
    
    sgraph_bfs(g, 2);
    
    sgraph_destroy(g);
}

int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}
