#include <cdll.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void cdll_verify_head(cdll_head_t * head)
{
    if(!head)
    {
        fprintf(stderr, "CDLL Head not initialized\n");
        _exit(1);
    }

    if(0 > head->entries)
    {
        fprintf(stderr, "CDLL Invalid number of entries\n");
        _exit(1);
    }
}

cdll_head_t * cdll_init(void)
{
    cdll_head_t * head = malloc(sizeof(cdll_head_t));
    if (!head)
    {
        _exit(1);
    }    

    head->node = NULL;
    head->entries = 0;

    return head;
}

cdll_node_t * cdll_node_init(void * data)
{
    cdll_node_t * node = malloc(sizeof(cdll_node_t));
    node->next = node;
    node->prev = node;
    node->data = data;

    return node;
}

void * cdll_node_data(cdll_node_t * node)
{
    return node->data;
}

void cdll_node_destroy(cdll_node_t * node)
{
    node->prev = NULL;
    node->next = NULL;
    node->data = NULL;

    free(node);
    node = NULL;

    return;
}

void cdll_destroy(cdll_head_t * head)
{
    cdll_verify_head(head);

    if(head->entries) {
        fprintf(stderr, "Error: I'm not your parent, remove your own nodes\n");
        _exit(1);
    }

    if(head->node) {
        fprintf(stderr, "Error: Linked list corruption\n");
        _exit(1);
    }

    free(head);
    head = NULL;
}

void cdll_insert_node(cdll_head_t * head, cdll_node_t * new_node)
{
    cdll_verify_head(head);

    // If we're the first node
    if (NULL == head->node)
    {
        head->node = new_node;
        head->entries = 1;

        return;
    }

    cdll_node_t * node = head->node;
    
    if (node->prev->next == node && node->next->prev == node) 
    {
        new_node->prev = node->prev;
        new_node->next = node;
        node->prev->next = new_node;
        node->prev = new_node;
        head->entries++;
        head->node = new_node;
        return;
    }

    fprintf(stderr,  "Error: Linked list corruption\n");
    _exit(1);

}

cdll_node_t * cdll_remove_node(cdll_head_t * head, cdll_node_t * old_node)
{
    cdll_verify_head(head);

    // If the list is empty
    if(0 == head->entries)
    {
        // This is an error condition
        return NULL;
    }

    // If we are the last node
    if (1 == head->entries)
    {
        if (head->node != old_node)
        {
            fprintf(stderr, "Error: Node should be the last in the list");
            _exit(1);
        }

        head->node = NULL;
        head->entries = 0;
        old_node->prev = NULL;
        old_node->next = NULL;

        return old_node;
    }

    // If the list has many nodes
    if(old_node->prev->next == old_node && old_node->next->prev == old_node)
    {
        cdll_node_t * prev = old_node->prev;
        cdll_node_t * next = old_node->next;

        prev->next = next;
        next->prev = prev;

        old_node->prev = NULL;
        old_node->next = NULL;

        if(old_node == head->node)
        {
            head->node = next;
        }
        head->entries--;

        return old_node;
    }

    fprintf(stderr, "Error: Linked list corruption\n");
    _exit(1);
}

void cdll_push_node(cdll_head_t * head, cdll_node_t * new_node)
{
    cdll_insert_node(head, new_node);
}

cdll_node_t * cdll_pop_node(cdll_head_t * head)
{
    if(0 == head->entries)
    {
        return NULL;
    }

    return cdll_remove_node(head, head->node);
}

void cdll_enqueue_node(cdll_head_t * head, cdll_node_t * new_node)
{
    cdll_insert_node(head, new_node);
}

cdll_node_t * cdll_dequeue_node(cdll_head_t * head)
{
    if(0 == head->entries)
    {
        return NULL;
    }

    return cdll_remove_node(head, head->node->prev);
}
