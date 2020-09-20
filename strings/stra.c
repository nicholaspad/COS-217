#include "str.h"

size_t Str_getLength(const char pcSrc[])
{
	size_t uLength = 0;
	assert(pcSrc != NULL);
	while (pcSrc[uLength] != '\0')
		uLength++;
	return uLength;
}
