#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

constexpr char END_OF_STR = '\0';

int     StrCompare  (const char * pStr1, const char * pStr2);
size_t  StrLen      (const char * pStr);
char *  StringCopy  (char * pDest, const char * pSrc);

#endif // !STRING_UTILS_HPP
