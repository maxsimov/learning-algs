#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "darray.h"

enum graph_type { adjacency_list, adjacency_matrix, incidence_matrix };

struct graph *graph_create(enum graph_type type, int capacity);
void graph_destroy(struct graph *g);

bool graph_adjacent(struct graph *g, int from, int to);
void graph_neighbors(struct graph *g, struct darray *neighbors);
void graph_add_vertex(struct graph *g, int vertex);
void graph_remove_vertex(struct graph *g, int x);
void graph_add_edge(struct graph *g, int from, int to);
void graph_remove_edge(struct graph *g, int from, int to);
uintptr_t graph_get_vertex_value(struct graph *g, int x);
void graph_set_vertex_value(struct graph *g, int x, uintptr_t value);
uintptr_t graph_get_edge_value(struct graph *g, int from, int to);
void graph_set_edge_value(struct graph *g, int from, int to, uintptr_t value);
