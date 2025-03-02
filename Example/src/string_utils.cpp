#include "string_utils.hpp"

/**
 * @brief Compares two C-style strings.
 *
 * This function compares the strings pointed to by `pStr1` and `pStr2`
 * lexicographically. It returns a negative value if `pStr1` is less than `pStr2`,
 * a positive value if `pStr1` is greater than `pStr2`, and 0 if they are equal.
 *
 * @param pStr1 Pointer to the first C-style string. Must not be null.
 * @param pStr2 Pointer to the second C-style string. Must not be null.
 * @return Negative value if `pStr1 < pStr2`, positive if `pStr1 > pStr2`, or 0 if they are equal.
 */
int StrCompare (const char * pStr1, const char * pStr2)
{
    if ((pStr1 == nullptr) || (pStr2 == nullptr)) {
        // Handle null pointers: 
        // Return -1 if pStr1 is null, 1 if pStr2 is null, or 0 if both are null.
        return (pStr1 == nullptr) ? (pStr2 == nullptr ? 0 : -1) : 1;

    }

    while ((*pStr1 != END_OF_STR) && (*pStr2 != END_OF_STR)) {

        if (*pStr1 != *pStr2) {

            return (unsigned char)*pStr1 - (unsigned char)*pStr2;
        }

        pStr1++;
        pStr2++;
    }
    return (unsigned char)*pStr1 - (unsigned char)*pStr2;
}

/**
 * @brief Calculates the length of a C-style string (char*).
 *
 * This function computes the length of the string pointed to by `pStr`.
 * It iterates through the string until it reaches the end-of-string character (EOS).
 *
 * @param pStr Pointer to the C-style string. Must not be null.
 * @return Length of the string, or -1 if the input string is null.
 */
size_t StrLen (const char * pStr)
{
            size_t length = 0;

        if (pStr == nullptr) {
            return -1; // Return -1 to indicate null input
        }

        while (*pStr !=  END_OF_STR) {

            length++;
            pStr++;
        }

        return length;
}

// Custom strcpy implementation
char * StringCopy (char * pDest, const char * pSrc)
{
        char * original_dest;

    if (!pDest || !pSrc) {
        return nullptr;                                 // Handle null pointers
    }

    original_dest = pDest;

    while ( (*pDest++ = *pSrc++) != END_OF_STR );              // Copy until null terminator

    return original_dest;
}
