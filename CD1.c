#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYMBOLS 100
#define MAX_NAME_LENGTH 50
#define MAX_INPUT_LENGTH 1000

typedef struct {
    char name[MAX_NAME_LENGTH];
    char type[20];
    void* address;
    size_t size;
} Symbol;

Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

void insertSymbol(const char* name, const char* type, size_t size) {
    if (symbolCount >= MAX_SYMBOLS) {
        printf("Symbol table is full.\n");
        return;
    }

    // Check if symbol already exists
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return; // Symbol already exists, don't insert again
        }
    }

    strcpy(symbolTable[symbolCount].name, name);
    strcpy(symbolTable[symbolCount].type, type);
    symbolTable[symbolCount].size = size;
    symbolTable[symbolCount].address = malloc(size);

    if (symbolTable[symbolCount].address == NULL) {
        printf("Memory allocation failed for symbol %s.\n", name);
        return;
    }

    symbolCount++;
}

void displaySymbolTable() {
    printf("\nSymbol Table:\n");
    printf("%-20s %-10s %-15s %s\n", "Name", "Type", "Address", "Size");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%-20s %-10s %-15p %zu\n",
               symbolTable[i].name,
               symbolTable[i].type,
               symbolTable[i].address,
               symbolTable[i].size);
    }
}

int isOperator(const char* str) {
    return (strlen(str) == 1 && strchr("+-*/", str[0])) ||
           (strcmp(str, "AND") == 0) ||
           (strcmp(str, "OR") == 0) ||
           (strcmp(str, "NOT") == 0);
}

void tokenizeAndInsert(const char* input) {
    char token[MAX_NAME_LENGTH] = "";
    int tokenIndex = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (islower(input[i])) {
            // Symbol (single lowercase letter)
            token[0] = input[i];
            token[1] = '\0';
            insertSymbol(token, "int", sizeof(int));
        } else if (strchr("+-*/", input[i])) {
            // Operator (single character)
            token[0] = input[i];
            token[1] = '\0';
            insertSymbol(token, "operator", sizeof(char));
        } else if (isupper(input[i])) {
            // Start of a potential operator (AND, NOT, OR)
            tokenIndex = 0;
            while (isupper(input[i]) && tokenIndex < MAX_NAME_LENGTH - 1) {
                token[tokenIndex++] = input[i++];
            }
            token[tokenIndex] = '\0';
            i--; // Move back one character as the loop will increment

            if (isOperator(token)) {
                insertSymbol(token, "operator", sizeof(char));
            }
        }
        // Ignore other characters (like spaces)
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];

    printf("Enter expression (terminate with '$'):\n");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline

    if (strcmp(input, "$") == 0) {
        printf("No input provided.\n");
        return 0;
    }

    tokenizeAndInsert(input);

    displaySymbolTable();

    // Clean up allocated memory
    for (int i = 0; i < symbolCount; i++) {
        free(symbolTable[i].address);
    }

    return 0;
}
