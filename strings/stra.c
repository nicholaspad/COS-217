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

	pDest[index] = '\0';
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

	pDest[pDestIndex] = '\0';
	return pDest;
}

int Str_compare(const char pStr1[], const char pStr2[]) {
	size_t index = 0;
	assert(pStr1 != NULL);
	assert(pStr2 != NULL);

	while (pStr1[index] != '\0' && pStr2[index] != '\0') {
		if (pStr1[index] != pStr2[index])
			break;
		index++;
	}

	return (int) (pStr1[index] - pStr2[index]);
}

char* Str_search(const char pHaystack[], const char pNeedle[]) {
	size_t hIndex = 0;
	size_t nIndex;
	size_t nLen = Str_getLength(pNeedle);
	assert(pHaystack != NULL);
	assert(pNeedle != NULL);

	if (pNeedle[0] == '\0')
		return (char*) pHaystack;

	while(pHaystack[hIndex] != '\0') {
		for (nIndex = 0; nIndex < nLen; nIndex++) {
			if (pHaystack[hIndex + nIndex] != pNeedle[nIndex])
				break;
			else if (nIndex == nLen - 1)
				return (char*) (pHaystack + hIndex);
		}
		hIndex++;
	}

	return NULL;
}
