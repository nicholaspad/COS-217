#ifndef STR_INCLUDED
#define STR_INCLUDED

#include <stddef.h>
#include <assert.h>

/*
   Returns the length of string pSrc.
 */
size_t Str_getLength(const char* pSrc);

/*
   Returns pDest, a copy of string pSrc.
 */
char* Str_copy(char* pDest, const char* pSrc);

/*
   Returns pDest, the concatentation of string pSrc to the end of
   string pDest.
 */
char* Str_concat(char* pDest, const char* pSrc);

/*
   Compares strings pStr1 and pStr2 and returns 0 if they are identical,
   >0 if pStr1 > pStr2, or <0 if pStr1 < pStr2.
 */
int Str_compare(const char* pStr1, const char* pStr2);

#endif
