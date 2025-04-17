#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LENGTH 100
#define MAX_OPERANDS 50
#define MAX_OPERATORS 50

typedef struct {
    char op;
    char arg1[10];
    char arg2[10];
    char result[10];
} Quadruple;

int getPrecedence(char op);
void generateIntermediateCode(char* expression);

int main() {
    char expression[MAX_EXPR_LENGTH];

    printf("Intermediate Code Generator\n");

    printf("Enter the expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = 0;
    generateIntermediateCode(expression);

    return 0;
}
void generateIntermediateCode(char* expression) {
    int len = strlen(expression);
    char* exp = expression;
    char operands[MAX_OPERANDS][10];
    char operators[MAX_OPERATORS];
    int operandCount = 0, operatorCount = 0;
    Quadruple* quads = NULL;
    int quadCount = 0;
    int tempVarCount = 1;

    if (len > 3) {
        for (int i = 0; i < len; i++) {
            if (isalnum(exp[i])) {

                char operand[10] = {0};
                int j = 0;
                while (isalnum(exp[i])) {
                    operand[j++] = exp[i++];
                }
                i--;
                strcpy(operands[operandCount++], operand);
            } else if (exp[i] != ' ') {

                operators[operatorCount++] = exp[i];
            }
        }
    }


    quads = (Quadruple*)malloc(sizeof(Quadruple) * operatorCount);

    for (int i = 0; i < operatorCount; i++) {

        int precedence = getPrecedence(operators[i]);

        quads[quadCount].op = operators[i];
        strcpy(quads[quadCount].arg1, operands[i]);
        strcpy(quads[quadCount].arg2, operands[i+1]);
        sprintf(quads[quadCount].result, "t%d", tempVarCount++);

        if (i < operatorCount - 1) {
            strcpy(operands[i+1], quads[quadCount].result);
        }

        quadCount++;
    }

    printf("\nIntermediate Code:\n");
    for (int i = 0; i < quadCount; i++) {
        printf("%s = %s %c %s\n", quads[i].result, quads[i].arg1, quads[i].op, quads[i].arg2);
    }

    free(quads);
}

int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}
