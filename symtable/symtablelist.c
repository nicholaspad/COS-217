/*--------------------------------------------------------------------*/
/* symtablelist.c                                                     */
/* Author: Nicholas Padmanabhan (ntyp) (P05)                          */
/*--------------------------------------------------------------------*/

#include "symtable.h"

static size_t length;

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
	SymTable_T *oSymTable = malloc(sizeof(SymTable_T));
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
