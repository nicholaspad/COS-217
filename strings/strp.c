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

	*pDestEnd = '\0';
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

	*pDestEnd = '\0';
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
			break;
		pStr1End++;
		pStr2End++;
	}

	return (int) (*pStr1End - *pStr2End);
}
