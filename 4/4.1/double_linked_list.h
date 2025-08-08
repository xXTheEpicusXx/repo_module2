#include "contacts.h"
typedef struct Node Node;

typedef struct Node
{
    Contact contact;
    Node *next;
    Node *prev;
} Node;

typedef struct DoubleLinkedList
{
    Node *head;
    Node *tail;
} DoubleLinkedList;

Node *initNode(Contact contact);
DoubleLinkedList *initList();
void addNode(DoubleLinkedList *list, Contact newContact);
void deleteNode(DoubleLinkedList *list, Contact contact);
void editNode(DoubleLinkedList *list, Contact oldContact, Contact newContact);
void printNode(DoubleLinkedList *list, Contact contact);
void clearList(DoubleLinkedList *list);
