#include "contacts.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

Contact contacts[ARR_SIZE];
int curSize = 0;

void contactsInit()
{
    for (int i = 0; i < ARR_SIZE; i++)
    {
        contacts[i].fullname.surname[0] = 0;
        contacts[i].fullname.name[0] = 0;
        contacts[i].fullname.secondname[0] = 0;
        contacts[i].work.place[0] = 0;
        contacts[i].work.post[0] = 0;
        contacts[i].phone[0] = 0;
        contacts[i].email[0] = 0;
        for (int j = 0; j < ARR_SIZE; j++)
        {
            contacts[i].socNets[j].name[0] = 0;
            contacts[i].socNets[j].link[0] = 0;
        }
    }
}

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
    contacts[curSize++] = newContact;
}
void edit(Fullname fn, ...)
{
    for (int i = 0; i < ARR_SIZE; i++)
    {
        if (strcmp(contacts[i].fullname.surname, fn.surname) == 0 && strcmp(contacts[i].fullname.name, fn.name) == 0)
        {

            va_list fields;
            va_start(fields, fn);
            if (strcmp(va_arg(fields, char *), "name") == 0)
            {
                contacts[i].fullname = va_arg(fields, Fullname);
            }
            if (strcmp(va_arg(fields, char *), "work") == 0)
            {
                contacts[i].work = va_arg(fields, Work);
            }
            if (strcmp(va_arg(fields, char *), "phone") == 0)
            {
                strcpy(contacts[i].phone, va_arg(fields, char *));
            }
            if (strcmp(va_arg(fields, char *), "email") == 0)
            {
                strcpy(contacts[i].email, va_arg(fields, char *));
            }
            if (strcmp(va_arg(fields, char *), "socials") == 0)
            {
                int n = va_arg(fields, int);
                contacts[i].socialCnt = n;
                for (int i = 0; i < n; i++)
                {
                    contacts[i].socNets[i] = va_arg(fields, SocialNetwork);
                }
            }
        }
    }
}
void delete(Fullname fn)
{
    int startMove = 0;
    for (int i = 0; i < ARR_SIZE; i++)
    {

        if (strcmp(contacts[i].fullname.surname, fn.surname) == 0 && strcmp(contacts[i].fullname.name, fn.name) == 0)
        {
            contacts[i].fullname.surname[0] = 0;
            contacts[i].fullname.name[0] = 0;
            contacts[i].fullname.secondname[0] = 0;
            contacts[i].work.place[0] = 0;
            contacts[i].work.post[0] = 0;
            contacts[i].phone[0] = 0;
            contacts[i].email[0] = 0;
            for (int j = 0; j < ARR_SIZE; j++)
            {
                contacts[i].socNets[j].name[0] = 0;
                contacts[i].socNets[j].link[0] = 0;
            }
            startMove = 1;
        }
        if (startMove)
        {
            if (i < ARR_SIZE - 1)
            {
                contacts[i] = contacts[i + 1];
            }
            else
            {
                contacts[i].fullname.surname[0] = 0;
                contacts[i].fullname.name[0] = 0;
                contacts[i].fullname.secondname[0] = 0;
                contacts[i].work.place[0] = 0;
                contacts[i].work.post[0] = 0;
                contacts[i].phone[0] = 0;
                contacts[i].email[0] = 0;
                for (int j = 0; j < ARR_SIZE; j++)
                {
                    contacts[i].socNets[j].name[0] = 0;
                    contacts[i].socNets[j].link[0] = 0;
                }
            }
        }
    }
}

void print(Fullname fn)
{
    for (int i = 0; i < ARR_SIZE; i++)
    {
        if (strcmp(contacts[i].fullname.surname, fn.surname) == 0 && strcmp(contacts[i].fullname.name, fn.name) == 0)
        {
            printf("ФИО: %s %s %s\n", contacts[i].fullname.surname, contacts[i].fullname.name, contacts[i].fullname.secondname);
            printf("Работа: %s, %s\n", contacts[i].work.place, contacts[i].work.post);
            printf("Телефон: %s\n", contacts[i].phone);
            printf("Эл. почта: %s\n", contacts[i].email);
            for (int j = 0; j < contacts[i].socialCnt; j++)
            {
                if (contacts[i].socNets[j].name[0] == 0)
                {
                    break;
                }
                printf("%s: %s\n", contacts[i].socNets[j].name, contacts[i].socNets[j].link);
            }
        }
    }
}
