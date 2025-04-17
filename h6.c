#include<stdio.h>
#include<string.h>

int main() {
    char reg[20];
    int q[20][3], i = 0, j = 1, len, a, b;

    // Initialize the transition table with 0s
    for (a = 0; a < 20; a++)
        for (b = 0; b < 3; b++)
            q[a][b] = 0;

    // Read the regular expression input
    scanf("%s", reg);
    printf("Given regular expression: %s\n", reg);

    len = strlen(reg);

    // Process the regular expression
    while (i < len) {
        if (reg[i] == 'a' && reg[i + 1] != '|' && reg[i + 1] != '*' && reg[i + 1] != '(') {
            q[j][0] = j + 1; // a transition
            j++;
        }
        if (reg[i] == 'b' && reg[i + 1] != '|' && reg[i + 1] != '*' && reg[i + 1] != '(') {
            q[j][1] = j + 1; // b transition
            j++;
        }
        if (reg[i] == 'e' && reg[i + 1] != '|' && reg[i + 1] != '*' && reg[i + 1] != '(') {
            q[j][2] = j + 1; // epsilon transition
            j++;
        }

        // Handling a | b
        if (reg[i] == 'a' && reg[i + 1] == '|' && reg[i + 2] == 'b') {
            q[j][2] = ((j + 1) * 10) + (j + 3); // epsilon transition to two states
            j++;
            q[j][0] = j + 1; // a transition
            j++;
            q[j][2] = j + 3; // epsilon transition
            j++;
            q[j][1] = j + 1; // b transition
            j++;
            q[j][2] = j + 1; // epsilon transition
            j++;
            i += 2;
        }

        // Handling b | a
        if (reg[i] == 'b' && reg[i + 1] == '|' && reg[i + 2] == 'a') {
            q[j][2] = ((j + 1) * 10) + (j + 3); // epsilon transition to two states
            j++;
            q[j][1] = j + 1; // b transition
            j++;
            q[j][2] = j + 3; // epsilon transition
            j++;
            q[j][0] = j + 1; // a transition
            j++;
            q[j][2] = j + 1; // epsilon transition
            j++;
            i += 2;
        }

        // Handling a* (Kleene star)
        if (reg[i] == 'a' && reg[i + 1] == '*') {
            q[j][2] = ((j + 1) * 10) + (j + 3); // epsilon transition
            j++;
            q[j][0] = j + 1; // a transition
            j++;
            q[j][2] = ((j + 1) * 10) + (j - 1); // epsilon transition looping back
            j++;
        }

        // Handling b* (Kleene star)
        if (reg[i] == 'b' && reg[i + 1] == '*') {
            q[j][2] = ((j + 1) * 10) + (j + 3); // epsilon transition
            j++;
            q[j][1] = j + 1; // b transition
            j++;
            q[j][2] = ((j + 1) * 10) + (j - 1); // epsilon transition looping back
            j++;
        }

        // Handling (a|b)* (Kleene star over parentheses)
        if (reg[i] == '(' && reg[i + 1] == 'a' && reg[i + 2] == '|' && reg[i + 3] == 'b' && reg[i + 4] == ')' && reg[i + 5] == '*') {
            q[j][2] = ((j + 1) * 10) + (j + 3); // epsilon transition
            j++;
            q[j][2] = ((j + 1) * 10) + (j + 5); // epsilon transition to next choice
            j++;
            q[j][0] = j + 1; // a transition
            j++;
            q[j][2] = j + 3; // epsilon transition
            j++;
            q[j][1] = j + 1; // b transition
            j++;
            q[j][2] = ((j + 1) * 10) + (j - 5); // epsilon transition looping back
            j++;
            i += 5;
        }

        i++;
    }

    // Print the transition table
    printf("\n\tTransition Table \n");
    printf("_\n");
    printf("Current State |\tInput |\tNext State");
    printf("\n_\n");
    for (i = 0; i <= j; i++) {
        if (q[i][0] != 0) printf("\n  q[%d]\t      |   a   |  q[%d]", i, q[i][0]);
        if (q[i][1] != 0) printf("\n  q[%d]\t      |   b   |  q[%d]", i, q[i][1]);
        if (q[i][2] != 0) {
            if (q[i][2] < 10) printf("\n  q[%d]\t      |   e   |  q[%d]", i, q[i][2]);
            else printf("\n  q[%d]\t      |   e   |  q[%d] , q[%d]", i, q[i][2] / 10, q[i][2] % 10);
        }
    }
    printf("\n_\n");

    return 0;
}
