// #include "contacts.h"
#include "double_linked_list.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

extern DoubleLinkedList *list;

void add(Fullname fn, ...)
{
    Contact newContact;
    newContact.fullname = fn;
    va_list fields;
    va_start(fields, fn);
    if (strcmp(va_arg(fields, char *), "work") == 0)
    {
        newContact.work = va_arg(fields, Work);
    }
    if (strcmp(va_arg(fields, char *), "phone") == 0)
    {
        strcpy(newContact.phone, va_arg(fields, char *));
    }
    if (strcmp(va_arg(fields, char *), "email") == 0)
    {
        strcpy(newContact.email, va_arg(fields, char *));
    }
    if (strcmp(va_arg(fields, char *), "socials") == 0)
    {
        int n = va_arg(fields, int);
        newContact.socialCnt = n;
        for (int i = 0; i < n; i++)
        {
            newContact.socNets[i] = va_arg(fields, SocialNetwork);
        }
    }
    addNode(list, newContact);
}
void edit(Fullname fn, ...)
{
    Contact oldContact, newContact;
    oldContact.fullname = fn;
    Node *tmp = list->head;
    while (strcmp(tmp->contact.fullname.surname, oldContact.fullname.surname) != 0)
    {
        tmp = tmp->next;
    }
    if (strcmp(tmp->contact.fullname.surname, oldContact.fullname.surname) == 0)
    {
        oldContact = tmp->contact;
    }
    va_list fields;
    va_start(fields, fn);
    if (strcmp(va_arg(fields, char *), "name") == 0)
    {
        newContact.fullname = va_arg(fields, Fullname);
    }
    else
    {
        newContact.fullname = oldContact.fullname;
    }
    if (strcmp(va_arg(fields, char *), "work") == 0)
    {
        newContact.work = va_arg(fields, Work);
    }
    else
    {
        newContact.work = oldContact.work;
    }
    if (strcmp(va_arg(fields, char *), "phone") == 0)
    {
        strcpy(newContact.phone, va_arg(fields, char *));
    }
    else
    {
        strcpy(newContact.phone, oldContact.phone);
    }
    if (strcmp(va_arg(fields, char *), "email") == 0)
    {
        strcpy(newContact.email, va_arg(fields, char *));
    }
    else
    {
        strcpy(newContact.email, oldContact.email);
    }
    if (strcmp(va_arg(fields, char *), "socials") == 0)
    {

        int n = va_arg(fields, int);
        newContact.socialCnt = n;
        if (n > 0)
        {
            for (int i = 0; i < n; i++)
            {
                newContact.socNets[i] = va_arg(fields, SocialNetwork);
            }
        }
    }
    else
    {

        int n = oldContact.socialCnt;
        newContact.socialCnt = n;
        for (int i = 0; i < n; i++)
        {
            newContact.socNets[i] = oldContact.socNets[i];
        }
    }
    editNode(list, oldContact, newContact);
}
void delete(Fullname fn)
{
    Contact contact;
    contact.fullname = fn;
    deleteNode(list, contact);
}

void print(Fullname fn)
{
    Contact contact;
    contact.fullname = fn;
    printNode(list, contact);
}
