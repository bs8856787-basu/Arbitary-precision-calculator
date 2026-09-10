#include <stdio.h>
#include <string.h>
#include "apc.h"
#include "validation.h"

typedef struct {
    Node *digits;
    int sign; // +1 or -1
} BigInt;

Node* stringToList(const char *num) {
    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < strlen(num); i++) {
        insertLast(&head, &tail, num[i] - '0');
    }
    return head;
}

BigInt parseOperand(const char *str) {
    BigInt num;
    num.sign = 1;

    int minusCount = 0;
    while (*str == '+' || *str == '-') {
        if (*str == '-') minusCount++;
        str++;
    }
    if (minusCount % 2 != 0) num.sign = -1;

    num.digits = stringToList(str);
    return num;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./a.out <num1> <op> <num2>\n");
        return 1;
    }

    char *num1 = argv[1];
    char *op   = argv[2];
    char *num2 = argv[3];

    // First operand: only one sign allowed
    if (!isValidNumber(num1, 0)) {
        printf("Invalid input! First operand must have at most one sign.\n");
        return 1;
    }
    // Second operand: allow multiple signs
    if (!isValidNumber(num2, 1)) {
        printf("Invalid input! Second operand must have digits after signs.\n");
        return 1;
    }
    if (!isValidOperator(op)) {
        printf("Unsupported operator!\n");
        return 1;
    }

    BigInt a = parseOperand(num1);
    BigInt b = parseOperand(num2);

    Node *result = NULL;
    int resultSign = 1;

    if (strcmp(op, "+") == 0) {
        if (a.sign == b.sign) {
            result = addLists(a.digits, b.digits);
            resultSign = a.sign;
        } else {
            int cmp = compareLists(a.digits, b.digits);
            if (cmp >= 0) {
                result = subtractLists(a.digits, b.digits);
                resultSign = a.sign;
            } else {
                result = subtractLists(b.digits, a.digits);
                resultSign = b.sign;
            }
        }
    } else if (strcmp(op, "-") == 0) {
        if (a.sign != b.sign) {
            result = addLists(a.digits, b.digits);
            resultSign = a.sign;
        } else {
            int cmp = compareLists(a.digits, b.digits);
            if (cmp >= 0) {
                result = subtractLists(a.digits, b.digits);
                resultSign = a.sign;
            } else {
                result = subtractLists(b.digits, a.digits);
                resultSign = -a.sign;
            }
        }
    } else if (strcmp(op, "x") == 0 || strcmp(op, "*") == 0) {
        result = multiplyLists(a.digits, b.digits);
        resultSign = (a.sign == b.sign) ? 1 : -1;
    } else if (strcmp(op, "/") == 0) {
        result = divideLists(a.digits, b.digits);
        resultSign = (a.sign == b.sign) ? 1 : -1;
    }

    if (resultSign == -1) printf("-");
    printList(result);
    printf("\n");

    return 0;
}
