#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertLast(Node **head, Node **tail, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void printList(Node *head) {
    if (!head) {
        printf("0");
        return;
    }

    // Handle negative marker
    if (head->data == -1) {
        printf("-");
        head = head->next;
    }

    // Skip leading zeros
    while (head && head->data == 0) {
        head = head->next;
    }

    if (!head) {
        printf("0");
        return;
    }

    while (head) {
        printf("%d", head->data);
        head = head->next;
    }
}



Node* reverseList(Node *head) {
    Node *prev = NULL, *curr = head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

Node* addLists(Node *list1, Node *list2) {
    list1 = reverseList(list1);
    list2 = reverseList(list2);

    Node *result = NULL, *tail = NULL;
    int carry = 0;

    while (list1 || list2 || carry) {
        int sum = carry;
        if (list1) { sum += list1->data; list1 = list1->next; }
        if (list2) { sum += list2->data; list2 = list2->next; }

        insertLast(&result, &tail, sum % 10);
        carry = sum / 10;
    }

    return reverseList(result);
}
// Compare two lists: return 1 if list1 > list2, -1 if list1 < list2, 0 if equal
int compareLists(Node *list1, Node *list2) {
    // Count lengths
    int len1 = 0, len2 = 0;
    Node *t1 = list1, *t2 = list2;
    while (t1) { len1++; t1 = t1->next; }
    while (t2) { len2++; t2 = t2->next; }

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    // Same length → compare digit by digit
    while (list1 && list2) {
        if (list1->data > list2->data) return 1;
        if (list1->data < list2->data) return -1;
        list1 = list1->next;
        list2 = list2->next;
    }
    return 0;
}

Node* subtractLists(Node *list1, Node *list2) {
    int cmp = compareLists(list1, list2);
    int negative = 0;

    // Ensure list1 >= list2
    if (cmp < 0) {
        Node *tmp = list1;
        list1 = list2;
        list2 = tmp;
        negative = 1;
    } else if (cmp == 0) {
        Node *zero = createNode(0);
        return zero;
    }

    list1 = reverseList(list1);
    list2 = reverseList(list2);

    Node *result = NULL, *tail = NULL;
    int borrow = 0;

    while (list1) {
        int diff = list1->data - (list2 ? list2->data : 0) - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insertLast(&result, &tail, diff);

        list1 = list1->next;
        if (list2) list2 = list2->next;
    }

    result = reverseList(result);

    // Remove leading zeros
    while (result && result->data == 0 && result->next) {
        Node *temp = result;
        result = result->next;
        free(temp);
    }

    // If negative, insert a '-' node at the front
    if (negative) {
        Node *minus = createNode(-1); // special marker for '-'
        minus->next = result;
        result = minus;
    }

    return result;
}
Node* multiplyLists(Node *list1, Node *list2) {
    list1 = reverseList(list1);
    list2 = reverseList(list2);

    Node *result = createNode(0); // start with 0

    Node *ptr2 = list2;
    int shift = 0;

    while (ptr2) {
        int carry = 0;
        Node *partial = NULL, *tail = NULL;

        // Add leading zeros for shift
        for (int i = 0; i < shift; i++) {
            insertLast(&partial, &tail, 0);
        }

        Node *ptr1 = list1;
        while (ptr1) {
            int prod = ptr1->data * ptr2->data + carry;
            insertLast(&partial, &tail, prod % 10);
            carry = prod / 10;
            ptr1 = ptr1->next;
        }
        if (carry) insertLast(&partial, &tail, carry);

        partial = reverseList(partial);
        result = addLists(result, partial);

        ptr2 = ptr2->next;
        shift++;
    }

    // Remove leading zeros
    while (result && result->data == 0 && result->next) {
        Node *temp = result;
        result = result->next;
        free(temp);
    }

    return result;
}
Node* divideLists(Node *dividend, Node *divisor) {
    // Handle divide by zero
    if (!divisor || (divisor->data == 0 && !divisor->next)) {
        printf("Error: Division by zero\n");
        return createNode(0);
    }

    // If dividend < divisor → quotient = 0
    int cmp = compareLists(dividend, divisor);
    if (cmp < 0) {
        return createNode(0);
    }
    if (cmp == 0) {
        return createNode(1);
    }

    Node *quotient = NULL, *qTail = NULL;
    Node *remainder = NULL, *rTail = NULL;

    Node *ptr = dividend;
    while (ptr) {
        // Bring down next digit
        insertLast(&remainder, &rTail, ptr->data);

        // Remove leading zeros in remainder
        while (remainder && remainder->data == 0 && remainder->next) {
            Node *temp = remainder;
            remainder = remainder->next;
            free(temp);
        }

        // Count how many times divisor fits
        int count = 0;
        while (compareLists(remainder, divisor) >= 0) {
            remainder = subtractLists(remainder, divisor);
            count++;
        }

        insertLast(&quotient, &qTail, count);
        ptr = ptr->next;
    }

    // Remove leading zeros in quotient
    while (quotient && quotient->data == 0 && quotient->next) {
        Node *temp = quotient;
        quotient = quotient->next;
        free(temp);
    }

    return quotient;
}
