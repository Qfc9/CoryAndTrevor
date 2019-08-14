#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include <arpa/inet.h>

#include "graph.h"

// Initializing Functions
static void _graphDestoryNodes(struct _node *n);
static void _graphResetNodes(struct _node *n);
static void _graphResetNodes(struct _node *n);

// Creating Graph
graph graphCreate(void)
{
    graph g = calloc(1, sizeof(*g));
    g->nodes = NULL;
    g->type = BST;

    return g;
}

void graph_size(struct _node *n, uint32_t *size)
{
    if (!n)
    {
        return;
    }

    (*size)++;
    graph_size(n->next, size);

    return;
}

void graph_add_existing_node(struct _node *n, struct _node *new_n)
{
    if (!n)
    {
        return;
    }
    if (!n->next)
    {
        n->next = new_n;
        return;
    }

    graph_add_existing_node(n->next, new_n);
}

// Adding a node to the graph
void graphAddNode(graph g, uint32_t value)
{
    if(!g)
    {
        return;
    }

    if(!g->nodes)
    {
        g->nodes = calloc(1, sizeof(_node));
        if(!g->nodes)
        {
            return;
        }
        // g->nodes->data.value = value;
        g->nodes->visited = false;
        g->nodes->parent = NULL;
        return;
    }

    struct _node *newNode = calloc(1, sizeof(_node));
    // newNode->data.value = value;
    newNode->visited = false;
    newNode->parent = NULL;

    struct _node *next = g->nodes;
    while(next->next)
    {
        next = next->next;
    }

    next->next = newNode;
}

struct _node *graph_find_by_idx(graph g, uint32_t idx)
{
    struct _node *n = g->nodes;

    if (!n || idx == 0)
    {
        return NULL;
    }

    uint32_t current_pos = 1;
    while(n)
    {
        if(current_pos == idx)
        {
            return n;
        }
        current_pos++;
        n = n->next;
    }

    return NULL;
}

// Destroying the graph
void graphDestroy(graph g)
{
    _graphDestoryNodes(g->nodes);

    free(g);
}

// Find a certain node
struct _node *_graph_find(struct _node *n, struct _node *find_n)
{
    if(!n)
    {
        return NULL;
    }

    if(n == find_n)
    {
        return n;
    }

    return _graph_find(n->next, find_n);
}

// Settings all nodes to false
void graphResetNodes(graph g)
{
    if(!g)
    {
        return;
    }

    _graphResetNodes(g->nodes);
}

// Settings all nodes to false
static void _graphResetNodes(struct _node *n)
{
    if(!n)
    {
        return;
    }

    n->visited = false;
    n->parent = NULL;
    _graphResetNodes(n->next);
}

// Destroy nodes
static void _graphDestoryNodes(struct _node *n)
{
    if(!n)
    {
        return;
    }

    _graphDestoryNodes(n->next);
    free(n);
}
