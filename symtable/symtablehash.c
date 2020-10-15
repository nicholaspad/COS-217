/*--------------------------------------------------------------------*/
/* symtablehash.c                                                     */
/* Author: Nicholas Padmanabhan (ntyp) (P05)                          */
/*--------------------------------------------------------------------*/

#include <stdio.h>

#include "symtable.h"

/*
   Successive prime-number sizes of the buckets array, used during hash
   table expansion.
 */
enum {
    INITIAL_SIZE = 509,
    XXSMALL = 1021,
    XSMALL = 2039,
    SMALL = 4093,
    MEDIUM = 8191,
    LARGE = 16381,
    XLARGE = 32749,
    XXLARGE = 65521
};

/*
   Represents a single binding, consisting of a key (string), a value
   (any pointer), and a pointer to the next binding in the linked list.
 */
struct Binding {
    /* Pointer to binding key (string) */
    const char *key;
    /* Pointer to binding value */
    const void *value;
    /* Pointer to next binding in list */
    struct Binding *next;
};

/*
   Represents the hash table, consisting of an array of linked lists
   of bindings, the number of bindings, and the number of buckets.
 */
struct SymTable {
    /* Pointer to buckets array */
    struct Binding **buckets;
    /* Number of bindings in hash table */
    size_t length;
    /* Number of buckets in hash table */
    size_t nBuckets;
};

/*
   Returns a hash code for pcKey that is between 0 and uBucketCount-1,
   inclusive.
 */
static size_t SymTable_hash(const char *pcKey, size_t uBucketCount) {
    const size_t HASH_MULTIPLIER = 65599;
    size_t u;
    size_t uHash = 0;

    assert(pcKey != NULL);

    for (u = 0; pcKey[u] != '\0'; u++)
        uHash = uHash * HASH_MULTIPLIER + (size_t)pcKey[u];

    return uHash % uBucketCount;
}

/*
   Returns the next bucket count based on the current bucket count
   uCurrentSize, needed during hash table expansion. Returns 0 if the
   maximum bucket count is already in use, or if expansion is not yet
   needed.
 */
static size_t SymTable_nextSize(size_t uCurrentSize) {
    switch (uCurrentSize) {
    case INITIAL_SIZE:
        return XXSMALL;
    case XXSMALL:
        return XSMALL;
    case XSMALL:
        return SMALL;
    case SMALL:
        return MEDIUM;
    case MEDIUM:
        return LARGE;
    case LARGE:
        return XLARGE;
    case XLARGE:
        return XXLARGE;
    default:
        return 0;
    }
}

/*
   Expands the buckets array (if needed) of oSymTable, a SymTable_T
   object, to the next appropriate size. Does not change oSymTable if
   expansion is not needed, if the buckets array is already at maximum
   size, or if there is insufficient memory.
 */
static void SymTable_expand(SymTable_T oSymTable) {
    struct Binding **newBuckets;
    struct Binding *curr;
    struct Binding *next;
    struct Binding *temp;
    size_t uNewSize;
    size_t uIndex;
    size_t i;
    assert(oSymTable != NULL);

    /* Retrieve the next buckets count */

    uNewSize = SymTable_nextSize(oSymTable->length);
    if (uNewSize == 0)
        return;

    /* Allocate an expanded buckets array */

    newBuckets = calloc(uNewSize, sizeof(struct Binding));
    if (newBuckets == NULL)
        return;

    /* Rehash all bindings into expanded buckets array */

    for (uIndex = 0; uIndex < oSymTable->nBuckets; uIndex++) {
        for (curr = oSymTable->buckets[uIndex]; curr != NULL;
             curr = next) {
            next = curr->next;
            i = SymTable_hash(curr->key, uNewSize);

            if (newBuckets[i] == NULL)
                newBuckets[i] = curr;
            else {
                temp = newBuckets[i];
                newBuckets[i] = curr;
                newBuckets[i]->next = temp;
            }
        }
    }

    /* Link expanded buckets array to oSymTable and clean up */

    free(oSymTable->buckets);
    oSymTable->buckets = newBuckets;
    oSymTable->nBuckets = uNewSize;
}

SymTable_T SymTable_new(void) {
    SymTable_T oSymTable = calloc(1, sizeof(struct SymTable));
    if (oSymTable == NULL)
        return NULL;

    oSymTable->buckets = calloc(INITIAL_SIZE, sizeof(struct Binding));
    if (oSymTable->buckets == NULL) {
        free(oSymTable);
        return NULL;
    }

    oSymTable->nBuckets = INITIAL_SIZE;

    return oSymTable;
}

void SymTable_free(SymTable_T oSymTable) {
    struct Binding *prev;
    struct Binding *curr;
    size_t uIndex;
    assert(oSymTable != NULL);

    /* Free each linked list */

    printf("HERE\n");

    for (uIndex = 0; uIndex < oSymTable->nBuckets; uIndex++) {
        prev = NULL;

        for (curr = oSymTable->buckets[uIndex]; curr != NULL;
             curr = curr->next) {
            free(prev);
            printf("NICHOLAS\n");
            free((char *)curr->key);
            printf("PADMANABHAN\n");
            prev = curr;
        }

        free(prev);
    }

    /* Free the buckets array and oSymTable itself */

    free(oSymTable->buckets);
    free(oSymTable);
}

size_t SymTable_getLength(SymTable_T oSymTable) {
    assert(oSymTable != NULL);

    return oSymTable->length;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey,
                 const void *pvValue) {
    struct Binding *prev;
    struct Binding *curr;
    size_t i;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    /* Expand oSymTable if needed */

    if (oSymTable->length == oSymTable->nBuckets)
        SymTable_expand(oSymTable);

    i = SymTable_hash(pcKey, oSymTable->nBuckets);

    /* Check bucket for duplicate key */

    prev = NULL;
    for (curr = oSymTable->buckets[i]; curr != NULL;
         curr = curr->next) {
        if (strcmp(curr->key, pcKey) == 0)
            return 0;
        prev = curr;
    }

    /* Add binding to bucket */

    curr = calloc(1, sizeof(struct Binding));
    if (curr == NULL)
        return 0;

    curr->key = malloc(strlen(pcKey) + 1);
    if (curr->key == NULL)
        return 0;
    strcpy((char *)curr->key, pcKey);

    curr->value = pvValue;
    oSymTable->length++;
    if (prev != NULL)
        prev->next = curr;
    else
        oSymTable->buckets[i] = curr;

    return 1;
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
                       const void *pvValue) {
    struct Binding *curr;
    void *retval;
    size_t i;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    i = SymTable_hash(pcKey, oSymTable->nBuckets);

    /* Locate binding and replace its value */

    for (curr = oSymTable->buckets[i]; curr != NULL; curr = curr->next)
        if (strcmp(curr->key, pcKey) == 0) {
            retval = (void *)curr->value;
            curr->value = pvValue;
            return retval;
        }

    return NULL;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
    struct Binding *curr;
    size_t i;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    i = SymTable_hash(pcKey, oSymTable->nBuckets);

    /* Locate binding */

    for (curr = oSymTable->buckets[i]; curr != NULL; curr = curr->next)
        if (strcmp(curr->key, pcKey) == 0)
            return 1;

    return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey) {
    struct Binding *curr;
    size_t i;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    i = SymTable_hash(pcKey, oSymTable->nBuckets);

    /* Locate binding */

    for (curr = oSymTable->buckets[i]; curr != NULL; curr = curr->next)
        if (strcmp(curr->key, pcKey) == 0)
            return (void *)curr->value;

    return NULL;
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
    struct Binding *prev;
    struct Binding *curr;
    void *retval;
    size_t i;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    i = SymTable_hash(pcKey, oSymTable->nBuckets);

    /* Locate binding, remove it from the linked list, and clean up */

    prev = NULL;
    for (curr = oSymTable->buckets[i]; curr != NULL;
         curr = curr->next) {
        if (strcmp(curr->key, pcKey) == 0) {
            oSymTable->length--;
            retval = (void *)curr->value;

            if (prev != NULL)
                prev->next = curr->next;
            else
                oSymTable->buckets[i] = curr->next;

            free((char *)curr->key);
            free(curr);
            return retval;
        }
        prev = curr;
    }

    return NULL;
}

void SymTable_map(SymTable_T oSymTable,
                  void (*pfApply)(const char *pcKey, void *pvValue,
                                  void *pvExtra),
                  const void *pvExtra) {
    struct Binding *curr;
    size_t uIndex;
    assert(oSymTable != NULL);
    assert(pfApply != NULL);

    /* Traverse all bindings and apply the function */

    for (uIndex = 0; uIndex < oSymTable->nBuckets; uIndex++)
        for (curr = oSymTable->buckets[uIndex]; curr != NULL;
             curr = curr->next)
            pfApply(curr->key, (void *)curr->value, (void *)pvExtra);
}
