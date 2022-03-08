#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"



struct token_type scanner(int fsa_table[7][10], char* vec, int position);

#endif