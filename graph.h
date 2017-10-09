#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "darray.h"

enum graph_type { adjacency_list, adjacency_matrix, incidence_matrix };

struct graph *graph_create(enum graph_type type, int capacity);
void graph_destroy(struct graph *g);
void graph_print(struct graph *g);

// tests whether there is an edge from the vertex x to the vertex y
bool graph_adjacent(struct graph *g, int from, int to);

// lists all vertices y such that there is an edge from the vertex x to the vertex y;
void graph_neighbors(struct graph *g, struct darray *neighbors);

//  adds the vertex x, if it is not there;
void graph_add_vertex(struct graph *g, int vertex);

// removes the vertex x, if it is there;
void graph_remove_vertex(struct graph *g, int x);

// adds the edge from the vertex x to the vertex y, if it is not there;
void graph_add_edge(struct graph *g, int from, int to);

// removes the edge from the vertex x to the vertex y, if it is there;
void graph_remove_edge(struct graph *g, int from, int to);

// returns the value associated with the vertex x;
uintptr_t graph_get_vertex_value(struct graph *g, int x);

// sets the value associated with the vertex x to v.
void graph_set_vertex_value(struct graph *g, int x, uintptr_t value);

// returns the value associated with the edge (x, y);
uintptr_t graph_get_edge_value(struct graph *g, int from, int to);

// sets the value associated with the edge (x, y) to v.
void graph_set_edge_value(struct graph *g, int from, int to, uintptr_t value);
