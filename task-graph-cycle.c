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

bool sgraph_is_cycle_from_vertex_it(struct sgraph *g, int start, 
                                 bool *visited, bool *path)
{
    if (visited[start])
        return false;

    struct stack *s = stack_create(4);
    bool ret = false;
    
    path[start] = true;
    stack_push(s, start);
    stack_push(s, g->vertices);

    stack_push(s, start);
    
    intptr_t cur;
    bool back_track = false;
    
    while (stack_pop(s, &cur))
    {
        if (back_track)
        {
            path[cur] = false;
            back_track = false;
            continue;
        }
        
        if (cur == g->vertices)
        {
            back_track = true;
            continue;
        }
        
        if (visited[cur])
        {
            if (!path[cur])
                continue;

            ret = true;
            break;
        }
        
        visited[cur] = true;
        
        path[cur] = true;
        stack_push(s, cur);
        stack_push(s, g->vertices);
        
        struct darray *adj = g->adj[cur];
        
        for (int i=0, len=darray_length(adj); i<len;  ++i)
        {
            int vtx = darray_get(adj, i);
            stack_push(s, vtx);
        }
    }

    stack_destroy(s);
    return ret;
}

bool sgraph_is_cycle(struct sgraph *g, bool it)
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
        bool rt;

        if (it) rt = sgraph_is_cycle_from_vertex_it(g, i, visited, path);
         else rt = sgraph_is_cycle_from_vertex(g, i, visited, path); 
        
        if (rt)
        {
            cycles = true;
            break;
        }
    }

    free(path);
    free(visited);
    
    return cycles;
}

enum  VCOLOR { WHITE, GREY, BLACK };

bool sgraph_is_cycle_colors_it(struct sgraph *g, enum VCOLOR *colors, int start)
{
    struct stack *s = stack_create(4);
    bool cycles = false;

    stack_push(s, start);    
    
    bool change_color = false;
    intptr_t cur;
    while (stack_pop(s, &cur))
    {
        if (change_color)
        {
            colors[cur] = BLACK;
            change_color = false;
            continue;
        }
        
        if (cur == g->vertices)
        {
            change_color = true;
            continue;
        }
        
        if (colors[cur] == BLACK)
            continue;
            
        if (colors[cur] ==  GREY)
        {
            cycles = true;
            break;
        }
        
        colors[cur] = GREY;
        stack_push(s, cur);    
        stack_push(s, g->vertices);
        
        struct darray *adj = g->adj[cur];
        
        for (int i=0, len=darray_length(adj); i<len;  ++i)
            stack_push(s, darray_get(adj, i));
    }
    
    stack_destroy(s);
    return cycles;
}

bool sgraph_is_cycle_colors(struct sgraph *g)
{
    enum VCOLOR *colors = xmalloc(sizeof(enum VCOLOR[g->vertices]));

    for (int i=0; i<g->vertices; ++i)
        colors[i] = WHITE;

    bool cycles = false;

    for (int i=0; i<g->vertices; ++i)
    {
        if (sgraph_is_cycle_colors_it(g, colors, i))
        {
            cycles = true;
            break;
        }
    }

    free(colors);

    return cycles;
}

void is_cycle_worker(struct sgraph *g)
{
    if (sgraph_is_cycle(g, false)) printf("Recursion: graph has cycle!\n");
     else printf("Recursion: graph doesn't have cycle!\n");
    
    if (sgraph_is_cycle(g, true)) printf("Iteration: graph has cycle!\n");
     else printf("Iteration: graph doesn't have cycle!\n");
     
    if (sgraph_is_cycle_colors(g)) printf("Colors: graph has cycle!\n");
     else printf("Colors: graph doesn't have cycle!\n");
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
