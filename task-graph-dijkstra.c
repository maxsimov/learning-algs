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
  http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
  
  Given a graph and a source vertex in graph, 
  find shortest paths from source to all vertices in the given graph.
*/

struct edge
{
    int weight;
    int v;
};

struct adj
{
    int capacity;
    int E;
    struct edge edges[];
};

struct sgraph
{
    int V;
    struct adj *adj[];
};

struct sgraph *sgraph_create(int V)
{
    struct sgraph *g = xmalloc(sizeof(*g)+sizeof(struct adj *[V]));
    
    g->V = V;
    for (int i=0; i<V; ++i)
        g->adj[i] = 0;

    return g;
}

void sgraph_destroy(struct sgraph *g)
{
   for (int i=0; i<g->V; ++i)
        free(g->adj[i]);
    free(g);
}

void sgraph_add_edge(struct sgraph *g, int from, int to, int weight)
{
    if (from >= g->V || to >= g->V)
        return;
    
    if (g->adj[from])
    {
        if (g->adj[from]->E >= g->adj[from]->capacity)
        {
            int new_capacity = g->adj[from]->capacity*2;
            g->adj[from] = xrealloc(g->adj[from], sizeof(struct adj)+sizeof(struct edge [new_capacity]));
            g->adj[from]->capacity = new_capacity;
        }
    } else {
        const int def_capacity = 4;
        g->adj[from] = xmalloc(sizeof(struct adj)+sizeof(struct edge [def_capacity]));
        g->adj[from]->capacity = def_capacity;
        g->adj[from]->E = 0;
    }
    
    struct edge *edge = &g->adj[from]->edges[g->adj[from]->E++];
    
    edge->weight = weight;
    edge->v = to;
}

struct path_step
{
    int parent;
    int weight;
};

struct path
{
    int V;
    struct path_step steps[];
};

struct path *path_create(int V)
{
    struct path *path = xmalloc(sizeof(*path) + sizeof(struct path_step [V]));
    path->V = V;

    return path;
}

void path_destroy(struct path *path)
{
    free(path);
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int min_distance(int dist[], bool sptSet[], int V)
{
   // Initialize min value
   int min = INT_MAX, min_index;
  
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
  
   return min_index;
}

struct path *dijkstra(struct sgraph *g, int start)
{
    bool *spt_set = xmalloc(sizeof(bool[g->V]));
    int *dist = xmalloc(sizeof(int[g->V]));
    struct path *path = path_create(g->V);
    
    for (int i=0; i<g->V; ++i)
        spt_set[i] = false, dist[i] = INT_MAX, path->steps[i].parent = -1;
        
    dist[start] = 0;
    
    for (int count=0; count<g->V; count++)
    {
        int u = min_distance(dist, spt_set, g->V);
        
       spt_set[u] = true;
       
        struct adj *adj=g->adj[u];
        if (adj)
        {
            for (int e=0; e<adj->E; ++e)
            {
                struct edge *edge = &adj->edges[e];
            
                if (!spt_set[edge->v] && dist[u] != INT_MAX 
                                           && (dist[u]+edge->weight) < dist[edge->v])
                {
                    dist[edge->v] = dist[u] + edge->weight;
                    path->steps[edge->v].parent = u;
                    path->steps[edge->v].weight = edge->weight;
                }
            }
        }
    }
    
    free(dist);
    free(spt_set);
    
    return path;
}

void path_calc(char *msg, struct sgraph *g, int start, int end)
{
    printf("Path for graph:\n");

    for (int i=0; i<strlen(msg); ++i)
    {
        switch (msg[i])
        {
            case '`': msg[i] = '\\'; break;
        }
    }

    printf("%s", msg);

    struct path *path = dijkstra(g, start);

    printf("Path(%d-%d): (path will be displayed in reverse order)\n", start, end);
    
    int w = 0;
    for (int c=end; c!=-1; c=path->steps[c].parent)
    {
        printf(" %d",c);
        w += path->steps[c].weight;
    }
    printf("\n");
    printf("Path weight %d\n", w);
    
    path_destroy(path);
}

void test_1()
{
    struct sgraph *g = sgraph_create(9);

    char text[] =
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
    
    path_calc(text, g, 0, 4);
    
    sgraph_destroy(g);
}

void test_2()
{
    struct sgraph *g = sgraph_create(6);

    char text[] =
"            18         \n"
"        1-------2      \n"
"       /         `     \n"
"    10/           ` 17 \n"
"     /             `   \n"
"    0               3  \n"  
"     `             /   \n"
"     1`           /100 \n"
"       `         /     \n"
"        5-------4      \n"
"            2          \n";

    sgraph_add_edge(g, 0, 1, 10);
    sgraph_add_edge(g, 1, 2, 18);
    sgraph_add_edge(g, 2, 3, 17);
    sgraph_add_edge(g, 0, 5, 1);
    sgraph_add_edge(g, 5, 4, 2);
    sgraph_add_edge(g, 4, 3, 100);

    path_calc(text, g, 0, 3);
    
    sgraph_destroy(g);
}


int main(int argc, char *argv[])
{
    test_1();
    test_2();

    return 0;
}
