#include <ctype.h>
#include <string.h>
#include "validation.h"

// allowMultipleSigns = 0 → allow at most ONE sign (+ or -)
// allowMultipleSigns = 1 → allow multiple signs (normalize later)
int isValidNumber(const char* str, int allowMultipleSigns) {
    if (!str || !*str) return 0;

    int signCount = 0;

    // Handle leading signs
    while (*str == '+' || *str == '-') {
        signCount++;
        str++;

        // must have digits after sign(s)
        if (!*str) return 0;

        // First operand rule: reject if more than one sign
        if (!allowMultipleSigns && signCount > 1) return 0;
    }

    // Remaining characters must be digits
    while (*str) {
        if (!isdigit((unsigned char)*str)) return 0;
        str++;
    }

    return 1;
}

// Check if operator is valid
int isValidOperator(const char *op) {
    if (!op || !*op) return 0;

    if (strcmp(op, "+") == 0) return 1;
    if (strcmp(op, "-") == 0) return 1;
    if (strcmp(op, "x") == 0 || strcmp(op, "*")== 0) return 1;
    if (strcmp(op, "/") == 0) return 1;

    return 0;
}
