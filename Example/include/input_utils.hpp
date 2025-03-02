#ifndef INPUT_UTILS_HPP
#define INPUT_UTILS_HPP

#include "defines.hpp"
#include <stdio.h>

constexpr char ZERO_CHAR        = '0';
constexpr char NINE_CHAR        = '9';
constexpr char PLUS_SIGN        = '+';
constexpr char MINUS_SIGN       = '-';

constexpr char NEWLINE          = '\n';
constexpr char EOS              = '\0';

constexpr int WIN_EOF           = 26;
constexpr int CONV_FACTOR_10    = 10;
constexpr int CAPACITY          = 128;
constexpr int MAX_CAPACITY      = (1024 * 1024 * 1024);

#define CLRINP while (getc (stdin) != NEWLINE)

int         GetInt              ();
void        GetString           (char *& pStr);

#endif // !INPUT_UTILS_HPP
