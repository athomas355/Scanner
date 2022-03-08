#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testScanner.h"


void testScan(int fsa_table[7][10], char* str, int line_number) {

    //declarations
    struct token_type token;
    int last_position = 0;
    int new_position = 0;
    
    //iterate through the array
    int i;
    for(i = 0; i < strlen(str); i++) {
        token = scanner(fsa_table, str, last_position);
        token.char_counter--;
        new_position = token.char_counter;
        i = new_position;
        
        //increments line number
        int j;
        for(j = last_position; j < new_position; j++) {
            if(str[j] == '\n') 
                
                line_number++;
        }
        
        //prints output
        if(token.return_token != "") {
            if(!strcmp(token.return_token, "EOF_tk")) {
                // printf("%s %s\n", token.return_token, token.token_str);
                break;
            }
            else {
                printf("%s %s %d\n", token.return_token, token.token_str, line_number);
            }
        }

        memset(token.token_str, 0, sizeof token.token_str);
        last_position = new_position;
    }

    // if(token.return_token != "EOF_tk") {
    //     token.return_token = "EOF_tk";
    //     printf("%s\n", token.return_token);
    // }    
}