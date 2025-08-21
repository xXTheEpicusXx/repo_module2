#include "contacts.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

Contact contacts[ARR_SIZE] = {0};
int curSize = 0;

void safe_strcpy(char *dest, const char *src, size_t dest_size)
{
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

void add(Fullname fn, ...)
{
    if (curSize >= ARR_SIZE)
        return;

    Contact newContact = {0};
    newContact.fullname = fn;

    va_list fields;
    va_start(fields, fn);

    while (true)
    {
        char *field_type = va_arg(fields, char *);
        if (field_type == NULL)
            break;

        if (strcmp(field_type, "work") == 0)
        {
            newContact.work = va_arg(fields, Work);
        }
        else if (strcmp(field_type, "phone") == 0)
        {
            char *phone = va_arg(fields, char *);
            safe_strcpy(newContact.phone, phone, STR_LEN);
        }
        else if (strcmp(field_type, "email") == 0)
        {
            char *email = va_arg(fields, char *);
            safe_strcpy(newContact.email, email, STR_LEN);
        }
        else if (strcmp(field_type, "socials") == 0)
        {
            int n = va_arg(fields, int);
            if (n < 0 || n > ARR_SIZE)
                break;
            newContact.socialCnt = n;
            for (int i = 0; i < n; i++)
            {
                newContact.socNets[i] = va_arg(fields, SocialNetwork);
            }
        }
    }

    va_end(fields);
    contacts[curSize++] = newContact;
}

void edit(Fullname fn, ...)
{
    for (int i = 0; i < curSize; i++)
    {
        if (strcmp(contacts[i].fullname.surname, fn.surname) == 0 &&
            strcmp(contacts[i].fullname.name, fn.name) == 0)
        {

            va_list fields;
            va_start(fields, fn);

            while (true)
            {
                char *field_type = va_arg(fields, char *);
                if (field_type == NULL)
                    break;

                if (strcmp(field_type, "name") == 0)
                {
                    contacts[i].fullname = va_arg(fields, Fullname);
                }
                else if (strcmp(field_type, "work") == 0)
                {
                    contacts[i].work = va_arg(fields, Work);
                }
                else if (strcmp(field_type, "phone") == 0)
                {
                    char *phone = va_arg(fields, char *);
                    safe_strcpy(contacts[i].phone, phone, STR_LEN);
                }
                else if (strcmp(field_type, "email") == 0)
                {
                    char *email = va_arg(fields, char *);
                    safe_strcpy(contacts[i].email, email, STR_LEN);
                }
                else if (strcmp(field_type, "socials") == 0)
                {
                    int n = va_arg(fields, int);
                    if (n >= 0 && n <= ARR_SIZE)
                    {
                        contacts[i].socialCnt = n;
                        for (int j = 0; j < n; j++)
                        {
                            contacts[i].socNets[j] = va_arg(fields, SocialNetwork);
                        }
                    }
                }
            }

            va_end(fields);
            return;
        }
    }
}

void delete(Fullname fn)
{
    for (int i = 0; i < curSize; i++)
    {
        if (strcmp(contacts[i].fullname.surname, fn.surname) == 0 &&
            strcmp(contacts[i].fullname.name, fn.name) == 0)
        {

            for (int j = i; j < curSize - 1; j++)
            {
                contacts[j] = contacts[j + 1];
            }

            memset(&contacts[curSize - 1], 0, sizeof(Contact));
            curSize--;
            return;
        }
    }
}

void print_contact(const Contact *c)
{
    printf("ФИО: %s %s %s\n", c->fullname.surname, c->fullname.name, c->fullname.secondname);
    printf("Работа: %s, %s\n", c->work.place, c->work.post);
    printf("Телефон: %s\n", c->phone);
    printf("Email: %s\n", c->email);
    for (int i = 0; i < c->socialCnt; i++)
    {
        printf("%s: %s\n", c->socNets[i].name, c->socNets[i].link);
    }
    printf("\n");
}

void find_and_print(Fullname fn)
{
    int isFound = 0;
    for (int i = 0; i < curSize; i++)
    {
        if (strcmp(contacts[i].fullname.surname, fn.surname) == 0)
        {
            print_contact(&contacts[i]);
            isFound = 1;
        }
    }
    if (!isFound)
    {
        printf("%s %s %s: Не найдено\n", fn.surname, fn.name, fn.secondname);
    }
}
