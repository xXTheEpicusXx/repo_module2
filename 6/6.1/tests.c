#include "tests.h"
#include "double_linked_list.h"
#include <stdio.h>

extern DoubleLinkedList *list;

#ifdef TEST_1
void test()
{
    Fullname fn = {"Саньков", "Андрей", "Иванович"};
    Work w = {"НГТУ", "Студент"};
    char p[] = "+79133896816";
    char e[] = "andreysankov2004@gmail.com";
    SocialNetwork sns[2];
    sns[0] = (SocialNetwork){"Whatsapp", "+79133896816"};
    sns[1] = (SocialNetwork){"Telegram", "@the_epicus"};
    add(fn, "work", w, "phone", p, "email", e, "socials", 2, sns[0], sns[1]);
    print(fn);
}

#elif TEST_2
void test()
{
    Fullname fn = {"Саньков", "Андрей", "Иванович"};
    Work w = {"НГТУ", "Студент"};
    char p[] = "+79133896816";
    char e[] = "andreysankov2004@gmail.com";
    SocialNetwork sns[2];
    sns[0] = (SocialNetwork){"Whatsapp", "+79133896816"};
    sns[1] = (SocialNetwork){"Telegram", "@the_epicus"};
    add(fn, "work", w, "phone", p, "email", e, "socials", 2, sns[0], sns[1]);
    print(fn);
    delete(fn);
    print(fn);
}

#elif TEST_3
void test()
{
    Fullname fn = {"Саньков", "Андрей", "Иванович"};
    Work w = {"НГТУ", "Студент"};
    char p[] = "+79133896816";
    char e[] = "andreysankov2004@gmail.com";
    SocialNetwork sns[2];
    sns[0] = (SocialNetwork){"Whatsapp", "+79133896816"};
    sns[1] = (SocialNetwork){"Telegram", "@the_epicus"};
    add(fn, "work", w, "phone", p, "email", e, "socials", 2, sns[0], sns[1]);
    print(fn);
    Fullname newName = {"Иванов", "Иван", "Иванович"};
    char newPhone[] = "+77777777777";
    edit(fn, "name", newName, "skip", "phone", newPhone, "skip", "skip");
    print(newName);
}

#elif TEST_4
void test()
{
    Fullname fn = {"Иванов", "Иван", "Иванович"};
    Work w = {"Элтекс", "Программист"};
    char p[] = "+78888888888";
    char e[] = "andreysankov2004@gmail.com";
    SocialNetwork sns[2];
    sns[0] = (SocialNetwork){"Whatsapp", "+78888888888"};
    add(fn, "work", w, "phone", p, "email", e, "socials", 1, sns[0]);
    print(fn);

    Fullname fn1 = {"Саньков", "Андрей", "Иванович"};
    Work w1 = {"НГТУ", "Студент"};
    char p1[] = "+79133896816";
    char e1[] = "andreysankov2004@gmail.com";
    SocialNetwork sns1[2];
    sns1[0] = (SocialNetwork){"Whatsapp", "+79133896816"};
    sns1[1] = (SocialNetwork){"Telegram", "@the_epicus"};
    add(fn1, "work", w1, "phone", p1, "email", e1, "socials", 2, sns1[0], sns1[1]);
    print(fn1);
    printf("%s", list->head->contact.fullname.surname);
    delete(fn);
    printf("%s", list->head->contact.fullname.surname);
}

#elif TEST_5
void test()
{
    Fullname fn = {"Иванов", "Иван", "Иванович"};
    Work w = {"Элтекс", "Программист"};
    char p[] = "+78888888888";
    char e[] = "ivan@gmail.com";
    SocialNetwork sns[2];
    sns[0] = (SocialNetwork){"Whatsapp", "+78888888888"};
    add(fn, "work", w, "phone", p, "email", e, "socials", 1, sns[0]);

    Fullname fn1 = {"Саньков", "Андрей", "Иванович"};
    Work w1 = {"НГТУ", "Студент"};
    char p1[] = "+79133896816";
    char e1[] = "andreysankov2004@gmail.com";
    SocialNetwork sns1[2];
    sns1[0] = (SocialNetwork){"Whatsapp", "+79133896816"};
    sns1[1] = (SocialNetwork){"Telegram", "@the_epicus"};
    add(fn1, "work", w1, "phone", p1, "email", e1, "socials", 2, sns1[0], sns1[1]);

    Fullname fn2 = {"Александров", "Александр", "Александрович"};
    Work w2 = {"Убер", "Таксист"};
    char p2[] = "+79999999999";
    char e2[] = "alesan4@gmail.com";
    SocialNetwork sns2[0];
    sns2[0] = (SocialNetwork){"VK", "@tutu"};
    add(fn2, "work", w2, "phone", p2, "email", e2, "socials", 1, sns2[0]);

    Fullname fn3 = {"NULL", "NULL", "NULL"};
    Work w3 = {"NULL", "NULL"};
    char p3[] = "0";
    char e3[] = "NULL";
    add(fn3, "work", w3, "phone", p3, "email", e3);

    printf("%s %s %s %s\n", list->head->contact.fullname.surname, list->head->next->contact.fullname.surname, list->head->next->next->contact.fullname.surname, list->head->next->next->next->contact.fullname.surname);
    delete(fn2);
    printf("%s %s %s %s\n", list->head->contact.fullname.surname, list->head->next->contact.fullname.surname, list->head->next->next->contact.fullname.surname, list->head->next->next->next->contact.fullname.surname);
    printf("%s\n", list->tail->contact.fullname.surname);
    print(fn3);
}
#endif
