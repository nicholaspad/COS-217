/*--------------------------------------------------------------------*/
/* symtable.h                                                         */
/* Author: Nicholas Padmanabhan (ntyp) (P05)                          */
/*--------------------------------------------------------------------*/

#ifndef ST_INCLUDED
#define ST_INCLUDED

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
   A SymTable_T stores bindings each consisting of a key-value pair.
   Keys are strings that uniquely identify their bindings, and values
   are data that are somehow associated with their keys.
 */
typedef struct SymTable *SymTable_T;

/*
   Creates and returns an empty SymTable_T object, or NULL if
   insufficient memory is available.
 */
SymTable_T SymTable_new(void);

/*
   Frees all memory occupied by oSymTable, a SymTable_T object.
 */
void SymTable_free(SymTable_T oSymTable);

/*
   Returns the number of bindings in oSymTable, a SymTable_T object.
 */
size_t SymTable_getLength(SymTable_T oSymTable);

/*
    Adds to oSymTable a new binding with key pcKey and value pvValue,
    and returns 1. If a binding with key pcKey already exists, or if
    insufficient memory is available, leave oSymTable unchanged and
    return 0.
 */
int SymTable_put(SymTable_T oSymTable, const char *pcKey,
                 const void *pvValue);

/*
   If oSymTable contains a binding with key pcKey, replace its value
   with value pvValue and return the old value. Otherwise, leave
   oSymTable unchanged and return NULL.
 */
void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
                       const void *pvValue);

/*
    If oSymTable contains a binding with key pcKey, return 1. Otherwise,
    return 0.
 */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/*
    If oSymTable contains a binding with key pcKey, return its value.
    Otherwise, return NULL.
 */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

/*
    If oSymTable contains a binding with key pcKey, remove the binding
    from oSymTable and return its value. Otherwise, return NULL.
 */
void *SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/*
   Applies function *pfApply to each binding in oSymTable, passing
   pvExtra as an additional parameter.
 */
void SymTable_map(SymTable_T oSymTable,
                  void (*pfApply)(const char *pcKey, void *pvValue,
                                  void *pvExtra),
                  const void *pvExtra);

#endif
