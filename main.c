#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testScanner.h"

#define MAX_STR_LENGTH 1024

int main(int argc, char* argv[]) {

    //declarations
    char input[MAX_STR_LENGTH];
    char *text = calloc(MAX_STR_LENGTH + 1, 1);
    
    /*
        Rows:
        0 = initial state, 1 = ID, 2 = digit, 3 = single_op, 4 = double_op, 5 = :<, 6 = :=, 7 = :&
        
        Columns:
        EOF, WS, Uppercase letter, Lowercaser letter, number, Single_op, <, <, -, *
        
        Final States:
        1001 = EOFtk, 1002 = IDtk/KWtk, 1003 = NUMtk, 1004-1008 = OPtk, 2000 = comment 
    */
    int fsa_table[7][10] = {
        //eof, ws, upper, lower, num, single op, < , < , -, * 
        1001, 0, 1, 1, 2, 3, 4, -1, -1, 2000,                             //initial state
        1002, 1002, 1, 1, 1, 1002, 1002, 1002, 1002, 2000,                //ID state
        1003, 1003, 1003, 1003, 2, 1003, 1003, 1003, 1003, 2000,          //digit state
        1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 2000,       //single_op state
        -1, -1, -1, -1, -1, -1, 5, 5, 6, 2000,                           //double_op 1st state <
        1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 2000,       //double_op 2nd state <
        1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 2000,       //double_op 2nd state - 
    };

    if(argc == 1) {
        printf("Enter Input:\n");

         while(fgets(input, MAX_STR_LENGTH, stdin)) {  /* break with ^D or ^Z */
            text = realloc(text, strlen(text) + 1 + strlen(input));
            strcat(text, input);
        }  

        printf("\n\n");
        testScan(fsa_table, text, 1);

        printf("EOF_tk\n");

    }
    else if(argc == 2) {
        FILE * file = fopen(argv[1], "r");
        char buff[MAX_STR_LENGTH];
        int ch;
        int counter = 1;
        while (fgets(buff, MAX_STR_LENGTH, (FILE*)file)){
            // printf("%s\n", buff );
            testScan(fsa_table, buff, counter);
            counter++;
        }
        
        printf("EOF_tk\n");
        fclose(file);
    }
    else {
        printf("Command line error\n");
        exit(-1);
    }

    return 0;
}