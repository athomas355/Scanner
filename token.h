#ifndef TOKEN_H
#define TOKEN_H
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STR_LENGTH 1024


struct token_type {
    enum token_ID {IDENT_tk, NUM_tk, KW_tk, OP_tk, EOF_tk} token;
    int line_number;
    int state;
    char* return_token;
    char token_str[MAX_STR_LENGTH];
    int char_counter;
    bool newline_lookahead;
};

#endif