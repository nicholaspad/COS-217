/*--------------------------------------------------------------------*/
/* symtablelist.c                                                     */
/* Author: Nicholas Padmanabhan (ntyp) (P05)                          */
/*--------------------------------------------------------------------*/

#include "symtable.h"

struct Binding {
	/* Pointer to binding key (string) */
	const char *key;
	/* Pointer to binding value */
	void *value;
	/* Pointer to next binding in list */
	struct Binding *next;
};

struct SymTable {
	/* Pointer to first binding in list */
	struct Binding *first;
	/* Number of bindings in list */
	size_t length;
};

SymTable_T SymTable_new(void) {
	SymTable_T oSymTable = malloc(sizeof(SymTable_T));
	if (oSymTable == NULL)
		return NULL;

	oSymTable->length = 0;
	return oSymTable;
}

void SymTable_free(SymTable_T oSymTable) {

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

	curr = oSymTable->first;
	while (curr != NULL) {
		if (strcmp(curr->key, pcKey) == 0)
			return 0;
		prev = curr;
		curr = curr->next;
	}

	curr = malloc(sizeof(struct Binding));
	if (curr == NULL)
		return 0;

	curr->key = malloc(strlen(pcKey) + 1);
	if (curr->key == NULL)
		return 0;
	strcpy(curr->key, pcKey);

	curr->value = pvValue;
	oSymTable->length++;
	if (prev != NULL)
		prev->next = curr;
	return 1;
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
                       const void *pvValue) {
	return NULL;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
	return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey) {
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
