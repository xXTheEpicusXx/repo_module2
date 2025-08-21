#include "database.h"
#include "contacts.h"
#include <stdio.h>

void test1()
{
    Fullname fn = {"Иванов", "Иван", "Иванович"};
    Work w = {"Элтекс", "Программист"};
    char p[] = "+78888888888";
    char e[] = "ivan@gmail.com";
    SocialNetwork sn = {"Whatsapp", "+78888888888"};
    add(fn, "work", w, "phone", p, "email", e, "socials", 1, sn, NULL);

    Fullname fn1 = {"Саньков", "Андрей", "Иванович"};
    Work w1 = {"НГТУ", "Студент"};
    char p1[] = "+79133896816";
    char e1[] = "andreysankov2004@gmail.com";
    SocialNetwork sn1[] = {{"Whatsapp", "+79133896816"}, {"Telegram", "@the_epicus"}};
    add(fn1, "work", w1, "phone", p1, "email", e1, "socials", 2, sn1[0], sn1[1], NULL);

    Fullname fn2 = {"Александров", "Александр", "Александрович"};
    Work w2 = {"Убер", "Таксист"};
    char p2[] = "+79999999999";
    char e2[] = "alesan4@gmail.com";
    SocialNetwork sn2 = {"VK", "@tutu"};
    add(fn2, "work", w2, "phone", p2, "email", e2, "socials", 1, sn2, NULL);

    Fullname fn3 = {"NULL", "NULL", "NULL"};
    Work w3 = {"NULL", "NULL"};
    char p3[] = "0";
    char e3[] = "NULL";
    add(fn3, "work", w3, "phone", p3, "email", e3, NULL);

    find_and_print(fn);
    find_and_print(fn1);
    find_and_print(fn2);
    find_and_print(fn3);
}

void test2()
{
    Fullname fn = {"Иванов", "Иван", "Иванович"};
    Fullname fn1 = {"Саньков", "Андрей", "Иванович"};
    Fullname fn2 = {"Александров", "Александр", "Александрович"};
    Fullname fn3 = {"NULL", "NULL", "NULL"};
    delete(fn2);
    find_and_print(fn);
    find_and_print(fn1);
    find_and_print(fn2);
    find_and_print(fn3);
}

int main()
{
    printf("===============test_1===============\n");
    int fd = openDB("contacts.dat");
    test1();
    closeDB(fd);

    fd = openDB("contacts.dat");
    printf("===============test_2===============\n");
    test2();
    closeDB(fd);
    return 0;
}
