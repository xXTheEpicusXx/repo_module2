#include "double_linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

DoubleLinkedList *list = NULL;

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
    if (list == NULL || list->head == NULL) {
        printf("Список пуст\n");
        return;
    }

    Node *current = list->head;
    Node *toDelete = NULL;
    while (current != NULL) {
        if (strcmp(current->contact.fullname.surname, contact.fullname.surname) == 0 &&
            strcmp(current->contact.fullname.name, contact.fullname.name) == 0 &&
            strcmp(current->contact.fullname.secondname, contact.fullname.secondname) == 0) {

            toDelete = current;
            break;
        }
        current = current->next;
    }

    if (toDelete == NULL) {
        printf("Контакт не найден\n");
        return;
    }
    if (toDelete->prev != NULL) {
        toDelete->prev->next = toDelete->next;
    } else {
        list->head = toDelete->next;
    }

    if (toDelete->next != NULL) {
        toDelete->next->prev = toDelete->prev;
    } else {
        list->tail = toDelete->prev;
    }
    free(toDelete);
    printf("Контакт удален\n");
}

void editNode(DoubleLinkedList *list, Contact oldContact, Contact newContact)
{
    if (list == NULL || list->head == NULL) return;
    deleteNode(list, oldContact);
    addNode(list, newContact);
}

Node* printNode(DoubleLinkedList *list, Contact contact)
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
    return tmp;
}
void clearList(DoubleLinkedList *list) {
    if (list == NULL) return;
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;

}
