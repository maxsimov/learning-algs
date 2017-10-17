#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "darray.h"
#include "stack.h"

/* 
  http://www.geeksforgeeks.org/a-search-algorithm/
  
  To approximate the shortest path in real-life situations, 
  like- in maps, games where there can be many hindrances.

  We can consider a 2D Grid having several obstacles and we start from 
  a source cell (coloured green below) to reach towards a goal cell 
  (coloured red below)
*/


struct cell
{
    int x;
    int y;
};

struct cell_path
{
    int len;
    struct cell path[];
};

int estimate_distance(struct cell start, struct cell end)
{
    int dx = start.x-end.x;
    int dy = start.y-end.y;
    
    return sqrt(dx*dx+dy*dy);
}

int distance(struct cell start, struct cell end)
{
    int dx = start.x-end.x;
    int dy = start.y-end.y;
    
    return sqrt(dx*dx+dy*dy);
}

void explore_path(struct cell cur, struct cell pt, struct cell end,
                  int N, int map[N][N],
                  bool visited[N][N], int g_dist[N][N],
                  int f_dist[N][N], struct cell parent[N][N])
{
    if (pt.x < 0 || pt.x >= N || pt.y < 0 || pt.y >= N)
        return;

    if (visited[pt.x][pt.y])
        return;
        
    if (map[pt.x][pt.y] != 0)
        return;
    
    int new_gdist = g_dist[cur.x][cur.y] + distance(cur, pt);
    int new_fdist = new_gdist + estimate_distance(pt, end);
    
    if (new_gdist >= g_dist[pt.x][pt.y])
        return;
        
    f_dist[pt.x][pt.y] = new_fdist;
    g_dist[pt.x][pt.y] = new_gdist;
    parent[pt.x][pt.y] = cur;
}

struct cell_path *find_path(int N, int map[N][N], 
                            struct cell start, struct cell end)
{
    if (start.x < 0 || start.x >= N || start.y < 0 || start.y >= N)
        return 0;
    if (end.x < 0 || end.x >= N || end.y < 0 || end.y >= N)
        return 0;
    if (start.x == end.x && start.y == end.y)
        return 0;
        
    bool visited[N][N];
    int g_dist[N][N];
    int f_dist[N][N];
    struct cell parent[N][N];
    
    for (int i=0; i<N; ++i)
        for (int j=0; j<N; ++j)
        {
            visited[i][j] = false;
            g_dist[i][j] = INT_MAX;
            f_dist[i][j] = INT_MAX;
            parent[i][j] = (struct cell) {x: INT_MAX, y: INT_MAX};
        }
        
    g_dist[start.x][start.y] = 0;
    f_dist[start.x][start.y] = estimate_distance(start, end);

    for (;;)
    {
        struct cell cur;
        int cur_weight = INT_MAX;

        // pick up current
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j)
                if (map[i][j] == 0 && !visited[i][j] && f_dist[i][j] < cur_weight)
                {
                    cur = (struct cell){ x:i, y:j };
                    cur_weight = f_dist[i][j];
                }

        if (cur_weight == INT_MAX)
            break;
            
        if (cur.x == end.x && cur.y == end.y)
        {
            // reconstruct path
            struct stack *s = stack_create(4);
            
            for (struct cell *p=&cur; p->x != INT_MAX && p->y != INT_MAX; p=&parent[p->x][p->y] )
                stack_push(s, (intptr_t) p);
                
            int len = stack_len(s);

            struct cell_path *path = xmalloc(sizeof(path)+sizeof(struct cell [len]));
            path->len = len;
            
            for (struct cell *dst=path->path, *p=0; stack_pop(s, (intptr_t *)&p); )
                *dst++ = *p;

            stack_destroy(s);
            
            return path;
        }

        visited[cur.x][cur.y] = true;
        
        explore_path(cur, (struct cell){ x:cur.x+1, y:cur.y }, end,
                     N, map, visited, g_dist, f_dist, parent);
        explore_path(cur, (struct cell){ x:cur.x-1, y:cur.y }, end,
                     N, map, visited, g_dist, f_dist, parent);
        explore_path(cur, (struct cell){ x:cur.x, y:cur.y+1 }, end,
                     N, map, visited, g_dist, f_dist, parent);
        explore_path(cur, (struct cell){ x:cur.x, y:cur.y-1 }, end,
                     N, map, visited, g_dist, f_dist, parent);
    }
    
    return 0;
}

char num2chr(int q)
{
    switch (q)
    {
        case 0: return '-';
        case 1: return '#';
        case 2: return '*';
        default: return ' ';
    }
}

void display(int N, int map[N][N])
{
    for (int i=0; i<N; ++i)
    {
        for (int j=0; j<N; ++j)
            printf(" %c", num2chr(map[i][j])); 
        printf("\n");
    }
}

void start(int N, int map[N][N], struct cell start, struct cell end)
{
    display(N, map);
    printf("Finding a path from (%d,%d) to (%d,%d)\n", start.x, start.y, end.x, end.y);
    
    struct cell_path *path = find_path(N, map, start, end);
    
    if (!path)
    {
        printf("Path cannot be found!\n");
        return;
    }
    
    printf("Found this path:");
    for (int i=0; i<path->len; ++i)
    {
        map[path->path[i].x][path->path[i].y] = 2;
        printf(" (%d,%d)", path->path[i].x, path->path[i].y);
    }
    printf("\n");

    display(N, map);
    
    free(path);
}

void test_1()
{
    enum { N = 10 };
    int map[N][N] = 
    {
      //  0  1  2  3  4  5  6  7  8  9
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 0
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 1
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }, // 2
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }, // 3
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 4
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }, // 5
        { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 }, // 6
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }, // 7
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // 8
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }  // 9
    };
    
    printf("Test 1\n");
    start(N, map, (struct cell ){x: 9, y:1}, (struct cell ){x: 1, y:9});
}

int main(int argc, char *argv[])
{
    test_1();

    return 0;
}
