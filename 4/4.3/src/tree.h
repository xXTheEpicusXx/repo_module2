#include "contacts.h"
typedef struct Node Node;

typedef struct Node
{
    Contact contact;
    Node *right;
    Node *left;
} Node;

typedef struct Tree
{
    Node *root;
} Tree;

Node *initNode(Contact contact);
Tree *initTree();
void addNode(Tree *tree, Contact contact);
void deleteNode(Tree *tree, Contact contact);
void editNode(Tree *tree, Contact oldContact, Contact newContact);
void printNode(Tree *tree, Contact contact);
Node *copyNode(Tree *tree, Contact contact);
void inorderTraversal(Tree *tree);
void balanceTree(Tree *tree);
void clearTree(Tree *tree);
