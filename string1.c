#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toUpperCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}
void stringCopy(char* dest, const char* src) {
    while ((*dest++ = *src++) != '\0');
}
int main() {
    char str1[100], str2[100], str3[200], strCopy[100];

    printf("Enter the first string (no spaces): ");
    scanf("%99s", str1);

    printf("Enter the second string (no spaces): ");
    scanf("%99s", str2);

    printf("\nLength of first string: %lu\n", strlen(str1));
    printf("Length of second string: %lu\n", strlen(str2));


    stringCopy(str3, str1);
    strcat(str3, str2);
    printf("\nConcatenated string: %s\n", str3);

    toUpperCase(str1);
    toUpperCase(str2);
    printf("\nUppercase of first string: %s\n", str1);
    printf("Uppercase of second string: %s\n", str2);

    stringCopy(strCopy, str1);
    printf("\nCopied first string: %s\n", strCopy);

    return 0;
}
