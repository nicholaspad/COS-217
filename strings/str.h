/*--------------------------------------------------------------------*/
/* str.h                                                              */
/* Author: Nicholas Padmanabhan (ntyp) (P05)                          */
/*--------------------------------------------------------------------*/

#ifndef STR_INCLUDED
#define STR_INCLUDED

#include <stddef.h>
#include <assert.h>

/*
   Returns the length of string pSrc.
 */
size_t Str_getLength(const char* pSrc);

/*
   Copies string pSrc into string pDest and returns pDest.
 */
char* Str_copy(char* pDest, const char* pSrc);

/*
   Concatenates string pSrc to string pDest and returns pDest.
 */
char* Str_concat(char* pDest, const char* pSrc);

/*
   Compares strings pStr1 and pStr2 and returns 0 if they are identical,
   >0 if pStr1 > pStr2, or <0 if pStr1 < pStr2.
 */
int Str_compare(const char* pStr1, const char* pStr2);

/*
   Returns a pointer to the first occurence of string pNeedle (in its
   entirety) in string pHaystack.
 */
char* Str_search(const char *pHaystack, const char *pNeedle);

#endif
