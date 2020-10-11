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
	/* Pointer to first binding in list */
	struct Binding **buckets;
	/* Number of bindings in list */
	size_t length;
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
		uHash = uHash * HASH_MULTIPLIER + (size_t)pcKey[u];

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

	return oSymTable;
}
