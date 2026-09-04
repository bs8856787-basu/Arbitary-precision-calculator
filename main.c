#include <stdio.h>
#include <string.h>
#include "apc.h"
#include "validation.h"

Node* stringToList(const char *num) {
    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < strlen(num); i++) {
        insertLast(&head, &tail, num[i] - '0');
    }
    return head;
}

int main() {
    char num1[100], num2[100];

    printf("Enter first number: ");
    scanf("%s", num1);
    printf("Enter second number: ");
    scanf("%s", num2);

    if (!isValidNumber(num1) || !isValidNumber(num2)) {
        printf("Invalid input! Only digits allowed.\n");
        return 1;
    }

    Node *list1 = stringToList(num1);
    Node *list2 = stringToList(num2);

    Node *sum = addLists(list1, list2);

    printf("Sum: ");
    printList(sum);

    return 0;
}
