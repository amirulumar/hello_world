#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct stack {
	char data[10];
	int top;
} stack;

int priority(char x); // Determines priority of incoming operator.
void push(stack *s, int item); // Pushes element to stack.
char pop(stack *s); // Pops element from stack.
int evaluate(char* init); // Evaluates postfix expression.
void empty(stack *s); // Empty stack.
char* infix_to_postfix(char* init);
char* infix_to_prefix(char* init);
char* postfix_to_infix(char* init);
char* postfix_to_prefix(char* init);
char* prefix_to_postfix(char* init);
char* prefix_to_infix(char* init);

int main() {
	int i, j, x, operand = 0, leftPar = 0, rightPar = 0;
	int expression;
	char choice, readChoice, userChoice;
    FILE *fp;
	char exp[50];
	char* in_to_post;
	char* in_to_pre;
	char* post_to_in;
	char* pre_to_in;
	char* post_to_pre;
	char* pre_to_post;
    printf("Would you like to:\nA) Read from file or\nB) Read from standard input?");
    scanf(" %c", readChoice);
    if (readChoice == 'a' || readChoice == 'A') {
        if ((fp = fopen("default.txt", "r")) == NULL); {
            printf("default.txt could not be found. The program will now close.\n");
            return 0;
        }
        else {
            fgets(exp, 50, fp);
            printf("%s\n", exp);
            fclose(fp);
        }
    }
    else if (readChoice == 'b' || readChoice == 'B') {
        fp = fopen("input.txt", "w");
        printf("Enter an expression: ");
        gets(exp);
        fprintf(fp, "%s", exp);
        fclose(fp);
    }
	for (i = 0; exp[i] != '\0'; i++) {
        if (isalnum(exp[i]) != 0)
            operand = operand + 1;
        else if (exp[i] == '(')
            leftPar = leftPar + 1;
        else if (exp[i] == ')')
            rightPar = rightPar + 1;
    }
    if (operand > 6){
        printf("Too many operands and operators. The program will now close.\n");
        return 0;
    }
    if (leftPar != rightPar) { // Parentheses imbalance specified by the number of left and right parentheses.
        printf("Imbalanced parentheses. The program will now close.\n");
        return 0;
    }
    while (1) { // Accepts as many inputs until told to break and close the program.
    	printf("A. Convert to infix, postfix or prefix.\nB. Evaluate to expression.\nC. Exit.\n");
    	scanf(" %c", &userChoice);
    	if (userChoice == 'c' || userChoice == 'C') {
    		printf("The program will now close.\n");
    		return 0;
    	}
		if (exp[0] == '(' || (isalnum(exp[0]) != 0 && (exp[1] == '+' || exp[1] == '-' || exp[1] == '/' || exp[1] == '*' || exp[1] == '^'))) {
		if (userChoice == 'a' || userChoice == 'A') {
    		printf("This is an infix expression; do you want to convert it to (A) postfix or (B) prefix or (C) for both? Select A, B or C option.");
        	scanf(" %c", &choice);
            if (readChoice == 'a' || readChoice == 'A') {
                fp = fopen("default.txt", "a");
                switch (choice) {
                    case 'a':
                    case 'A':
                        in_to_post = infix_to_postfix(exp);
                        fprintf(fp, "\nPostfix expression is %s.\n", in_to_post);
                        break;
                    case 'b':
                    case 'B':
                        in_to_pre = infix_to_prefix(exp);
                        fprintf(fp, "\nPrefix expression is %s.\n", in_to_pre);
                        break;
                    case 'c':
                    case 'C':
                        in_to_post = infix_to_postfix(exp);
                        fprintf(fp, "\nPostfix expression is %s.\n", in_to_post);
                        in_to_pre = infix_to_prefix(exp);
                        fprintf(fp, "\nPrefix expression is %s.\n", in_to_pre);
                        break;
                }
                fclose(fp);
            }
            else if (readChoice == 'b' || readChoice == 'B') {
                fp = fopen("output.txt", "w");
                switch (choice) {
                    case 'a':
                    case 'A':
                        in_to_post = infix_to_postfix(exp);
                        fprintf(fp, "Postfix expression is %s.\n", in_to_post);
                        break;
                    case 'b':
                    case 'B':
                        in_to_pre = infix_to_prefix(exp);
                        fprintf(fp, "Prefix expression is %s.\n", in_to_pre);
                        break;
                    case 'c':
                    case 'C':
                        in_to_post = infix_to_postfix(exp);
                        fprintf(fp, "Postfix expression is %s.\n", in_to_post);
                        in_to_pre = infix_to_prefix(exp);
                        fprintf(fp, "Prefix expression is %s.\n", in_to_pre);
                        break;
                }
                fclose(fp);
            }
        } else if (userChoice == 'b' || userChoice == 'B') {
			expression = evaluate(infix_to_postfix(exp));
            if (readChoice == 'a' || readChoice == 'A') {
                fp = fopen("default.txt", "a");
                fprintf(fp, "\nThe final answer is %d.\n", expression);
                fclose(fp);
            }
            else if (readChoice == 'b' || readChoice == 'B') {
                fp = fopen("output.txt", "a");
                fprintf(fp, "\nThe final answer is %d.\n", expression);
                fclose(fp);
            }
		}
    	} else if (isalnum(exp[0]) != 0 && isalnum(exp[1]) != 0) {
    	if (userChoice == 'a' || userChoice == 'A') {
        printf("This is a postfix expression; do you want to convert it to (A) infix or (B) prefix or (C) for both? Select A, B or C option.");
        scanf(" %c", &choice);
            if (readChoice == 'a' || readChoice == 'A') {
                fp = fopen("default.txt", "a");
                switch (choice) {
                    case 'a':
                    case 'A':
                        post_to_in = postfix_to_infix(exp);
                        fprintf(fp, "\nInfix expression is %s.\n", post_to_in);
                        break;
                    case 'b':
                    case 'B':
                        post_to_pre = postfix_to_prefix(exp);
                        fprintf(fp, "\nPrefix expression is %s.\n", post_to_pre);
                        break;
                    case 'c':
                    case 'C':
                        post_to_in = postfix_to_infix(exp);
                        fprintf(fp, "\nInfix expression is %s.\n", post_to_in);
                        post_to_pre = postfix_to_prefix(exp);
                        fprintf(fp, "\nPrefix expression is %s.\n", post_to_pre);
                        break;
                }
                fclose(fp);
            }
            else if (readChoice == 'b' || readChoice == 'B') {
                fp = fopen("output.txt", "w");
                switch (choice) {
                    case 'a':
                    case 'A':
                        post_to_in = postfix_to_infix(exp);
                        fprintf(fp, "Infix expression is %s.\n", post_to_in);
                        break;
                    case 'b':
                    case 'B':
                        post_to_pre = postfix_to_prefix(exp);
                        fprintf(fp, "Prefix expression is %s.\n", post_to_pre);
                        break;
                    case 'c':
                    case 'C':
                        post_to_in = postfix_to_infix(exp);
                        fprintf(fp, "Infix expression is %s.\n", post_to_in);
                        post_to_pre = postfix_to_prefix(exp);
                        fprintf(fp, "Prefix expression is %s.\n", post_to_pre);
                        break;
                }
                fclose(fp);
            }
		} else if (userChoice == 'b' || userChoice == 'B') {
			expression = evaluate(exp);
            if (readChoice == 'a' || readChoice == 'A') {
                fp = fopen("default.txt", "a");
                fprintf(fp, "\nThe final answer is %d.\n", expression);
                fclose(fp);
            }
            else if (readChoice == 'b' || readChoice == 'B') {
                fp = fopen("output.txt", "a");
                fprintf(fp, "\nThe final answer is %d.\n", expression);
                fclose(fp);
            }
		}
    } else if (exp[0] == '+' || exp[0] == '-' || exp[0] == '/' || exp[0] == '*' || exp[0] == '^') {
    	if (userChoice == 'a' || userChoice == 'A') {
        printf("This is a prefix expression; do you want to convert it to (A) infix or (B) postfix or (C) for both? Select A, B or C option.\n");
        scanf(" %c", &choice);
            if (readChoice == 'a' || readChoice == 'A') {
                fp = fopen("default.txt", "a");
                switch (choice) {
                    case 'a':
                    case 'A':
                        pre_to_in = prefix_to_infix(exp);
                        fprintf(fp, "\nInfix expression is %s.\n", pre_to_in);
                        break;
                    case 'b':
                    case 'B':
                        pre_to_post = prefix_to_postfix(exp);
                        fprintf(fp, "\nInfix expression is %s.\n", pre_to_post);
                        break;
                    case 'c':
                    case 'C':
                        pre_to_in = prefix_to_infix(exp);
                        fprintf(fp, "\nInfix expression is %s.\n", pre_to_in);
                        pre_to_post = prefix_to_postfix(exp);
                        fprintf(fp, "\nPostfix expression is %s.\n", pre_to_post);
                        break;
                }
                fclose(fp);
            }
            else if (readChoice == 'b' || readChoice == 'B') {
                fp = fopen("output.txt", "w");
                switch (choice) {
                    case 'a':
                    case 'A':
                        pre_to_in = prefix_to_infix(exp);
                        fprintf(fp, "Infix expression is %s.\n", pre_to_in);
                        break;
                    case 'b':
                    case 'B':
                        pre_to_post = prefix_to_postfix(exp);
                        fprintf(fp, "Infix expression is %s.\n", pre_to_post);
                        break;
                    case 'c':
                    case 'C':
                        pre_to_in = prefix_to_infix(exp);
                        fprintf(fp, "Infix expression is %s.\n", pre_to_in);
                        pre_to_post = prefix_to_postfix(exp);
                        fprintf(fp, "Postfix expression is %s.\n", pre_to_post);
                        break;
                }
                fclose(fp);
            }
   		} else if (userChoice == 'b' || userChoice == 'B') {
   			expression = evaluate(prefix_to_postfix(exp));
            if (readChoice == 'a' || readChoice == 'A') {
                fp = fopen("default.txt", "a");
                fprintf(fp, "\nThe final answer is %d.\n", expression);
                fclose(fp);
            }
            else if (readChoice == 'b' || readChoice == 'B') {
                fp = fopen("output.txt", "a");
                fprintf(fp, "\nThe final answer is %d.\n", expression);
                fclose(fp);
            }
    	} 
    }
    }
}
char* infix_to_postfix(char* init) {
	static char result[50];
	char *x = &init[0], *z = &result[0];
	char y;
 	stack list;
 	empty(&list);
	while (*x != '\0') {
       	if (isdigit(*x)) {
           	*z = *x; // Operand printed out immediately.
           	z++;
        } else if (*x == ' ') {
            *z = ' ';
            z++;
       	} else if (*x == '(')
           	push(&list, *x); // '(' character pushed.
       	else if (*x == ')') {
           	while ((y = pop(&list)) != '(') {
            	*z = y; // Popping elements from stack until reaching '('.
            	z++;
           	}
        } else {
            while (priority(*x) <= priority(list.data[list.top])) {// If expression operator has higher precedence than stack operator, expression operator is pushed onto stack. Else stack operator is popped and printed out.
                *z = pop(&list);
                z++;
            }
            push(&list, *x);
        }
        x++;
	}
	while (list.top != -1) {
        *z = pop(&list); z++;// Remaining operators printed out.
        *z = ' '; z++;
	}
	return result;
}

char* infix_to_prefix(char* init) {
    static char result[50];
	char *x = &init[0], *z = &result[0];
    char y;
    stack list;
	empty(&list);
    strrev(init);
    while (*x != '\0') {
   		if (isdigit(*x)) {
     		*z = *x; // Operand printed out immediately.
     		z++;
        } else if (*x == ' ') {
            *z = ' ';
            z++;
       	} else if (*x == ')')
            push(&list, *x); // Similar to '(' character in postfix conversion but applies to the reversed expression.
        else if (*x == '(') {
        	while ((y = pop(&list)) != ')') {
       			*z = y; // Popping elements from stack until reaching ')'
       			z++;
        	}
        } else {
        	while (priority(*x) <= priority(list.data[list.top])) {
         		*z = pop(&list);
         		z++;
        	}
           	push(&list, *x);
        } 
		x++;
  	}
    while (list.top != -1) {
        *z = pop(&list); z++;
        *z = ' '; z++;
    }
    strrev(result);
    return result;
}

char* postfix_to_infix(char* init) {
    static char result[50];
	char *x = &init[0], *z = &result[0];
    char operand, operators;
    stack list;
    empty(&list);
    *z = *x;
    z++; x++;
    while (*x != '\0') {
		if (isdigit(*x))
            push(&list, *x);
        else if (*x == ' ') {
            *z = ' ';
            z++;
       	}
        else if (*x == '-' || *x == '/' || *x == '*'|| *x == '+' || *x == '^') {
            operand = pop(&list);
            operators = *x;
            *z = operators; z++;
            *z = operand; z++;
        } 
        x++;
    }
    *z = init[list.top--]; z++;
    return result;
}

char* postfix_to_prefix(char* init) {
	return strrev(init); // Postfix conversion to prefix is simply a reversed string.
}

char* prefix_to_infix(char* init) {
	static char result[50];
	char *x = &init[0], *z = &result[0];
    char operand, operators;
    stack list;
    empty(&list);
    while (*x != '\0') {
		if (*x == '-' || *x == '/' || *x == '*'|| *x == '+' || *x == '^')
            push(&list, *x);
        else if (*x == ' ') {
            *z = ' ';
            z++;
       	}
		else if (isdigit(*x)) {
			operators = pop(&list);
            operand = *x;
            *z = operand; z++;
            *z = operators; z++;
		}
        x++;
    }
    *z = init[list.top--]; z++;
    return result;
}

char* prefix_to_postfix(char* init) {
	return strrev(init); // Prefix conversion to postfix is simply a reversed string.
}


int priority(char x) {
    int precedence = 0;
    if (x == '(')
        precedence = 0;
    if (x == '+' || x == '-')
        precedence = 1;
    if (x == '*' || x == '/')
        precedence = 2;
    if (x == '^')
        precedence = 3;
    return precedence;
}

void push(stack* s, int item) {
	++s->top;
    s->data[s->top] = item;
}

char pop(stack* s) {
    char item;
    item = s->data[s->top];
    --s->top;
    return item;
}

void empty(stack* s) {
	s->top = -1;
}

int evaluate(char* init) {
    int n1, n2, n3 = 0, num;
    char *x = &init[0];
    stack list;
    empty(&list);
    while(*x != '\0') {
        if(isdigit(*x)) {
            num = *x - '0';
            push(&list, num);
        } else if (*x == ' ')
            x++;
        else {
            n1 = pop(&list);
            n2 = pop(&list);
            switch(*x) {
                case '+':
                    n3 = n1 + n2;
                    break;
                case '-':
                    n3 = n2 - n1;
                    break;
                case '*':
                    n3 = n1 * n2;
                    break;
                case '/':
                    n3 = n2 / n1;
                    break;
                case '^':
                	n3 = (int)pow(n2, n1);
                	break;
            }
            push(&list, n3);
        }
        x++;
    }
    return pop(&list);
}
