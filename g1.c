#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Grammar rules
struct Rule {
    char left;
    char right[10];
};

// Stack and Input Buffer
char stack[MAX], input[MAX];
int top = -1, ip = 0;
struct Rule rules[] = {
    {'S', "aSb"},
    {'S', ""}
};

// Function to check if the current stack top matches any grammar rule
int checkForReduction() {
    for (int i = 0; i < 2; i++) {
        int len = strlen(rules[i].right);
        if (len <= top + 1) {
            int match = 1;
            for (int j = 0; j < len; j++) {
                if (stack[top - len + 1 + j] != rules[i].right[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                top = top - len;
                stack[++top] = rules[i].left;
                return 1;
            }
        }
    }
    return 0;
}

// Function to shift input to the stack
void shift() {
    stack[++top] = input[ip++];
}

int main() {
    printf("Enter the input string: ");
    scanf("%s", input);
    strcat(input, "$");

    stack[++top] = '0'; // Push initial state '0'

    while (1) {
        char currentInput = input[ip];
        if (currentInput == '$' && top == 1 && stack[top] == 'S') {
            printf("String Accepted\n");
            break;
        } else if (checkForReduction()) {
            // Reduce
            printf("Reducing...\n");
        } else {
            // Shift
            printf("Shifting...\n");
            shift();
        }

        if (top == -1) {
            printf("Error: Stack is empty!\n");
            break;
        }
    }

    return 0;
}

