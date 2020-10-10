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

	oSymTable->first = malloc(sizeof(struct Binding));
	if (oSymTable->first == NULL) {
		free(oSymTable);
		return NULL;
	}

	oSymTable->length = 0;

	return oSymTable;
}

void SymTable_free(SymTable_T oSymTable) {

}

size_t SymTable_getLength(SymTable_T oSymTable) {
	return 0;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey,
                 const void *pvValue) {
	return 0;
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
