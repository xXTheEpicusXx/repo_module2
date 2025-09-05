// #include "contacts.h"
#include "double_linked_list.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

extern DoubleLinkedList *list;

Node *add(Fullname fn, ...)
{
    Contact newContact;
    memset(&newContact, 0, sizeof(Contact));
    newContact.fullname = fn;

    va_list fields;
    va_start(fields, fn);

    char *field_type;
    while ((field_type = va_arg(fields, char *)) != NULL) {
        if (strcmp(field_type, "work") == 0) {
            newContact.work = va_arg(fields, Work);
        }
        else if (strcmp(field_type, "phone") == 0) {
            char *phone = va_arg(fields, char *);
            strncpy(newContact.phone, phone, sizeof(newContact.phone) - 1);
        }
        else if (strcmp(field_type, "email") == 0) {
            char *email = va_arg(fields, char *);
            strncpy(newContact.email, email, sizeof(newContact.email) - 1);
        }
        else if (strcmp(field_type, "socials") == 0) {
            int n = va_arg(fields, int);
            newContact.socialCnt = n > ARR_SIZE ? ARR_SIZE : n;
            for (int i = 0; i < newContact.socialCnt; i++) {
                newContact.socNets[i] = va_arg(fields, SocialNetwork);
            }
        }
    }
    va_end(fields);

    addNode(list, newContact);
    return list->tail;
}

Node *edit(Fullname fn, ...)
{
    Node *tmp = list->head;
    while (tmp != NULL) {
        if (strcmp(tmp->contact.fullname.surname, fn.surname) == 0 &&
            strcmp(tmp->contact.fullname.name, fn.name) == 0 &&
            strcmp(tmp->contact.fullname.secondname, fn.secondname) == 0) {
            break;
        }
        tmp = tmp->next;
    }

    if (tmp == NULL) return NULL;
    Contact oldContact = tmp->contact;
    Contact newContact = oldContact;

    va_list fields;
    va_start(fields, fn);

    char *field_type;
    while ((field_type = va_arg(fields, char *)) != NULL) {
        if (strcmp(field_type, "name") == 0) {
            newContact.fullname = va_arg(fields, Fullname);
        }
        else if (strcmp(field_type, "work") == 0) {
            newContact.work = va_arg(fields, Work);
        }
        else if (strcmp(field_type, "phone") == 0) {
            char *phone = va_arg(fields, char *);
            strncpy(newContact.phone, phone, sizeof(newContact.phone) - 1);
        }
        else if (strcmp(field_type, "email") == 0) {
            char *email = va_arg(fields, char *);
            strncpy(newContact.email, email, sizeof(newContact.email) - 1);
        }
        else if (strcmp(field_type, "socials") == 0) {
            int n = va_arg(fields, int);
            newContact.socialCnt = n > ARR_SIZE ? ARR_SIZE : n;
            for (int i = 0; i < newContact.socialCnt; i++) {
                newContact.socNets[i] = va_arg(fields, SocialNetwork);
            }
        }
    }
    va_end(fields);

    editNode(list, oldContact, newContact);
    return list->tail;
}

void del(Fullname fn)
{
    Contact contact;
    contact.fullname = fn;
    deleteNode(list, contact);
}

Node *print(Fullname fn)
{
    Contact contact;
    contact.fullname = fn;
    return printNode(list, contact);
}
