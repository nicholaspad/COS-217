# 1 "strp.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "strp.c"





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
# 7 "strp.c" 2

size_t Str_getLength(const char* pSrc) {
 const char* pEnd;
 ((pSrc != ((void *)0)) ? (void) (0) : __assert_fail ("pSrc != ((void *)0)", "strp.c", 10, __PRETTY_FUNCTION__));

 pEnd = pSrc;

 while (*pEnd != '\0')
  pEnd++;

 return (size_t)(pEnd - pSrc);
}

char* Str_copy(char* pDest, const char* pSrc) {
 const char* pSrcEnd;
 char* pDestEnd;
 ((pSrc != ((void *)0)) ? (void) (0) : __assert_fail ("pSrc != ((void *)0)", "strp.c", 23, __PRETTY_FUNCTION__));
 ((pDest != ((void *)0)) ? (void) (0) : __assert_fail ("pDest != ((void *)0)", "strp.c", 24, __PRETTY_FUNCTION__));

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
 ((pSrc != ((void *)0)) ? (void) (0) : __assert_fail ("pSrc != ((void *)0)", "strp.c", 42, __PRETTY_FUNCTION__));
 ((pDest != ((void *)0)) ? (void) (0) : __assert_fail ("pDest != ((void *)0)", "strp.c", 43, __PRETTY_FUNCTION__));

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
 ((pStr1 != ((void *)0)) ? (void) (0) : __assert_fail ("pStr1 != ((void *)0)", "strp.c", 61, __PRETTY_FUNCTION__));
 ((pStr2 != ((void *)0)) ? (void) (0) : __assert_fail ("pStr2 != ((void *)0)", "strp.c", 62, __PRETTY_FUNCTION__));

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

char* Str_search(const char* pHaystack, const char* pNeedle) {
# 93 "strp.c"
 const char* pHaystackEnd;
 const char* pNeedleEnd;
 const char* pHaystackTemp;
 size_t nLen = Str_getLength(pNeedle);
 ((pHaystack != ((void *)0)) ? (void) (0) : __assert_fail ("pHaystack != ((void *)0)", "strp.c", 97, __PRETTY_FUNCTION__));
 ((pNeedle != ((void *)0)) ? (void) (0) : __assert_fail ("pNeedle != ((void *)0)", "strp.c", 98, __PRETTY_FUNCTION__));

 pHaystackEnd = pHaystack;
 pNeedleEnd = pNeedle;

 if (*pNeedle == '\0')
  return (char*) pHaystack;

 while (*pHaystackEnd != '\0') {
  pHaystackTemp = pHaystackEnd;
  pNeedleEnd = pNeedle;
  while(*pNeedleEnd != '\0') {
   if (*pHaystackTemp != *pNeedleEnd)

    break;
   else if (pNeedleEnd - pNeedle == (long) nLen - 1)


    return (char*) pHaystackEnd;
   pHaystackTemp++;
   pNeedleEnd++;
  }
  pHaystackEnd++;
 }


 return ((void *)0);
}
