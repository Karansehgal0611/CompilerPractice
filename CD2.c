#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char category[50];
    char lexeme[100];
} Token;
Token getNextToken(char **input)
{
    Token token;
    int ch = **input;
    while (isspace(ch))
    {
        (*input)++;
        ch = **input;
    }
    if (ch == '\0')
    {
        strcpy(token.category, "END_OF_INPUT");
        strcpy(token.lexeme, "");
        return token;
    }
    if (isalpha(ch))
    {
        int i = 0;
        while (isalnum(ch) || ch == '_')
        {
            token.lexeme[i++] = ch;
            (*input)++;
            ch = **input;
        }
        token.lexeme[i] = '\0';
        strcpy(token.category, "identifier");
    }
    else if (isdigit(ch))
    {
        int i = 0;
        while (isdigit(ch))
        {
            token.lexeme[i++] = ch;
            (*input)++;
            ch = **input;
        }
        token.lexeme[i] = '\0';
        strcpy(token.category, "integer literal");
    }
    else if (ch == '+')
    {
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        strcpy(token.category, "addition operator");
        (*input)++;
    }
    else if (ch == '-')
    {
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        strcpy(token.category, "subtraction operator");
        (*input)++;
    }
    else if (ch == '*')
    {
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        strcpy(token.category, "multiplication operator");
        (*input)++;
    }
    else if (ch == '/')
    {
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        strcpy(token.category, "division operator");
        (*input)++;
    }
    else if (ch == '=')
    {
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        strcpy(token.category, "assignment operator");
        (*input)++;
    }
    else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == ',')
    {
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        strcpy(token.category, "delimiter");
        (*input)++;
    }
    else
    {
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        strcpy(token.category, "unknown");
        (*input)++;
    }
    return token;
}
int main()
{
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0';
        }
    }
    char *ptr = input;
    Token token;
    printf("Lexeme \t\t\t Token Category \n");
    printf("--------------------------------------------\n");
    do
    {
        token = getNextToken(&ptr);
        if (strcmp(token.category, "END_OF_INPUT") != 0)
        {
            printf("%-10s \t\t %s\n", token.lexeme, token.category);
        }
    } while (strcmp(token.category, "END_OF_INPUT") != 0);

    return 0;
}
