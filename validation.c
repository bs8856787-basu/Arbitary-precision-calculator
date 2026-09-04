#include <ctype.h>
#include "validation.h"

// Check if string contains only digits
int isValidNumber(const char *str) {
    if (!str || !*str) return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}
