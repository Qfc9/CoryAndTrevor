#ifndef graph_h
#define graph_h
#define DFS 0
#define FAST 1
#define BOTH 2

#include <stdlib.h>
#include <stdbool.h>

enum graph_type {BST=0, GRAPH=1};

struct _graph
{
    unsigned int type;
    unsigned int sz;
    struct _node *nodes;
} _graph;

// Initializing Structs
struct _data
{
    char ip_addr[32];
    char port[32];
    size_t lastPing;
} _data;

struct _node
{
    struct _data data;
    bool visited;
    struct _node *parent;
    struct _node *next;
} _node;

struct _stack
{
    struct _node *node;
    struct _stack *next;
} _stack;

typedef struct _graph *graph;

struct _node;

graph graphCreate(void);
void graphAddNode(graph g, char *ip_addr, char *port, size_t lastPing);
void graph_print(graph g);
void *graphMonitor(void *data);
bool graphUpdate(graph g, char *ip_addr, char *port, size_t lastPing);
void graph_add_edge(graph g, uint32_t n1, uint32_t n2);
bool graphPrintPath(graph g, char **data, size_t sz, char start, char end, size_t search);
void graphDestroy(graph g);

void graph_calculate_edges(graph g);
void graph_mark(struct _node *n_list, struct _node *n);

struct _node *graph_find_by_idx(graph g, uint32_t idx);
struct _node *_graph_find(struct _node *n, char *port, char *ip_addr);
void graph_replace_edges(struct _node *rem_n, struct _node *cur_n);
unsigned int graph_evaluate(struct _node *n);
void graph_edge_count_deduction(struct _node *n);
void graph_add_existing_node(struct _node *n, struct _node *new_n);
uint32_t graph_payload(graph g);
uint32_t graph_payload2(graph g);
void graphSize(graph g, uint32_t *size);
void graph_size_ignore(struct _node *n, uint32_t *size);

#endif
