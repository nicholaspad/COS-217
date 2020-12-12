#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* a Node_T is a member of the List with a string as contents */
typedef struct node* Node_T;

/* building block of the List */
struct node {
    /* contents of node */
    char* payload;
    /* next node in List */
    Node_T next;
};

/* head of the List */
static Node_T first = NULL;

/* if payload is not already in the List,
   inserts a new node at front of the List having contents payload.
   returns 1 if insertion is successful, 0 if unsuccessful. */
int List_insert(const char* payload) {
    Node_T curr = first;
    assert(payload != NULL);
    while (curr != NULL)
        if (!strcmp(curr->payload, payload))
            return 0;
    curr = malloc(sizeof(struct node));
    if (curr == NULL)
        return 0;
    curr->next = first;
    curr->payload = malloc(strlen(payload) + 1);
    if (curr->payload == NULL)
        return 0;
    strcpy(curr->payload, payload);
    return 1;
}

/* removes all nodes from the List */
void List_free() {
    Node_T current;
    for (current = first; current != NULL; current = current->next)
        free(current);
}