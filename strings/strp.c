/*--------------------------------------------------------------------*/
/* strp.c                                                             */
/* Author: Nicholas Padmanabhan (ntyp) (P05)                          */
/*--------------------------------------------------------------------*/

#include "str.h"

size_t Str_getLength(const char* pSrc) {
	const char* pEnd;
	assert(pSrc != NULL);

	pEnd = pSrc;

	while (*pEnd != '\0')
		pEnd++;

	return (size_t)(pEnd - pSrc);
}

char* Str_copy(char* pDest, const char* pSrc) {
	const char* pSrcEnd;
	char* pDestEnd;
	assert(pSrc != NULL);
	assert(pDest != NULL);

	pSrcEnd = pSrc;
	pDestEnd = pDest;

	while (*pSrcEnd != '\0') {
		*pDestEnd = *pSrcEnd;
		pSrcEnd++;
		pDestEnd++;
	}

	*pDestEnd = '\0'; /* Append null char to pDest */
	return pDest;
}

char* Str_concat(char* pDest, const char* pSrc) {
	const char* pSrcEnd;
	char* pDestEnd;
	assert(pSrc != NULL);
	assert(pDest != NULL);

	pSrcEnd = pSrc;
	pDestEnd = pDest + Str_getLength(pDest);

	while (*pSrcEnd != '\0') {
		*pDestEnd = *pSrcEnd;
		pSrcEnd++;
		pDestEnd++;
	}

	*pDestEnd = '\0'; /* Append null char to pDest */
	return pDest;
}

int Str_compare(const char* pStr1, const char* pStr2) {
	const char* pStr1End;
	const char* pStr2End;
	assert(pStr1 != NULL);
	assert(pStr2 != NULL);

	pStr1End = pStr1;
	pStr2End = pStr2;

	while (*pStr1End != '\0' && *pStr2End != '\0') {
		if (*pStr1End != *pStr2End)
			/* Early-stopping when chars are different */
			break;
		pStr1End++;
		pStr2End++;
	}

	return (int) (*pStr1End - *pStr2End);
}

char* Str_search(const char* pHaystack, const char* pNeedle) {
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

	const char* pHaystackEnd;
	const char* pNeedleEnd;
	const char* pHaystackTemp;
	size_t nLen;
	assert(pHaystack != NULL);
	assert(pNeedle != NULL);

	nLen = Str_getLength(pNeedle);
	pHaystackEnd = pHaystack;
	pNeedleEnd = pNeedle;

	if (*pNeedle == '\0')
		return (char*) pHaystack;

	while (*pHaystackEnd != '\0') {
		pHaystackTemp = pHaystackEnd;
		pNeedleEnd = pNeedle;
		while(*pNeedleEnd != '\0') {
			if (*pHaystackTemp != *pNeedleEnd)
				/* Early-stopping (no match) when chars are different */
				break;
			else if (pNeedleEnd - pNeedle == (long) nLen - 1)
				/* Match found if pNeedleEnd points to last char of
				   pNeedle */
				return (char*) pHaystackEnd;
			pHaystackTemp++;
			pNeedleEnd++;
		}
		pHaystackEnd++;
	}

	/* pNeedle does not exist in pHaystack if code gets here */
	return NULL;
}
