#include "tests.h"
#include "contacts.h"
#include <stdio.h>

extern Contact contacts[ARR_SIZE];

#ifdef TEST_1
void test()
{
    contactsInit();
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
    contactsInit();
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
    contactsInit();
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
    contactsInit();
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
    delete(fn);
    printf("%s", contacts[0].fullname.surname);
}
#endif
