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
  http://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
  
  Detect Cycle in a Undirected Graph
  using union-find algorithm
*/

struct edge
{
    int x;
    int y;
};

struct sgraph
{
    int V;
    int E;
    int M;
    struct edge *edges;
};

struct sgraph *sgraph_create(int V)
{
    struct sgraph *g = xmalloc(sizeof(*g));
    
    g->edges = 0;
    g->V = V;
    g->E = 0;
    g->M = 0;

    return g;
}

void sgraph_destroy(struct sgraph *g)
{
    free(g->edges);
    free(g);
}

void sgraph_add_edge(struct sgraph *g, int x, int y)
{
    if (x >= g->V || y >= g->V)
        return;
        
    if (g->E >= g->M)
    {
        if (!g->M) g->M = 4;
         else g->M = g->M*2;
        g->edges = realloc(g->edges, sizeof(struct edge *[g->M]));
    }
    
    struct edge *e = &g->edges[g->E++];
    e->x = x;
    e->y = y;
}

struct subset
{
    int rank;
    int parent;
};

int uf_find(struct subset *subset, int e)
{
    int parent = subset[e].parent;
    
    while (parent != subset[parent].parent)
        parent = subset[parent].parent;
        
    subset[e].parent = parent;

    return parent;
}

bool uf_union(struct subset *subset, int x, int y)
{
    int px = uf_find(subset, x);
    int py = uf_find(subset, y);

    if (px == py)
        return false;
        
    if (subset[px].rank > subset[py].rank)
        subset[py].parent = px;
    else if (subset[px].rank < subset[py].rank)
        subset[px].parent = py;
    else {
        subset[py].parent = px;
        subset[px].rank++;
    }
    
    return true;
}

bool sgraph_is_cycle(struct sgraph *g)
{
    struct subset *subset = xmalloc(sizeof(struct subset *[g->V]));
    
    for (int i=0; i<g->V; ++i)
    {
        subset[i].rank = 0;
        subset[i].parent = i;
    }
    
    bool cycle = false;
    
    for (int i=0; i<g->E; ++i)
    {
        if (!uf_union(subset, g->edges[i].x, g->edges[i].y))
        {
            cycle = true;
            break;
        }
    }
    
    free(subset);

    return cycle;
}

void is_cycle_worker(struct sgraph *g)
{
    if (sgraph_is_cycle(g)) printf("UnionFind: graph has cycle!\n");
     else printf("UnionFind: graph doesn't have cycle!\n");
}

void test_1()
{
    struct sgraph *g = sgraph_create(5);

/*
        0---------- 3
      /   \
    /      \
   1--------2
   |
   |
   |
   4
*/

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
    struct sgraph *g = sgraph_create(5);

/*
        0---------- 3
      /   \
    /      \
   1        2
   |
   |
   |
   4
*/

    sgraph_add_edge(g, 1, 0);
    sgraph_add_edge(g, 0, 2);
    sgraph_add_edge(g, 0, 3);
    sgraph_add_edge(g, 1, 4);
    
    is_cycle_worker(g);
    
    sgraph_destroy(g);
}

void test_3()
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
    test_3();

    return 0;
}
