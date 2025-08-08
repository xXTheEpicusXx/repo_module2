#include "tests.h"
#include "tree.h"
#include <stdio.h>

extern Tree *tree;

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
    inorderTraversal(tree);
    delete(fn);
    inorderTraversal(tree);
}

#elif TEST_5
void test()
{
    Fullname fn = {"Иванов", "Иван", "Иванович"};
    Work w = {"Элтекс", "Программист"};
    char p[] = "+78888888888";
    char e[] = "andreysankov2004@gmail.com";
    SocialNetwork sns[2];
    sns[0] = (SocialNetwork){"Whatsapp", "+78888888888"};
    add(fn, "work", w, "phone", p, "email", e, "socials", 1, sns[0]);

    Fullname fn1 = {"Смирнов", "Иван", "Иванович"};
    Work w1 = {"Элтекс", "Программист"};
    char p1[] = "+78888888888";
    char e1[] = "andreysankov2004@gmail.com";
    SocialNetwork sns1[2];
    sns1[0] = (SocialNetwork){"Whatsapp", "+78888888888"};
    add(fn1, "work", w1, "phone", p1, "email", e1, "socials", 1, sns1[0]);

    Fullname fn2 = {"Кузнецов", "Иван", "Иванович"};
    Work w2 = {"Элтекс", "Программист"};
    char p2[] = "+78888888888";
    char e2[] = "andreysankov2004@gmail.com";
    SocialNetwork sns2[2];
    sns2[0] = (SocialNetwork){"Whatsapp", "+78888888888"};
    add(fn2, "work", w2, "phone", p2, "email", e2, "socials", 1, sns2[0]);

    Fullname fn3 = {"Саньков", "Иван", "Иванович"};
    Work w3 = {"Элтекс", "Программист"};
    char p3[] = "+78888888888";
    char e3[] = "andreysankov2004@gmail.com";
    SocialNetwork sns3[2];
    sns3[0] = (SocialNetwork){"Whatsapp", "+78888888888"};
    add(fn3, "work", w3, "phone", p3, "email", e3, "socials", 1, sns3[0]);

    Fullname fn4 = {"Петров", "Иван", "Иванович"};
    Work w4 = {"Элтекс", "Программист"};
    char p4[] = "+78888888888";
    char e4[] = "andreysankov2004@gmail.com";
    SocialNetwork sns4[2];
    sns4[0] = (SocialNetwork){"Whatsapp", "+78888888888"};
    add(fn4, "work", w4, "phone", p4, "email", e4, "socials", 1, sns4[0]);

    Fullname fn5 = {"Кузьмин", "Иван", "Иванович"};
    Work w5 = {"Элтекс", "Программист"};
    char p5[] = "+78888888888";
    char e5[] = "andreysankov2004@gmail.com";
    SocialNetwork sns5[2];
    sns5[0] = (SocialNetwork){"Whatsapp", "+78888888888"};
    add(fn5, "work", w5, "phone", p5, "email", e5, "socials", 1, sns5[0]);
    inorderTraversal(tree);
    balanceTree(tree);
    printf("После балансировки:\n");
    inorderTraversal(tree);
}
#endif
