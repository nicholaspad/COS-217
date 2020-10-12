/*--------------------------------------------------------------------*/
/* symtablehash.c                                                     */
/* Author: Nicholas Padmanabhan (ntyp) (P05)                          */
/*--------------------------------------------------------------------*/

#include "symtable.h"
#include <stdio.h>

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
		uHash = uHash * HASH_MULTIPLIER + (size_t) pcKey[u];

	return uHash % uBucketCount;
}

static void SymTable_freeBuckets(SymTable_T oSymTable) {
	struct Binding *prev;
	struct Binding *curr;
	size_t b;
	assert(oSymTable != NULL);

	for (b = 0; b < oSymTable->nBuckets; b++) {
		prev = NULL;

		for (curr = oSymTable->buckets[b]; curr != NULL;
		     curr = curr->next) {
			free(prev);
			free((char *) curr->key);
			prev = curr;
		}

		free(prev);
	}

	free(oSymTable->buckets);
}

/*
   Returns the next bucket count based on the current bucket count,
   needed during hash table expansion. Returns 0 if the maximum bucket
   count is already in use, or if expansion is not yet needed.
 */
static size_t SymTable_nextSize(size_t uCurrentSize) {
	switch (uCurrentSize) {
	case INITIAL_SIZE:
		return XXS;
	case XXS:
		return XS;
	case XS:
		return S;
	case S:
		return M;
	case M:
		return L;
	case L:
		return XL;
	case XL:
		return XXL;
	default:
		return 0;
	}
}

/*
   Creates and returns a new SymTable_T object with an expanded buckets
   array and frees the old SymTable_T. Does not change the old
   SymTable_T and returns NULL if expansion is not needed, if the
   buckets array is already at maximum size, or if there is insufficient
   memory.
 */
static SymTable_T SymTable_expand(SymTable_T oSymTable) {
	SymTable_T newSymTable;
	struct Binding *curr;
	size_t uNewSize;
	size_t b;
	int res;
	assert(oSymTable != NULL);

	newSymTable = SymTable_new();

	uNewSize = SymTable_nextSize(oSymTable->length);
	if (uNewSize == 0) {
		SymTable_free(newSymTable);
		return NULL;
	}

	newSymTable->buckets = calloc(uNewSize, sizeof(struct Binding));
	if (newSymTable->buckets == NULL) {
		SymTable_free(newSymTable);
		return NULL;
	}

	newSymTable->nBuckets = uNewSize;

	for (b = 0; b < oSymTable->nBuckets; b++) {
		for (curr = oSymTable->buckets[b]; curr != NULL;
		     curr = curr->next) {
			res = SymTable_put(newSymTable, curr->key, curr->value);
			if (res == 0) {
				SymTable_free(newSymTable);
				return NULL;
			}
		}
	}

	SymTable_freeBuckets(oSymTable);
	oSymTable->buckets = newSymTable->buckets;
	oSymTable->nBuckets = uNewSize;
	free(newSymTable);

	return oSymTable;
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
	size_t b;
	assert(oSymTable != NULL);

	SymTable_freeBuckets(oSymTable);
	free(oSymTable);
}

size_t SymTable_getLength(SymTable_T oSymTable) {
	assert(oSymTable != NULL);

	return oSymTable->length;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey,
                 const void *pvValue) {
	SymTable_T temp;
	struct Binding *prev;
	struct Binding *curr;
	size_t i;
	assert(oSymTable != NULL);
	assert(pcKey != NULL);

	if (oSymTable->length == oSymTable->nBuckets) {
		temp = SymTable_expand(oSymTable);
		if (temp != NULL)
			oSymTable = temp;
	}

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

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
                       const void *pvValue) {
	struct Binding *curr;
	void *retval;
	size_t i;
	assert(oSymTable != NULL);
	assert(pcKey != NULL);

	i = SymTable_hash(pcKey, oSymTable->nBuckets);

	for (curr = oSymTable->buckets[i]; curr != NULL;
	     curr = curr->next)
		if (strcmp(curr->key, pcKey) == 0) {
			retval = (void *) curr->value;
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

	for (curr = oSymTable->buckets[i]; curr != NULL;
	     curr = curr->next)
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

	for (curr = oSymTable->buckets[i]; curr != NULL;
	     curr = curr->next)
		if (strcmp(curr->key, pcKey) == 0)
			return (void *) curr->value;

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

	prev = NULL;
	for (curr = oSymTable->buckets[i]; curr != NULL;
	     curr = curr->next) {
		if (strcmp(curr->key, pcKey) == 0) {
			oSymTable->length--;
			retval = (void *) curr->value;

			if (prev != NULL)
				prev->next = curr->next;
			else
				oSymTable->buckets[i] = curr->next;

			free((char *) curr->key);
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
	size_t b;
	assert(oSymTable != NULL);
	assert(pfApply != NULL);

	for (b = 0; b < oSymTable->nBuckets; b++)
		for (curr = oSymTable->buckets[b]; curr != NULL;
		     curr = curr->next)
			pfApply(curr->key, (void *) curr->value, (void *) pvExtra);
}
