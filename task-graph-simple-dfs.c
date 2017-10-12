#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "util.h"
#include "darray.h"
#include "stack.h"

/* 
  http://www.geeksforgeeks.org/iterative-depth-first-traversal/
  
  Simple deep first graph traversal 

*/

struct sgraph
{
    int vertices;
    struct darray *adj[];
};

struct sgraph *sgraph_create(int vertices)
{
    struct sgraph *g = xmalloc(sizeof(*g)+sizeof(struct darray *[vertices]));
    
    g->vertices = vertices;

    for (int i=0; i<vertices; ++i)
    {
        if ( !(g->adj[i]=darray_create(16)) )
        {
            for (int j=i-1; j>=0; --j)
                darray_destroy(g->adj[j]);
                
            free(g);
            return 0;
        }
    }

    return g;
}

void sgraph_destroy(struct sgraph *g)
{
    for (int i=0; i<g->vertices; ++i)
        darray_destroy(g->adj[i]);

    free(g);
}

void sgraph_add_edge(struct sgraph *g, int from, int to)
{
    if (from >= g->vertices || to >= g->vertices)
        return;
    
    darray_add(g->adj[from], to);
}

void sgraph_dfs(struct sgraph *g, int start)
{
    bool *visited = xmalloc(sizeof(bool[g->vertices]));

    for (int i=0; i<g->vertices; ++i)
        visited[i] = false;
        
    struct stack *s = stack_create(4);

    stack_push(s, start);
    
    intptr_t cur;
    
    printf("DFS:");
    
    while (stack_pop(s, &cur))
    {
        if (visited[cur])
            continue;

        printf(" %d", (int)cur);
        visited[cur] = true;
        
        struct darray *adj = g->adj[cur];
        
        for (int i=0, len=darray_length(adj); i<len;  ++i)
        {
            int new_vertex = darray_get(adj, i);
            
            if (visited[new_vertex])
                continue;

            stack_push(s, new_vertex);
        }
    }
    printf("\n");
    
    stack_destroy(s);
    free(visited);
}

void test_1()
{
    struct sgraph *g = sgraph_create(5);

    sgraph_add_edge(g, 1, 0);
    sgraph_add_edge(g, 0, 2);
    sgraph_add_edge(g, 2, 1);
    sgraph_add_edge(g, 0, 3);
    sgraph_add_edge(g, 1, 4);
    
    sgraph_dfs(g, 0);
    
    sgraph_destroy(g);
}


int main(int argc, char *argv[])
{
    test_1();

    return 0;
}
