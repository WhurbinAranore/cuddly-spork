#pragma once

#include <stddef.h>

struct cdll_node_s {
    struct cdll_node_s * next;
    struct cdll_node_s * prev;
    void * data;
};
typedef struct cdll_node_s cdll_node_t;

struct cdll_head_s {
    cdll_node_t * node;
    size_t entries;
};
typedef struct cdll_head_s cdll_head_t;

cdll_head_t * cdll_init(void);

cdll_node_t * cdll_node_init(void *);

void * cdll_node_data(cdll_node_t *);

void cdll_node_destroy(cdll_node_t *);

void cdll_destroy(cdll_head_t *);

void cdll_insert_node(cdll_head_t *, cdll_node_t *);

cdll_node_t * cdll_remove_node(cdll_head_t *, cdll_node_t *);

void cdll_push_node(cdll_head_t *, cdll_node_t *);

cdll_node_t * cdll_pop_node(cdll_head_t *);

void cdll_enqueue_node(cdll_head_t *, cdll_node_t *);

cdll_node_t * cdll_dequeue_node(cdll_head_t *);
