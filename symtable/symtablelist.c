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
	/* Pointer to next binding */
	struct Binding *next;
};

struct SymTable {
	/* Pointer to first binding */
	struct Binding *first;
};
