#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#include <arpa/inet.h>

#include "graph.h"

// Initializing Functions
static void _graphDestoryNodes(struct _node *n);
static void _graphResetNodes(struct _node *n);
static void _graphResetNodes(struct _node *n);
static void _graphSize(struct _node *n, uint32_t *size);
static void _graph_remove_node(graph g, struct _node *n, struct _node *past_n);
static void _graph_monitor(graph g, struct _node *n, struct _node *past_n);
static void _graph_print(struct _node *n);

// Creating Graph
graph graphCreate(void)
{
    graph g = calloc(1, sizeof(*g));
    g->nodes = NULL;
    g->type = BST;

    return g;
}

void graph_print(graph g){
  _graph_print(g->nodes);
}

void _graph_print(struct _node *n){
  if (n == NULL) {
    return;
  }

  printf("%s\n", n->data.ip_addr);
  printf("%s\n\n", n->data.port);

  _graph_print(n->next);
}

void *graphMonitor(void *data){
  graph g = (graph) data;
  while (1) {
    sleep(5);
    _graph_monitor(g, g->nodes, NULL);
  }
}

void _graph_monitor(graph g, struct _node *n, struct _node *past_n)
{
  if (n == NULL) {
    return;
  }

  if (n->data.lastPing < (size_t) time(NULL) - 10) {
    _graph_remove_node(g, n, past_n);
  }

  _graph_monitor(g, n->next, n);
}

void _graph_remove_node(graph g, struct _node *n, struct _node *past_n)
{
  if (n == NULL) {
    return;
  }

  if (past_n == NULL) {
    g->nodes = n->next;
    free(n);
    return;
  }

  past_n->next = n->next;
  free(n);
}

void graphSize(graph g, uint32_t *size){
    _graphSize(g->nodes, size);
}

void _graphSize(struct _node *n, uint32_t *size)
{
    if (!n)
    {
        return;
    }

    (*size)++;
    _graphSize(n->next, size);

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
void graphAddNode(graph g, char *ip_addr, char *port, size_t lastPing)
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
        strncpy(g->nodes->data.ip_addr, ip_addr, sizeof(ip_addr)+1);
        strncpy(g->nodes->data.port, port, sizeof(port)+1);
        g->nodes->data.lastPing = lastPing;
        g->nodes->visited = false;
        g->nodes->parent = NULL;

        // printf("%s\n", g->nodes->data.ip_addr);
        // printf("%s\n", g->nodes->data.port);

        return;
    }

    struct _node *newNode = calloc(1, sizeof(_node));
    strncpy(newNode->data.ip_addr, ip_addr, sizeof(ip_addr)+1);
    strncpy(newNode->data.port, port, sizeof(port)+1);
    newNode->data.lastPing = lastPing;
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

bool graphUpdate(graph g, char *ip_addr, char *port, size_t lastPing)
{
  struct _node *n = _graph_find(g->nodes, ip_addr, port);

  if (n != NULL) {
    n->data.lastPing = lastPing;
    return true;
  }

  return false;
}

// Find a certain node
struct _node *_graph_find(struct _node *n, char *ip_addr, char *port)
{
    if(!n)
    {
        return NULL;
    }

    // if (sizeof(n->data.port) == sizeof(port) && sizeof(n->data.ip_addr) == sizeof(ip_addr)) {
      // printf("%s %s\n", n->data.port, port);
      // printf("%s %s\n", n->data.ip_addr, ip_addr);
      // printf("%u %u\n", strcmp(n->data.port, port), strcmp(n->data.ip_addr, ip_addr));
      if(strcmp(n->data.port, port) == 0 && strcmp(n->data.ip_addr, ip_addr) == 0)
      {
          return n;
      }
    // }

    return _graph_find(n->next, ip_addr, port);
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
