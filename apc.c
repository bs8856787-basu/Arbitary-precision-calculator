#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertLast(Node **head, Node **tail, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void printList(Node *head) {
    Node *temp = head;
    while (temp) {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
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
    // Reverse both lists to start from least significant digit
    list1 = reverseList(list1);
    list2 = reverseList(list2);

    Node *result = NULL, *tail = NULL;
    int carry = 0;

    while (list1 || list2 || carry) {
        int sum = carry;
        if (list1) {
            sum += list1->data;
            list1 = list1->next;
        }
        if (list2) {
            sum += list2->data;
            list2 = list2->next;
        }
        insertLast(&result, &tail, sum % 10);
        carry = sum / 10;
    }

    // Reverse result back to forward order
    result = reverseList(result);
    return result;
}

Node* subtractLists(Node *list1, Node *list2) { return NULL; }
Node* multiplyLists(Node *list1, Node *list2) { return NULL; }
Node* divideLists(Node *list1, Node *list2) { return NULL; }
