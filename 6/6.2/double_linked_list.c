#include "double_linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Node *initNode(Contact contact)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->contact = contact;
    return newNode;
}
DoubleLinkedList *initList()
{
    DoubleLinkedList *list = malloc(sizeof(DoubleLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}
void addNode(DoubleLinkedList *list, Contact newContact)
{
    Node *newNode = initNode(newContact);
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {

        newNode->contact = newContact;
        if (strcmp(newNode->contact.fullname.surname, list->head->contact.fullname.surname) <= 0)
        {
            list->head->prev = newNode;
            newNode->next = list->head;
            list->head = newNode;
        }
        else if (strcmp(newNode->contact.fullname.surname, list->tail->contact.fullname.surname) >= 0)
        {
            list->tail->next = newNode;
            newNode->prev = list->tail;
            list->tail = newNode;
        }
        else if (strcmp(newNode->contact.fullname.surname, list->head->contact.fullname.surname) > 0)
        {
            Node *tmp = list->head;
            while (strcmp(newNode->contact.fullname.surname, tmp->contact.fullname.surname) > 0)
            {
                tmp = tmp->next;
            }
            tmp->prev->next = newNode;
            newNode->prev = tmp->prev;
            tmp->prev = newNode;
            newNode->next = tmp;
        }
    }
}
void deleteNode(DoubleLinkedList *list, Contact contact)
{
    Node *tmp = list->head;
    while (strcmp(tmp->contact.fullname.surname, contact.fullname.surname) != 0)
    {
        tmp = tmp->next;
    }
    if (strcmp(tmp->contact.fullname.surname, contact.fullname.surname) == 0)
    {

        if (tmp->prev == NULL)
        {
            list->head = tmp->next;
        }
        else
        {
            tmp->prev->next = tmp->next;
        }
        if (tmp->next == NULL)
        {
            list->tail = tmp->prev;
        }
        else
        {
            tmp->next->prev = tmp->prev;
        }
        free(tmp);
    }
}
void editNode(DoubleLinkedList *list, Contact oldContact, Contact newContact)
{
    Node *tmp = list->head;
    while (strcmp(tmp->contact.fullname.surname, oldContact.fullname.surname) != 0)
    {
        tmp = tmp->next;
    }
    if (strcmp(tmp->contact.fullname.surname, oldContact.fullname.surname) == 0)
    {
        deleteNode(list, oldContact);
        addNode(list, newContact);
    }
}
void printNode(DoubleLinkedList *list, Contact contact)
{
    Node *tmp = list->head;
    while (strcmp(tmp->contact.fullname.surname, contact.fullname.surname) != 0)
    {
        tmp = tmp->next;
    }
    if (strcmp(tmp->contact.fullname.surname, contact.fullname.surname) == 0)
    {

        printf("ФИО: %s %s %s\n", tmp->contact.fullname.surname, tmp->contact.fullname.name, tmp->contact.fullname.secondname);
        printf("Работа: %s, %s\n", tmp->contact.work.place, tmp->contact.work.post);
        printf("Телефон: %s\n", tmp->contact.phone);
        printf("Эл. почта: %s\n", tmp->contact.email);
        for (int j = 0; j < tmp->contact.socialCnt; j++)
        {
            if (tmp->contact.socNets[j].name[0] == 0)
            {
                break;
            }
            printf("%s: %s\n", tmp->contact.socNets[j].name, tmp->contact.socNets[j].link);
        }
    }
}
void clearList(DoubleLinkedList *list)
{
    Node *tmp = list->head;
    while (tmp->next != NULL)
    {
        deleteNode(list, tmp->contact);
        tmp = tmp->next;
    }
    free(list);
}
