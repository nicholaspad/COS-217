/*--------------------------------------------------------------------*/
/* stra.c                                                             */
/* Author: Nicholas Padmanabhan (ntyp) (P05)                          */
/*--------------------------------------------------------------------*/

#include "str.h"

size_t Str_getLength(const char pSrc[]) {
	size_t length = 0;
	assert(pSrc != NULL);

	while (pSrc[length] != '\0')
		length++;

	return length;
}

char* Str_copy(char pDest[], const char pSrc[]) {
	size_t index = 0;
	assert(pSrc != NULL);
	assert(pDest != NULL);

	while (pSrc[index] != '\0') {
		pDest[index] = pSrc[index];
		index++;
	}

	pDest[index] = '\0'; /* Append null char to pDest */
	return pDest;
}

char* Str_concat(char pDest[], const char pSrc[]) {
	size_t pDestIndex = Str_getLength(pDest);
	size_t index = 0;
	assert(pSrc != NULL);
	assert(pDest != NULL);

	while (pSrc[index] != '\0') {
		pDest[pDestIndex] = pSrc[index];
		index++;
		pDestIndex++;
	}

	pDest[pDestIndex] = '\0'; /* Append null char to pDest */
	return pDest;
}

int Str_compare(const char pStr1[], const char pStr2[]) {
	size_t index = 0;
	assert(pStr1 != NULL);
	assert(pStr2 != NULL);

	while (pStr1[index] != '\0' && pStr2[index] != '\0') {
		if (pStr1[index] != pStr2[index])
			/* Early-stopping when chars are different */
			break;
		index++;
	}

	return (int) (pStr1[index] - pStr2[index]);
}

char* Str_search(const char pHaystack[], const char pNeedle[]) {
	/*
	   Algorithm overview:
	   1. Iterate through pHaystack, checking for equality with first
	   char of pNeedle.
	   2. If equality is found, continue iterating and check equality
	   with remaining chars of pNeedle.
	   2a. If unequality is found, return to step 1, starting one after
	   the initial equal char.
	   2b. SUCCESS if last char of pNeedle is equal (i.e. pNeedle is a
	   substring of pHaystack).
	   3. Return to step 1 until reaching end of pHaystack.
	   4. NON-SUCCESS if end of pHaystack is reached without full match.
	 */

	size_t hIndex = 0;
	size_t nIndex;
	size_t nLen;
	assert(pHaystack != NULL);
	assert(pNeedle != NULL);

	if (pNeedle[0] == '\0')
		return (char*) pHaystack;

	nLen = Str_getLength(pNeedle);

	while (pHaystack[hIndex] != '\0') {
		for (nIndex = 0; nIndex < nLen; nIndex++) {
			if (pHaystack[hIndex + nIndex] != pNeedle[nIndex])
				/* Early-stopping (no match) when chars are different */
				break;
			else if (nIndex == nLen - 1)
				/* Match found if nIndex points to last char of
				   pNeedle */
				return (char*) (pHaystack + hIndex);
		}
		hIndex++;
	}

	/* pNeedle does not exist in pHaystack if code gets here */
	return NULL;
}
