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

int Str_compare(const char str1[], const char str2[]) {
	size_t index = 0;
	assert(str1 != NULL);
	assert(str2 != NULL);

	while (str1[index] != '\0' && str2[index] != '\0') {
		if (str1[index] != str2[index])
			break;
		index++;
	}

	return (int) (str1[index] - str2[index]);
}
