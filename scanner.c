#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct token_type scanner(int fsa_table[7][10], char* str, int position) {
    
    //declarations
    int state = 0;
    int next_state;
    char current_char = str[position];
    int col_num;
    struct token_type token;
    token.char_counter = position;
    char keywords[13][10] = {
        "Again", "If", "Assign", "Move", "Show", "Flip", "Name", "Home", "Do", "Spot", "Place", "Here", "There"
    };
    memset(token.token_str, 0, sizeof token.token_str);
   
    while(state < 1000) {
        token.char_counter++;
        //if statement to determine what the current char is
        //white space
        if(current_char == ' ') 
            col_num = 1;
        //new line
        if(current_char == '\n') 
            col_num = 1;
        //uppercase letters
        if(isupper(current_char)) 
            col_num = 2;
        //lowercase letters
        if(islower(current_char)) 
            col_num = 3;
        //number
        if(isdigit(current_char)) 
            col_num = 4;
        //operator
        if(current_char == '&' || current_char == '+' || current_char == '/' || current_char == '%' || current_char == '.' || current_char == '{' || current_char == '}') 
            col_num = 5;
        //double operator 1st
        if(current_char == '<') 
            col_num = 6;
        //double operator 2nd
        if(current_char == '-') 
            col_num = 8;
        //comment
        if(current_char == '*') 
            col_num = 9;
        //EOF
        if(position >= strlen(str))
            col_num = 0;

        
        //determine the next state from the fsa table
        next_state = fsa_table[state][col_num];
        
        //error
        if(next_state == -1) {
            printf("ERROR\n");
            exit(-1);
        }

        //switch to determine the final state
        switch (next_state)
        {
            //EOF
            case 1001:
                token.return_token = "EOF_tk";
                return token;
            //ID_tk or Keyword
            case 1002:
                //check if keyword

                //ID_tk
                
                token.return_token = "Identifier";
                return token;
                
            //Num_tk
            case 1003:
                token.return_token = "Number";
                return token;
            //Operator
            case 1004:
                token.return_token = "Operator";
                return token;
            case 1005:
                token.return_token = "Operator";
                return token;
            case 1006:
                token.return_token = "Operator";
                return token;
            case 1007:
                token.return_token = "Operator";
                return token;
            //comment
            case 2000:
                while(str[token.char_counter] != '*') { 
                    token.char_counter++;
                }
                token.char_counter += 2;
                return token;

            
            default:
                if(!isspace(current_char) && current_char != '\n') {
                    strncat(token.token_str, &current_char, 1);
                }
                state = next_state;
                position++;

                current_char = str[position];
                
        }

    }

    return token;
}