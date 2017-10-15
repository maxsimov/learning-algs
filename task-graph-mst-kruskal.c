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
  http://www.geeksforgeeks.org/?p=26604
  
    What is Minimum Spanning Tree?
    Given a connected and undirected graph, a spanning tree of that graph is 
    a subgraph that is a tree and connects all the vertices together. 
    A single graph can have many different spanning trees. A minimum spanning 
    tree (MST) or minimum weight spanning tree for a weighted, connected and 
    undirected graph is a spanning tree with weight less than or equal to 
    the weight of every other spanning tree. The weight of a spanning tree is 
    the sum of weights given to each edge of the spanning tree.

    How many edges does a minimum spanning tree has?
    A minimum spanning tree has (V – 1) edges where V is the number of 
    vertices in the given graph.

    Below are the steps for finding MST using Kruskal’s algorithm

    1. Sort all the edges in non-decreasing order of their weight.

    2. Pick the smallest edge. Check if it forms a cycle with the spanning tree 
    formed so far. If cycle is not formed, include this edge. Else, discard it.  

    3. Repeat step#2 until there are (V-1) edges in the spanning tree.
*/

struct edge
{
    int x;
    int y;
    int weight;
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
    
    g->edges = xmalloc(sizeof(struct edge [V]));
    g->V = V;
    g->E = 0;
    g->M = V;

    return g;
}

void sgraph_destroy(struct sgraph *g)
{
    free(g->edges);
    free(g);
}

void sgraph_add_edge(struct sgraph *g, int x, int y, int weight)
{
    if (x >= g->V || y >= g->V)
        return;
        
    if (g->E >= g->M)
    {
        g->M = g->M*2;
        g->edges = realloc(g->edges, sizeof(struct edge [g->M]));
    }
    
    struct edge *e = &g->edges[g->E++];
    e->x = x;
    e->y = y;
    e->weight = weight;
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

static inline
int get_child(int i)
{
    return 2*i+1;
}

static inline
int get_parent(int i)
{
    return (i-1)/2;
}

void sift_down(struct edge *edges, int E, int root)
{
    for (int child=get_child(root); child < E; child=get_child(root))
    {
        int swap_index = root;
        
        if (edges[swap_index].weight < edges[child].weight)
            swap_index = child;
            
        ++child;
        if (child < E && edges[swap_index].weight < edges[child].weight)
            swap_index = child;
            
        if (root == swap_index)
            break;
            
        SWAP(edges[swap_index], edges[root]);
        root = swap_index;
    }
}

void heapify(struct edge *edges, int E)
{
    for (int i=get_parent(E-1); i>=0; --i)
       sift_down(edges, E, i); 
}

void heap_sort(struct edge *edges, int E)
{
    heapify(edges, E);

    for (int i=E-1; i>0; --i)
    {
        SWAP(edges[i], edges[0]);
        sift_down(edges, i, 0);
    }
}

struct sgraph *mst_kruskal(struct sgraph *g)
{
    struct subset *subset = xmalloc(sizeof(struct subset *[g->V]));
    
    for (int i=0; i<g->V; ++i)
    {
        subset[i].rank = 0;
        subset[i].parent = i;
    }

    heap_sort(g->edges, g->E);

    int edges = 0;
    struct sgraph *r = sgraph_create(g->V);
    
    for (int i=0; i<g->E; ++i)
    {
        if (uf_union(subset, g->edges[i].x, g->edges[i].y))
        {
            sgraph_add_edge(r, g->edges[i].x, g->edges[i].y, g->edges[i].weight);
            if (++edges == (g->V-1))
                break;
        }
    }
    
    free(subset);
    
    return r;
}

void test_1()
{
    struct sgraph *g = sgraph_create(9);

    const char text[] =
"           8      7          \n"
"        1-----2-------3      \n"
"       /|     |\\      |\\    \n"
"     4/ |    2| \\     | \\9  \n"
"     /  |     |  \\4   |  \\  \n"
"    0   |11   8   \\   |14 4  \n"  
"     \\  |    /|    \\  |  /   \n"
"     8\\ |  /7 |6    \\ | /10  \n"
"       \\|/    |      \\|/     \n"
"        7-----6-------5      \n"
"           1      2          \n";

    printf("MST fro graph:\n");
    printf("%s", text);

    sgraph_add_edge(g, 0, 1, 4);
    sgraph_add_edge(g, 1, 2, 8);
    sgraph_add_edge(g, 2, 3, 7);
    sgraph_add_edge(g, 3, 4, 9);
    sgraph_add_edge(g, 4, 5, 10);
    sgraph_add_edge(g, 5, 6, 2);
    sgraph_add_edge(g, 6, 7, 1);
    sgraph_add_edge(g, 7, 0, 8);
    sgraph_add_edge(g, 1, 7, 11);
    sgraph_add_edge(g, 7, 8, 7);
    sgraph_add_edge(g, 2, 8, 2);
    sgraph_add_edge(g, 8, 6, 6);
    sgraph_add_edge(g, 2, 5, 4);
    sgraph_add_edge(g, 3, 5, 14);

    struct sgraph *r = mst_kruskal(g);
    
    if (r)
    {
        printf("MST:\n");
        for (int i=0; i<r->E; ++i)
            printf(" %d <-> %d (%d)\n", r->edges[i].x, r->edges[i].y, r->edges[i].weight);
        sgraph_destroy(r);
    } else 
        printf("MST failed!\n");

    sgraph_destroy(g);
}

int main(int argc, char *argv[])
{
    test_1();

    return 0;
}
