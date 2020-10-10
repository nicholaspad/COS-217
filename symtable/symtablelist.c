/*--------------------------------------------------------------------*/
/* symtablelist.c                                                     */
/* Author: Nicholas Padmanabhan (ntyp) (P05)                          */
/*--------------------------------------------------------------------*/

#include "symtable.h"

struct Binding {
	/* Pointer to binding key (string) */
	const char *key;
	/* Pointer to binding value */
	const void *value;
	/* Pointer to next binding in list */
	struct Binding *next;
};

struct SymTable {
	/* Pointer to first binding in list */
	struct Binding *first;
	/* Number of bindings in list */
	size_t *length;
};

SymTable_T SymTable_new(void) {
	SymTable_T oSymTable = malloc(sizeof(*SymTable_T));
	if (oSymTable == NULL)
		return NULL;

	oSymTable->first = NULL;
	oSymTable->length = 0;

	return oSymTable;
}

void SymTable_free(SymTable_T oSymTable) {
	struct Binding *prev;
	struct Binding *curr;
	assert(oSymTable != NULL);

	prev = NULL;
	for (curr = oSymTable->first; curr != NULL; curr = curr->next) {
		free(prev);
		free((char *) curr->key);
		prev = curr;
	}

	free(prev);
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
	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	assert(pvValue != NULL);

	prev = NULL;
	for (curr = oSymTable->first; curr != NULL; curr = curr->next) {
		if (strcmp(curr->key, pcKey) == 0)
			return 0;
		prev = curr;
	}

	curr = malloc(sizeof(struct Binding));
	if (curr == NULL)
		return 0;

	curr->key = malloc(strlen(pcKey) + 1);
	if (curr->key == NULL)
		return 0;
	strcpy((char *) curr->key, pcKey);

	curr->value = pvValue;
	oSymTable->length++;
	curr->next=NULL;
	if (prev != NULL)
		prev->next = curr;
	else
		oSymTable->first = curr;

	return 1;
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
                       const void *pvValue) {
	struct Binding *curr;
	void *retval;
	assert(oSymTable != NULL);
	assert(pcKey != NULL);
	assert(pvValue != NULL);

	for (curr = oSymTable->first; curr != NULL; curr = curr->next)
		if (strcmp(curr->key, pcKey) == 0) {
			retval = (void *) curr->value;
			curr->value = pvValue;
			return retval;
		}

	return NULL;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
	struct Binding *curr;
	assert(oSymTable != NULL);
	assert(pcKey != NULL);

	for (curr = oSymTable->first; curr != NULL; curr = curr->next)
		if (strcmp(curr->key, pcKey) == 0)
			return 1;

	return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey) {
	struct Binding *curr;
	assert(oSymTable != NULL);
	assert(pcKey != NULL);

	for (curr = oSymTable->first; curr != NULL; curr = curr->next)
		if (strcmp(curr->key, pcKey) == 0)
			return (void *) curr->value;

	return NULL;
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
	return NULL;
}

void SymTable_map(SymTable_T oSymTable,
                  void (*pfApply)(const char *pcKey, void *pvValue,
                                  void *pvExtra),
                  const void *pvExtra) {

}
