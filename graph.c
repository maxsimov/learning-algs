#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "graph.h"

struct graph_ops
{
    bool (*create) (struct graph *g, int capacity);
    void (*destroy)(struct graph *g);
    void (*print)(struct graph *g);

    bool (*adjacent)(struct graph *g, int from, int to);
    void (*neighbors)(struct graph *g, struct darray *neighbors);
    void (*add_vertex)(struct graph *g, int vertex);
    void (*remove_vertex)(struct graph *g, int x);
    void (*add_edge)(struct graph *g, int from, int to);
    void (*remove_edge)(struct graph *g, int from, int to);
    uintptr_t (*get_vertex_value)(struct graph *g, int x);
    void (*set_vertex_value)(struct graph *g, int x, uintptr_t value);
    uintptr_t (*get_edge_value)(struct graph *g, int from, int to);
    void (*set_edge_value)(struct graph *g, int from, int to, uintptr_t value);
};

// adjacency list
struct adjacency_list_edge
{
    struct adjacency_list_edge *next;
    int dst_vertex;
    uintptr_t edge_data;
};

struct adjacency_list_vertex
{
    struct adjacency_list_edge *edges;
    uintptr_t vertex_data;
};

struct adjacency_list_store
{
    int capacity;
    struct adjacency_list_vertex **vertex;
};

struct adjacency_matrix_store
{
    
};

struct incidence_matrix_store
{
};

union graph_rep
{
    struct adjacency_list_store adj_list;
    struct adjacency_matrix_store adj_matrix;
    struct incidence_matrix_store inc_matrix;
};

struct graph
{
    enum graph_type type;
    const struct graph_ops *ops;
    union graph_rep rep;
};


// 

bool adj_list_create(struct graph *g, int capacity)
{
    struct adjacency_list_store *adj = &g->rep.adj_list;
    
    adj->capacity = capacity;
    adj->vertex = malloc(capacity*sizeof(adj->vertex[0]));
    
    for (int i=0; i<capacity; ++i)
        adj->vertex[i] = 0;
    
    return true;
}

void adj_list_destroy(struct graph *g)
{
    struct adjacency_list_store *adj = &g->rep.adj_list;

    free(adj->vertex);
}

void adj_list_print(struct graph *g)
{
    struct adjacency_list_store *adj = &g->rep.adj_list;

    printf("{\n");
    printf("  capacity = %d\n", adj->capacity);
    printf("  vertexes = {");    
    for (int i=0; i<adj->capacity; ++i)
        if (adj->vertex[i])
            printf(" %d", i);
    printf(" }\n");   
    
    printf("  edges = {\n");    
    for (int i=0; i<adj->capacity; ++i)
        if (adj->vertex[i] && adj->vertex[i]->edges)
        {
            printf("   %d ->", i);
            for (struct adjacency_list_edge *edge=adj->vertex[i]->edges; edge; 
                 edge=edge->next)
            {
                printf(" %d", edge->dst_vertex);
            }
            printf("\n");
        }
    
    printf("  }\n");   
    
    printf("}\n");
}

bool adj_list_adjacent(struct graph *g, int from, int to)
{
    return true;
}

void adj_list_neighbors(struct graph *g, struct darray *neighbors)
{
    
}

void adj_list_add_vertex(struct graph *g, int vertex)
{
    struct adjacency_list_store *adj = &g->rep.adj_list;
    
    if (vertex < 0)
        return;
    
    if (vertex >= adj->capacity)
    {
        int ratio = vertex / adj->capacity;
        int new_capacity = (ratio + 1)*adj->capacity;
        assert(new_capacity > adj->capacity);
        
        adj->vertex = realloc(adj->vertex, new_capacity*sizeof(adj->vertex[0]));
        for (int i=adj->capacity; i<new_capacity; ++i)
            adj->vertex[i] = 0;
        adj->capacity = new_capacity;
    }
    
    struct adjacency_list_vertex *v = adj->vertex[vertex];
    
    if (!v)
    {
        v = malloc(sizeof(*v));
        v->edges = 0;
        v->vertex_data = 0;
        
        adj->vertex[vertex] = v;
    }
}

void adj_list_remove_vertex(struct graph *g, int x)
{

}

void adj_list_add_edge(struct graph *g, int from, int to)
{
    struct adjacency_list_store *adj = &g->rep.adj_list;

    if (from < 0 || from >= adj->capacity)
        return;

    struct adjacency_list_vertex *v = adj->vertex[from];
    
    if (!v)
        return;
        
    struct adjacency_list_edge *edge = v->edges;

    while (edge)
    {
        if (edge->dst_vertex == to)
            return;
        if (!edge->next)
            break;
        edge = edge->next;
    }
    
    struct adjacency_list_edge *newedge = malloc(sizeof(*newedge));
    
    newedge->dst_vertex = to;
    newedge->next = 0;
    newedge->edge_data = 0;
    
    if (edge)
        edge->next = newedge;
    else
        v->edges = newedge;
}

void adj_list_remove_edge(struct graph *g, int from, int to)
{
    
}

uintptr_t adj_list_get_vertex_value(struct graph *g, int x)
{
    return 0;
}

void adj_list_set_vertex_value(struct graph *g, int x, uintptr_t value)
{
    
}

uintptr_t adj_list_get_edge_value(struct graph *g, int from, int to)
{
    return 0;
}

void adj_list_set_edge_value(struct graph *g, int from, int to, uintptr_t value)
{
    
}

static const struct graph_ops adj_list_ops = 
{
    .create = adj_list_create,
    .destroy = adj_list_destroy,
    .print = adj_list_print,
    .adjacent = adj_list_adjacent,
    .neighbors = adj_list_neighbors,
    .add_vertex = adj_list_add_vertex,
    .remove_vertex = adj_list_remove_vertex,
    .add_edge = adj_list_add_edge,
    .remove_edge = adj_list_remove_edge,
    .get_vertex_value = adj_list_get_vertex_value,
    .set_vertex_value = adj_list_set_vertex_value,
    .get_edge_value = adj_list_get_edge_value,
    .set_edge_value = adj_list_set_edge_value
} ;

static
const struct graph_ops *get_ops_by_type(enum graph_type type)
{
    switch (type)
    {
        case adjacency_list:
        return &adj_list_ops;
        
        default:
        return 0;
    }
}

// dispatching methods

struct graph *graph_create(enum graph_type type, int capacity)
{
    struct graph *g = malloc(sizeof(*g));
    g->type = type;
    g->ops = get_ops_by_type(type);
    
    if (!g->ops || !(g->ops->create)(g, capacity))
    {
        free(g);
        return 0;
    }

    return g;
}

void graph_destroy(struct graph *g)
{
    (*g->ops->destroy)(g);
    free(g);
}

void graph_print(struct graph *g)
{
    (*g->ops->print)(g);
}

bool graph_adjacent(struct graph *g, int from, int to)
{
    return (*g->ops->adjacent)(g, from, to);
}

void graph_neighbors(struct graph *g, struct darray *neighbors)
{
    (*g->ops->neighbors)(g, neighbors);
}

void graph_add_vertex(struct graph *g, int vertex)
{
    (*g->ops->add_vertex)(g, vertex);
}

void graph_remove_vertex(struct graph *g, int x)
{
    (*g->ops->remove_vertex)(g, x);
}

void graph_add_edge(struct graph *g, int from, int to)
{
    (*g->ops->add_edge)(g, from, to);
}

void graph_remove_edge(struct graph *g, int from, int to)
{
    (*g->ops->remove_edge)(g, from, to);
}

uintptr_t graph_get_vertex_value(struct graph *g, int x)
{
    return (*g->ops->get_vertex_value)(g, x);
}

void graph_set_vertex_value(struct graph *g, int x, uintptr_t value)
{
    (*g->ops->set_vertex_value)(g, x, value);
}

uintptr_t graph_get_edge_value(struct graph *g, int from, int to)
{
    return (*g->ops->get_edge_value)(g, from, to);
}

void graph_set_edge_value(struct graph *g, int from, int to, uintptr_t value)
{
    (*g->ops->set_edge_value)(g, from, to, value);
}

