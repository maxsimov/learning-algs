#include <stdlib.h>
#include "graph.h"

struct graph_ops
{
    bool (*create) (struct graph *g, int capacity);
    void (*destroy)(struct graph *g);

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
    struct adjacency_list_edge *prev;
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
    int length;
    struct adjacency_list_vertex *vertex;
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
    struct graph_ops *ops;
    union graph_rep rep;
};

// dispatching methods

struct graph *graph_create(enum graph_type type, int capacity)
{
    struct graph *g = malloc(sizeof(*g));
    g->type = type;

    return 0;
}

void graph_destroy(struct graph *g)
{
    (*g->ops->destroy)(g);
    free(g);
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

