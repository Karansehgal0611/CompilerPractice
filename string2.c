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

    while (lineCount < MAX_LINES) {
        if (fgets(line, MAX_LENGTH, stdin) == NULL) {
            break;
        }


        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            break;
        }


        strcat(input, line);
        strcat(input, " ");
        lineCount++;
    }

    struct Token tokens[MAX_LENGTH];
    int tokenCount = 0;

    tokenize(input, tokens, &tokenCount);
    printResults(tokens, tokenCount);

    return 0;
}

int isKeyword(const char* str) {

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


    const int numKeywords = sizeof(keywords) / sizeof(keywords[0]);


    for (int i = 0; i < numKeywords; ++i) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
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

    char seenKeywords[MAX_LENGTH][100] = {0};
    char seenOperators[MAX_LENGTH][100] = {0};
    char seenConstants[MAX_LENGTH][100] = {0};
    char seenPunctuations[MAX_LENGTH][100] = {0};
    char seenIdentifiers[MAX_LENGTH][100] = {0};

    printf("Keywords : [");
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == KEYWORD) {
            int isNew = 1;
            for (int j = 0; j < keywordCount; j++) {
                if (strcmp(seenKeywords[j], tokens[i].value) == 0) {
                    isNew = 0;
                    break;
                }
            }
            if (isNew) {
                if (keywordCount > 0) {
                    printf(", ");
                }
                printf("%s", tokens[i].value);
                strcpy(seenKeywords[keywordCount++], tokens[i].value);
            }
        }
    }
    printf("]");

    printf("\n----------------------------\n");
    printf("Operators : [");
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == OPERATOR) {
            int isNew = 1;
            for (int j = 0; j < operatorCount; j++) {
                if (strcmp(seenOperators[j], tokens[i].value) == 0) {
                    isNew = 0;
                    break;
                }
            }
            if (isNew) {
                if (operatorCount > 0) {
                    printf(", ");
                }
                printf("%s", tokens[i].value);
                strcpy(seenOperators[operatorCount++], tokens[i].value);
            }
        }
    }
    printf("]");

    printf("\n----------------------------\n");
    printf("Constants : [");
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == CONSTANT) {
            int isNew = 1;
            for (int j = 0; j < constantCount; j++) {
                if (strcmp(seenConstants[j], tokens[i].value) == 0) {
                    isNew = 0;
                    break;
                }
            }
            if (isNew) {
                if (constantCount > 0) {
                    printf(", ");
                }
                printf("%s", tokens[i].value);
                strcpy(seenConstants[constantCount++], tokens[i].value);
            }
        }
    }
    printf("]");

    printf("\n----------------------------\n");
    printf("Punctuations : [");
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == PUNCTUATION) {
            int isNew = 1;
            for (int j = 0; j < punctuationCount; j++) {
                if (strcmp(seenPunctuations[j], tokens[i].value) == 0) {
                    isNew = 0;
                    break;
                }
            }
            if (isNew) {
                if (punctuationCount > 0) {
                    printf(", ");
                }
                printf("%s", tokens[i].value);
                strcpy(seenPunctuations[punctuationCount++], tokens[i].value);
            }
        }
    }
    printf("]");

    printf("\n----------------------------\n");
    printf("Identifiers : [");
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == IDENTIFIER) {
            int isNew = 1;
            for (int j = 0; j < identifierCount; j++) {
                if (strcmp(seenIdentifiers[j], tokens[i].value) == 0) {
                    isNew = 0;
                    break;
                }
            }
            if (isNew) {
                if (identifierCount > 0) {
                    printf(", ");
                }
                printf("%s", tokens[i].value);
                strcpy(seenIdentifiers[identifierCount++], tokens[i].value);
            }
        }
    }
    printf("]");

    printf("\n----------------------------\n");
    printf("Total number of tokens are %d\n", tokenCount);
}
