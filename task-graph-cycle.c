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
  http://www.geeksforgeeks.org/detect-cycle-in-a-graph/
  
  Detect Cycle in a Directed Graph
  
  Given a directed graph, check whether the graph contains a cycle or not. 
  Your function should return true if the given graph contains at least one cycle, 
  else return false. For example, the following graph contains three cycles
  0->2->0, 0->1->2->0 and 3->3, so your function must return true.

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

bool sgraph_is_cycle_from_vertex(struct sgraph *g, int start, 
                                 bool *visited, bool *path)
{
    if (visited[start])
        return false;

    visited[start] = true;
    path[start] = true;

    struct darray *adj = g->adj[start];
        
    for (int i=0, len=darray_length(adj); i<len;  ++i)
    {
        int new_vertex = darray_get(adj, i);
            
        if (!visited[new_vertex] && sgraph_is_cycle_from_vertex(g, new_vertex, visited, path))
            return true;
        else
            if (path[new_vertex])
                return true;
    }
    
    path[start] = false;

    return false;
}

bool sgraph_is_cycle(struct sgraph *g)
{
    bool *visited = xmalloc(sizeof(bool[g->vertices]));
    bool *path = xmalloc(sizeof(bool[g->vertices]));

    for (int i=0; i<g->vertices; ++i)
    {
        visited[i] = false;
        path[i] = false;
    }
    
    bool cycles = false;
    for (int i=0; i<g->vertices; ++i)
    {
        if (sgraph_is_cycle_from_vertex(g, i, visited, path))
        {
            cycles = true;
            break;
        }
    }

    free(path);
    free(visited);
    
    return cycles;
}

void is_cycle_worker(struct sgraph *g)
{
    if (sgraph_is_cycle(g)) printf("graph has cycle!\n");
     else printf("graph doesn't have cycle!\n");
}

void test_1()
{
    struct sgraph *g = sgraph_create(5);

    sgraph_add_edge(g, 1, 0);
    sgraph_add_edge(g, 0, 2);
    sgraph_add_edge(g, 2, 1);
    sgraph_add_edge(g, 0, 3);
    sgraph_add_edge(g, 1, 4);
    
    is_cycle_worker(g);
    
    sgraph_destroy(g);
}

void test_2()
{
    struct sgraph *g = sgraph_create(4);

    sgraph_add_edge(g, 0, 1);
    sgraph_add_edge(g, 0, 2);
    sgraph_add_edge(g, 1, 3);
    sgraph_add_edge(g, 2, 3);

    is_cycle_worker(g);
    
    sgraph_destroy(g);
}


int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}
