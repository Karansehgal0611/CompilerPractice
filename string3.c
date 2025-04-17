#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000
#define MAX_LINES 100

enum TokenType {
    KEYWORD,
    OPERATOR,
    CONSTANT,
    PUNCTUATION,
    IDENTIFIER
};

struct Token {
    enum TokenType type;
    char value[100];
};

int isKeyword(const char* str);
int isOperator(char ch);
int isPunctuation(char ch);
void tokenize(const char* input, struct Token* tokens, int* tokenCount);
void printResults(struct Token* tokens, int tokenCount);

int main() {
    char input[MAX_LINES * MAX_LENGTH] = {0};
    char line[MAX_LENGTH];
    int lineCount = 0;

    printf("Enter a string of C code (enter an empty line to stop):\n");

    // Read multiple lines of input
    while (lineCount < MAX_LINES) {
        if (fgets(line, MAX_LENGTH, stdin) == NULL) {
            break; // Stop if there's an input error
        }

        // Remove the newline character at the end of the line, if present
        line[strcspn(line, "\n")] = '\0';

        // Check if the line is empty
        if (strlen(line) == 0) {
            break; // Stop if an empty line is entered
        }

        // Concatenate the line into the input string
        strcat(input, line);
        strcat(input, " "); // Add a space to separate lines
        lineCount++;
    }

    struct Token tokens[MAX_LENGTH];
    int tokenCount = 0;

    tokenize(input, tokens, &tokenCount);
    printResults(tokens, tokenCount);

    return 0;
}

int isKeyword(const char* str) {
    // List of C keywords
    const char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "inline", "int", "long", "register", "restrict", "return",
        "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while", "_Alignas",
        "_Alignof", "_Atomic", "_Bool", "_Complex", "_Decimal128",
        "_Decimal32", "_Decimal64", "_Generic", "_Imaginary", "_Noreturn",
        "_Static_assert", "_Thread_local"
    };

    // Number of keywords
    const int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    // Check if the given string matches any of the keywords
    for (int i = 0; i < numKeywords; ++i) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1; // It is a keyword
        }
    }
    return 0; // Not a keyword
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>');
}

int isPunctuation(char ch) {
    return (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == ',' || ch == '.');
}

void tokenize(const char* input, struct Token* tokens, int* tokenCount) {
    char buffer[100];
    int bufferIndex = 0;
    *tokenCount = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (isalnum(input[i]) || input[i] == '_') {
            buffer[bufferIndex++] = input[i];
        } else {
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';
                if (isKeyword(buffer)) {
                    tokens[*tokenCount].type = KEYWORD;
                } else if (isdigit(buffer[0])) {
                    tokens[*tokenCount].type = CONSTANT;
                } else {
                    tokens[*tokenCount].type = IDENTIFIER;
                }
                strcpy(tokens[*tokenCount].value, buffer);
                (*tokenCount)++;
                bufferIndex = 0;
            }

            if (isOperator(input[i])) {
                tokens[*tokenCount].type = OPERATOR;
                tokens[*tokenCount].value[0] = input[i];
                tokens[*tokenCount].value[1] = '\0';
                (*tokenCount)++;
            } else if (isPunctuation(input[i])) {
                tokens[*tokenCount].type = PUNCTUATION;
                tokens[*tokenCount].value[0] = input[i];
                tokens[*tokenCount].value[1] = '\0';
                (*tokenCount)++;
            } else if (input[i] == '"') {
                int j = i + 1;
                while (input[j] != '"' && input[j] != '\0') {
                    j++;
                }
                if (input[j] == '"') {
                    tokens[*tokenCount].type = IDENTIFIER;
                    tokens[*tokenCount].value[0] = '"';
                    strncpy(tokens[*tokenCount].value + 1, input + i + 1, j - i - 1);
                    tokens[*tokenCount].value[j - i] = '"';
                    tokens[*tokenCount].value[j - i + 1] = '\0';
                    (*tokenCount)++;
                    i = j;
                }
            }
        }
    }
}

void printResults(struct Token* tokens, int tokenCount) {
    int keywordCount = 0, operatorCount = 0, constantCount = 0, punctuationCount = 0, identifierCount = 0;

    // Count each type of token
    for (int i = 0; i < tokenCount; i++) {
        switch (tokens[i].type) {
            case KEYWORD:
                keywordCount++;
                break;
            case OPERATOR:
                operatorCount++;
                break;
            case CONSTANT:
                constantCount++;
                break;
            case PUNCTUATION:
                punctuationCount++;
                break;
            case IDENTIFIER:
                identifierCount++;
                break;
        }
    }

    // Print counts
    printf("Keywords: %d\n", keywordCount);
    printf("Operators: %d\n", operatorCount);
    printf("Constants: %d\n", constantCount);
    printf("Punctuations: %d\n", punctuationCount);
    printf("Identifiers: %d\n", identifierCount);
    printf("Total number of tokens: %d\n", tokenCount);
}
