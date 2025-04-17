#include <stdio.h>
#include <string.h>

struct op {
    char l;
    char r[10];
} op[10], pr[10];

// Function to check if the left side of an expression is used anywhere
int isUsed(char var, struct op op[], int n) {
    for (int i = 0; i < n; i++) {
        if (strchr(op[i].r, var)) {
            return 1;  // If found, return 1 (used)
        }
    }
    return 0;  // Not used
}

// Function to eliminate dead code
void deadCodeElimination(struct op op[], int *n) {
    int used[10] = {0};  // Array to mark used expressions

    // Mark expressions that are used
    for (int i = 0; i < *n; i++) {
        if (isUsed(op[i].l, op, *n)) {
            used[i] = 1;
        }
    }

    // Eliminate dead code
    int newIdx = 0;
    for (int i = 0; i < *n; i++) {
        if (used[i]) {
            op[newIdx++] = op[i];
        }
    }

    *n = newIdx;  // Update number of expressions
}

// Function to eliminate common subexpressions
void commonExpressionElimination(struct op op[], int *n) {
    for (int i = 0; i < *n; i++) {
        for (int j = i + 1; j < *n; j++) {
            // Check for common subexpression
            if (strcmp(op[i].r, op[j].r) == 0) {
                char common = op[j].l;
                op[j].l = op[i].l;  // Replace with the same variable
                for (int k = 0; k < *n; k++) {
                    // Replace common expression in other places
                    char *p = strchr(op[k].r, common);
                    if (p) {
                        *p = op[i].l;  // Replace with the optimized variable
                    }
                }
            }
        }
    }
}

// Function to print the expressions
void printCode(struct op op[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%c = %s\n", op[i].l, op[i].r);
    }
}

// Function to print the optimized code (removes duplicates)
void printOptimizedCode(struct op op[], int n) {
    int printed[10] = {0};  // Array to track printed expressions

    for (int i = 0; i < n; i++) {
        // Check if this expression has already been printed
        int isDuplicate = 0;
        for (int j = 0; j < i; j++) {
            if (op[i].l == op[j].l && strcmp(op[i].r, op[j].r) == 0) {
                isDuplicate = 1;
                break;
            }
        }

        // Print the expression only if it's not a duplicate
        if (!isDuplicate) {
            printf("%c = %s\n", op[i].l, op[i].r);
        }
    }
}

int main() {
    int n;

    printf("Enter the Number of Expressions: ");
    scanf("%d", &n);

    // Input the expressions
    for (int i = 0; i < n; i++) {
        printf("Enter left variable (e.g., a): ");
        scanf(" %c", &op[i].l);
        printf("Enter right expression (e.g., b+c): ");
        scanf(" %s", op[i].r);
    }

    printf("\nIntermediate Code:\n");
    printCode(op, n);

    // Apply Dead Code Elimination
    deadCodeElimination(op, &n);
    printf("\nAfter Dead Code Elimination:\n");
    printCode(op, n);

    // Apply Common Expression Elimination
    commonExpressionElimination(op, &n);
    printf("\nAfter Common Expression Elimination:\n");
    printCode(op, n);

    // Print the Optimized Code (removes duplicates)
    printf("\nOptimized Code:\n");
    printOptimizedCode(op, n);

    return 0;
}

