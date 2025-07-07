/*The MIT License (MIT)
 *
 * Copyright © 2025 Artem Podlegaev
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <editline.h>

#include "stack.h"

#define SCAN_BUFFER 1024

#define PROMT_STRING ">>"

#define EXIT 0
#define O_PLUS 1
#define O_MINUS 2
#define O_MUL 3
#define O_DIV 4
#define PRINT 5

STACK stack;

int num_1 = 0, num_2 = 0;

int is_keyword(const char* in) {
    if (strcmp(in, "+") == 0) return O_PLUS;
    if (strcmp(in, "-") == 0) return O_MINUS;
    if (strcmp(in, "*") == 0) return O_MUL;
    if (strcmp(in, "/") == 0) return O_DIV;

    if (strcmp(in, ".") == 0) return PRINT;

    return EXIT;
}

void scan(char* input) {
    // p
    for (int i = 0; i < sizeof(input); ++i) {
        if (isdigit(input[i])) {
            int digit = input[i] - '0';
            int j = i;
            while (isdigit(input[j]) && isdigit(input[j + 1]) && input[j] != ' ') {
                digit = (digit * 10) + (input[j] -'0');
                ++j;
            }
            i = j;
	    push(&stack, digit);
            /*printf("%d\n", digit);*/
        }
        else if (isalpha(input[i])) {
            char lexem[100] = {0};
            int pos = 0;
            int j = i;
            while (isalpha(input[j])) {
                lexem[pos++] = input[j];
                ++j;
            }
            lexem[pos] = '\0';
            i = j - 1;
            //printf("%s\t", lexem);
            //printf("%d\n", is_keyword(lexem));
        }
        else if (isspace(input[i])) {
            continue;
        }
        else {
            char symbol[2] = {input[i], '\0'};
            //printf("%s\t", symbol);
            //printf("%d\n", is_keyword(symbol));
	    //printf("%s\n", symbol);
	    switch (is_keyword(symbol)) {
		    case O_PLUS:
			    num_1 = peek(&stack);
			    pop(&stack);
			    num_2 = peek(&stack);
			    push(&stack, num_2 + num_1);
			   printf("%d\n", peek(&stack));
		    case O_MINUS:
			    num_1 = peek(&stack);
			    pop(&stack);
			    num_2 = peek(&stack);
			    push(&stack, num_2 - num_1);
			    //printf("%d\n", peek(&stack));
        	    case O_MUL:
                	num_1 = peek(&stack);
                	pop(&stack);
                	num_2 = peek(&stack);
                	push(&stack, num_2 * num_1);
                	//printf("%d\n", peek(&stack));
	            case O_DIV:
                	num_1 = peek(&stack);
                	pop(&stack);
                	num_2 = peek(&stack);
                	push(&stack, num_2 / num_1);
                	//printf("%d\n", peek(&stack));
    		   case PRINT:
			printf("%d ", peek(&stack));
			printf("%s\n", "Ok.");
		  /* default:
			printf("%s\n", "error"); */
	    }
        }
    }
}

int main() {
    puts("Forth version 0.0.1\n");
    puts("Press Ctrl+d to exit\n");

    stack_init(&stack);
    while (1) {
        char* input = readline(PROMT_STRING);
        scan(input);
        if (!input) {
            printf("\n");
            return 0;
        }
    }
}
