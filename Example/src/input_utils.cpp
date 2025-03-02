#include <stdlib.h>
#include "input_utils.hpp"

/**
 * @brief Reads an integer input from the user.
 *
 * This function prompts the user to input an integer value from the standard input.
 * It supports both positive and negative integers and checks for valid integer input.
 * If the input is invalid, it prints an error message and clears the input buffer.
 * 
 * The function performs the following:
 * - Accepts a leading '+' or '-' sign to determine the integer's sign.
 * - Reads characters one by one and constructs the integer.
 * - Validates that the characters are digits (0-9).
 * - Checks for integer overflow when constructing the number. If the resulting number
 *   would exceed the range of an integer, it prints an error message and clears the buffer.
 *
 * @return 
 * - Returns the constructed integer multiplied by the appropriate sign.
 * - If the input is invalid (non-numeric character or overflow), it returns INT_MIN.
 * 
 * NOTE:
 * - All invalid inputs return INT_MIN. Therefore, return type cannot indicate whether the 
 *   error was due to invalid characters, an overflow condition,(only print statements)
 *   or if INT_MIN itself was entered. The INT_MIN which is valid int is handled in 
 *   incorrect way as we are not using exceptions (throw/catch) and return type is int only.
 * 
 * Example usage:
 * int value = GetInt();
 * if (value == INT_MIN) {
 *     // Handle error condition
 * }
 */
int GetInt ()
{
        int     sign            = 1;
        int     num             = INT_MIN;
        bool    signed_check    = true;
        char    ch;

    while ((ch = getc (stdin)) != NEWLINE && ch != EOF) {

        if (ch == MINUS_SIGN && signed_check) {

            sign = -1;
            signed_check = false;
            continue;
        }

        if (ch == PLUS_SIGN && signed_check) {

            signed_check = false;
            continue; 
        }

        if (ch < ZERO_CHAR || ch > NINE_CHAR) {

            CLRINP;
            return INT_MIN;
        }

        signed_check = false;

        if (num > (INT_MAX - (ch -  ZERO_CHAR)) / 10) {

            CLRINP;
            return INT_MIN;
        }

        num = num * 10 + (ch - ZERO_CHAR);
    }
    return sign * num;
}

void GetString (char *& pStr)
{
        int     input;
        char    char_input;
        char *  new_input;
        size_t  length;
        size_t  capacity    = CAPACITY;

    pStr = (char *) malloc ((capacity + 1) * sizeof (char));    // Add extra for \0

    if (!pStr) {

        printf ("\nMemory allocation failed\n");
        return;

    }

    length = 0;

    while ((input = getchar ()) != NEWLINE) {

        if (input == EOF || input == WIN_EOF) {     // Check for EOF condition

            if (length == 0) {

                // Input termination, return BAD.
                printf ("Got EOF without any input. Input terminated.\n");
                free (pStr);
                pStr = nullptr;
                return;

            }

            // Handle EOF but with existing input (finish string)
            printf ("\nEOF found. Terminating input.\n");
            break;
        }

        char_input = (char) input;

        if (length >= capacity) {

            capacity *= 2;

            if (capacity > MAX_CAPACITY) {

                printf ("Max limit reached");
                free (pStr);
                pStr = nullptr;
                return;

            }

            new_input = (char *) realloc (pStr, (capacity + 1) * sizeof (char));    // Add extra for \0

            if (!new_input) {

                printf ("\nFailed to allocate memory\n");
                free (pStr);
                pStr = nullptr;
                return;

            }

            pStr = new_input;
        }

        pStr[length++] = char_input;

    }

    pStr[length] = EOS;
}
