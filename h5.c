#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack implementation
char stack[MAX];
int top = -1;

void push(char symbol) {
    if (top >= MAX - 1) {
        printf("Stack Overflow!\n");
        exit(1);
    } else {
        stack[++top] = symbol;
    }
}

char pop() {
    if (top < 0) {
        printf("Stack Underflow!\n");
        exit(1);
    } else {
        return stack[top--];
    }
}

char peek() {
    return stack[top];
}

// Function to check if a character is a terminal
int isTerminal(char c) {
    return (c == 'i' || c == '+' || c == '*' || c == '(' || c == ')' || c == '$');
}

// Function to return production rule based on stack top and input symbol
const char* getProductionRule(char stackTop, char input) {
    if (stackTop == 'E' && (input == 'i' || input == '(')) return "TZ";
    if (stackTop == 'Z' && input == '+') return "+TZ";
    if (stackTop == 'Z' && (input == ')' || input == '$')) return "0";
    if (stackTop == 'T' && (input == 'i' || input == '(')) return "FX";
    if (stackTop == 'X' && input == '*') return "*FX";
    if (stackTop == 'X' && (input == '+' || input == ')' || input == '$')) return "0";
    if (stackTop == 'F' && input == 'i') return "i";
    if (stackTop == 'F' && input == '(') return "(E)";

    return NULL;
}

int main() {
    char input[MAX], action[30];
    int i = 0;

    // Read input string
    printf("Enter the input string to be parsed: ");
    scanf("%s", input);
    strcat(input, "$"); // Append end marker

    // Initialize stack with start symbol and end marker
    push('$');
    push('E');

    printf("\nStack\t\tInput\t\tAction\n");

    while (stack[top] != '$') {
        printf("\n");
        for (int j = 0; j <= top; j++)
            printf("%c", stack[j]);
        printf("\t\t%s", (input + i));

        char stackTop = pop();

        if (isTerminal(stackTop)) {
            if (stackTop == input[i]) {
                sprintf(action, "Matched %c", input[i]);
                i++;
            } else {
                sprintf(action, "Error");
                printf("\n%s", action);
                exit(1);
            }
        } else {
            const char* rule = getProductionRule(stackTop, input[i]);
            if (rule != NULL) {
                sprintf(action, "Apply rule %s", rule);
                int k = strlen(rule) - 1;
                while (k >= 0) {
                    if (rule[k] != '0' && rule[k] != ' ') push(rule[k]);
                    k--;
                }
            } else {
                sprintf(action, "Error");
                printf("\n%s", action);
                exit(1);
            }
        }
        printf("\t\t%s", action);
    }

    if (input[i] == '$') printf("\nInput string parsed successfully.\n");
    else printf("\nError in parsing the input string.\n");

    return 0;
}
