# 1 "stra.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "stra.c"





# 1 "str.h" 1
# 9 "str.h"
# 1 "/usr/lib/gcc/aarch64-redhat-linux/4.8.5/include/stddef.h" 1 3 4
# 147 "/usr/lib/gcc/aarch64-redhat-linux/4.8.5/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 212 "/usr/lib/gcc/aarch64-redhat-linux/4.8.5/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 324 "/usr/lib/gcc/aarch64-redhat-linux/4.8.5/include/stddef.h" 3 4
typedef unsigned int wchar_t;
# 10 "str.h" 2
# 1 "/usr/include/assert.h" 1 3 4
# 36 "/usr/include/assert.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 375 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 392 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 393 "/usr/include/sys/cdefs.h" 2 3 4
# 376 "/usr/include/features.h" 2 3 4
# 399 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 400 "/usr/include/features.h" 2 3 4
# 37 "/usr/include/assert.h" 2 3 4
# 65 "/usr/include/assert.h" 3 4



extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



# 11 "str.h" 2




size_t Str_getLength(const char* pSrc);




char* Str_copy(char* pDest, const char* pSrc);




char* Str_concat(char* pDest, const char* pSrc);





int Str_compare(const char* pStr1, const char* pStr2);





char* Str_search(const char *pHaystack, const char *pNeedle);
# 7 "stra.c" 2

size_t Str_getLength(const char pSrc[]) {
 size_t length = 0;
 ((pSrc != ((void *)0)) ? (void) (0) : __assert_fail ("pSrc != ((void *)0)", "stra.c", 10, __PRETTY_FUNCTION__));

 while (pSrc[length] != '\0')
  length++;

 return length;
}

char* Str_copy(char pDest[], const char pSrc[]) {
 size_t index = 0;
 ((pSrc != ((void *)0)) ? (void) (0) : __assert_fail ("pSrc != ((void *)0)", "stra.c", 20, __PRETTY_FUNCTION__));
 ((pDest != ((void *)0)) ? (void) (0) : __assert_fail ("pDest != ((void *)0)", "stra.c", 21, __PRETTY_FUNCTION__));

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
 ((pSrc != ((void *)0)) ? (void) (0) : __assert_fail ("pSrc != ((void *)0)", "stra.c", 35, __PRETTY_FUNCTION__));
 ((pDest != ((void *)0)) ? (void) (0) : __assert_fail ("pDest != ((void *)0)", "stra.c", 36, __PRETTY_FUNCTION__));

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
 ((pStr1 != ((void *)0)) ? (void) (0) : __assert_fail ("pStr1 != ((void *)0)", "stra.c", 50, __PRETTY_FUNCTION__));
 ((pStr2 != ((void *)0)) ? (void) (0) : __assert_fail ("pStr2 != ((void *)0)", "stra.c", 51, __PRETTY_FUNCTION__));

 while (pStr1[index] != '\0' && pStr2[index] != '\0') {
  if (pStr1[index] != pStr2[index])

   break;
  index++;
 }

 return (int) (pStr1[index] - pStr2[index]);
}

char* Str_search(const char pHaystack[], const char pNeedle[]) {
# 78 "stra.c"
 size_t hIndex = 0;
 size_t nIndex;
 size_t nLen = Str_getLength(pNeedle);
 ((pHaystack != ((void *)0)) ? (void) (0) : __assert_fail ("pHaystack != ((void *)0)", "stra.c", 81, __PRETTY_FUNCTION__));
 ((pNeedle != ((void *)0)) ? (void) (0) : __assert_fail ("pNeedle != ((void *)0)", "stra.c", 82, __PRETTY_FUNCTION__));

 if (pNeedle[0] == '\0')
  return (char*) pHaystack;

 while (pHaystack[hIndex] != '\0') {
  for (nIndex = 0; nIndex < nLen; nIndex++) {
   if (pHaystack[hIndex + nIndex] != pNeedle[nIndex])

    break;
   else if (nIndex == nLen - 1)


    return (char*) (pHaystack + hIndex);
  }
  hIndex++;
 }


 return ((void *)0);
}
