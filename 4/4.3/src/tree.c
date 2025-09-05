#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


static void clearTreeR(Node *node);

Node *initNode(Contact contact)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->contact = contact;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Tree *initTree()
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

static Node *addNodeR(Node *node, Contact contact)
{
    if (node == NULL)
    {
        return initNode(contact);
    }

    int cmp = strcmp(contact.fullname.surname, node->contact.fullname.surname);
    if (cmp <= 0)
    {
        node->left = addNodeR(node->left, contact);
    }
    else
    {
        node->right = addNodeR(node->right, contact);
    }

    return node;
}

void addNode(Tree *tree, Contact contact)
{
    if (tree == NULL)
        return;
    tree->root = addNodeR(tree->root, contact);
}

static Node *findMin(Node *node)
{
    while (node != NULL && node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

static Node *deleteNodeR(Node *node, Contact contact)
{
    if (node == NULL)
        return NULL;

    int cmp = strcmp(contact.fullname.surname, node->contact.fullname.surname);

    if (cmp < 0)
    {
        node->left = deleteNodeR(node->left, contact);
    }
    else if (cmp > 0)
    {
        node->right = deleteNodeR(node->right, contact);
    }
    else
    {
        if (node->left == NULL)
        {
            Node *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            Node *temp = node->left;
            free(node);
            return temp;
        }

        Node *temp = findMin(node->right);
        node->contact = temp->contact;
        node->right = deleteNodeR(node->right, temp->contact);
    }

    return node;
}

void deleteNode(Tree *tree, Contact contact)
{
    if (tree == NULL)
        return;
    tree->root = deleteNodeR(tree->root, contact);
}

void editNode(Tree *tree, Contact oldContact, Contact newContact)
{
    if (tree == NULL)
        return;
    deleteNode(tree, oldContact);
    addNode(tree, newContact);
}

static Node *searchNodeR(Node *node, Contact contact)
{
    if (node == NULL)
        return NULL;

    int cmp = strcmp(contact.fullname.surname, node->contact.fullname.surname);

    if (cmp < 0)
    {
        return searchNodeR(node->left, contact);
    }
    else if (cmp > 0)
    {
        return searchNodeR(node->right, contact);
    }
    else
    {
        return node;
    }
}

Node *copyNode(Tree *tree, Contact contact)
{
    if (tree == NULL)
        return NULL;
    Node *found = searchNodeR(tree->root, contact);
    return found;
}

void printNode(Tree *tree, Contact contact)
{
    if (tree == NULL)
        return;

    Node *found = searchNodeR(tree->root, contact);
    if (found != NULL)
    {
        printf("%s %s %s\n",
               found->contact.fullname.surname,
               found->contact.fullname.name,
               found->contact.fullname.secondname);
        printf("%s, %s\n",
               found->contact.work.place,
               found->contact.work.post);
        printf("%s\n", found->contact.phone);
        printf("%s\n", found->contact.email);

        for (int j = 0; j < found->contact.socialCnt; j++)
        {
            if (found->contact.socNets[j].name[0] == 0)
                break;
            printf("%s: %s\n",
                   found->contact.socNets[j].name,
                   found->contact.socNets[j].link);
        }
    }
}

static void bubbleSort(Contact *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (strcmp(arr[j].fullname.surname, arr[j + 1].fullname.surname) > 0)
            {
                Contact temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

static void treeToArr(Node *node, Contact *contacts, int *index)
{
    if (node == NULL)
        return;
    treeToArr(node->left, contacts, index);
    contacts[(*index)++] = node->contact;
    treeToArr(node->right, contacts, index);
}

static Node *buildBalancedTree(Contact *contacts, int start, int end)
{
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    Node *node = initNode(contacts[mid]);

    node->left = buildBalancedTree(contacts, start, mid - 1);
    node->right = buildBalancedTree(contacts, mid + 1, end);

    return node;
}
static void countNodes(Node *n, int *count)
{
    if (n != NULL)
    {
        (*count)++;
        countNodes(n->left, count);
        countNodes(n->right, count);
    }
}
void balanceTree(Tree *tree)
{
    if (tree == NULL || tree->root == NULL)
        return;

    int count = 0;

    countNodes(tree->root, &count);

    Contact *contacts = (Contact *)malloc(count * sizeof(Contact));
    int index = 0;
    treeToArr(tree->root, contacts, &index);

    bubbleSort(contacts, count);

    clearTreeR(tree->root);
    tree->root = buildBalancedTree(contacts, 0, count - 1);

    free(contacts);
}

static void inorderTraversalR(Node *node, int level, int is_last[])
{
    if (node == NULL)
        return;

    for (int i = 0; i < level - 1; i++)
    {
        printf(is_last[i] ? "    " : "│   ");
    }

    if (level > 0)
        printf(is_last[level - 1] ? "└── " : "├── ");

    if (level == 0)
        printf("\x1B[31m%s\x1B[0m\n", node->contact.fullname.surname);
    else
        printf("%s\n", node->contact.fullname.surname);

    is_last[level] = 0;
    inorderTraversalR(node->right, level + 1, is_last);
    is_last[level] = 1;
    inorderTraversalR(node->left, level + 1, is_last);
}

void inorderTraversal(Tree *tree)
{
    if (tree == NULL || tree->root == NULL)
        return;

    int is_last[100] = {0};
    inorderTraversalR(tree->root, 0, is_last);
}

static void clearTreeR(Node *node)
{
    if (node == NULL)
        return;
    clearTreeR(node->left);
    clearTreeR(node->right);
    free(node);
}

void clearTree(Tree *tree)
{
    if (tree == NULL)
        return;
    clearTreeR(tree->root);
    tree->root = NULL;
}
