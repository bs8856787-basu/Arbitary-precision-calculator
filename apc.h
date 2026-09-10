#ifndef APC_H
#define APC_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data);
void insertLast(Node **head, Node **tail, int data);
void printList(Node *head);
Node* reverseList(Node *head);

Node* addLists(Node *list1, Node *list2);

Node* subtractLists(Node *list1, Node *list2);
Node* multiplyLists(Node *list1, Node *list2);
Node* divideLists(Node *list1, Node *list2);
int compareLists(Node *list1, Node *list2);
#endif
