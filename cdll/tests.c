#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cdll.h>

cdll_node_t * return_random_node(cdll_head_t * head)
{
    int num = rand() % 1000;

    cdll_node_t * node = head->node;

    for(int i = 0; i < num; i++) {
        node = node->next;
    }

    return node;
}

int main(void) {
    printf("Just some basic tests...\n");

    time_t t;
    srand((unsigned) time(&t));

    cdll_head_t * head = cdll_init();

    for(size_t i = 0; i < 1000; i++) {
        cdll_insert_node(head, cdll_node_init((size_t*)i));
    }

    for(size_t i = 0; i < 1000; i++) {
        cdll_node_t * node = cdll_remove_node(head, return_random_node(head));

        size_t data = (size_t) cdll_node_data(node);

        printf("data: %lu\n", data);

        cdll_node_destroy(node);
    }
    
    cdll_destroy(head);


    head = cdll_init();

    for(size_t i = 0; i < 100; i++) {
        cdll_push_node(head, cdll_node_init((size_t*)i));
    }

    for(size_t i = 0; i < 100; i++) {
        cdll_node_t * node = cdll_pop_node(head);

        size_t data = (size_t) cdll_node_data(node);

        printf("data: %lu\n", data);
        
        cdll_node_destroy(node);
    }

    cdll_destroy(head);

    head = cdll_init();

    for(size_t i = 0; i < 100; i++) {
        cdll_enqueue_node(head, cdll_node_init((size_t*)i));
    }

    for(size_t i = 0; i < 100; i++) {
        cdll_node_t * node = cdll_dequeue_node(head);

        size_t data = (size_t) cdll_node_data(node);

        printf("data: %lu\n", data);

        cdll_node_destroy(node);
    }

    cdll_destroy(head);

    return 0; 
}
