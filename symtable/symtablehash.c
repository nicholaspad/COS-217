/*--------------------------------------------------------------------*/
/* symtablehash.c                                                     */
/* Author: Nicholas Padmanabhan (ntyp) (P05)                          */
/*--------------------------------------------------------------------*/

#include "symtable.h"

enum {INITIAL_SIZE = 509, XXS = 1021, XS = 2039, S = 4093, M = 8191,
	  L = 16381, XL = 32749, XXL = 65521};

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
   of bindings and a variable to store the number of bindings.
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
   Return a hash code for pcKey that is between 0 and uBucketCount-1,
   inclusive.
 */
static size_t SymTable_hash(const char *pcKey, size_t uBucketCount) {
	const size_t HASH_MULTIPLIER = 65599;
	size_t u;
	size_t uHash = 0;

	assert(pcKey != NULL);

	for (u = 0; pcKey[u] != '\0'; u++)
		uHash = uHash * HASH_MULTIPLIER + (size_t) pcKey[u];

	return uHash % uBucketCount;
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
	size_t i;
	assert(oSymTable != NULL);

	for (i = 0; i < oSymTable->nBuckets; i++) {
		prev = NULL;

		for (curr = oSymTable->buckets[i]; curr != NULL;
		     curr = curr->next) {
			free(prev);
			free((char *) curr->key);
			prev = curr;
		}

		free(prev);
	}

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

	i = SymTable_hash(pcKey, oSymTable->nBuckets);

	prev = NULL;
	for (curr = oSymTable->buckets[i]; curr != NULL;
	     curr = curr->next) {
		if (strcmp(curr->key, pcKey) == 0)
			return 0;
		prev = curr;
	}

	curr = calloc(1, sizeof(struct Binding));
	if (curr == NULL)
		return 0;

	curr->key = malloc(strlen(pcKey) + 1);
	if (curr->key == NULL)
		return 0;
	strcpy((char *) curr->key, pcKey);

	curr->value = pvValue;
	oSymTable->length++;
	if (prev != NULL)
		prev->next = curr;
	else
		oSymTable->buckets[i] = curr;

	return 1;
}
