#include "../unity/unity.h"
#include "../src/double_linked_list.h"
#include "../src/contacts.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern DoubleLinkedList *list;

void setUp(void)
{
    if (list != NULL)
    {
        clearList(list);
        free(list);
        list = NULL;
    }
    list = initList();
    if (list == NULL)
    {
        TEST_FAIL();
    }
}
void tearDown(void)
{
    if (list != NULL)
    {
        clearList(list);
        free(list);
        list = NULL;
    }
}

void test_add_simple(void)
{
    Fullname fn = {"Саньков", "Андрей", "Иванович"};
    Work w = {"НГТУ", "Студент"};

    Contact contact;
    contact.fullname = fn;
    contact.work = w;
    strncpy(contact.phone, "+79133896816", sizeof(contact.phone));
    strncpy(contact.email, "andreysankov2004@gmail.com", sizeof(contact.email));
    contact.socialCnt = 0;

    addNode(list, contact);

    TEST_ASSERT_NOT_NULL(list->head);
    TEST_ASSERT_EQUAL_STRING("Саньков", list->head->contact.fullname.surname);
}

void test_delete_simple(void)
{
    Fullname fn = {"Саньков", "Андрей", "Иванович"};
    Work w = {"НГТУ", "Студент"};

    Contact contact;
    contact.fullname = fn;
    contact.work = w;
    strncpy(contact.phone, "+79133896816", sizeof(contact.phone));
    strncpy(contact.email, "andreysankov2004@gmail.com", sizeof(contact.email));
    contact.socialCnt = 0;

    addNode(list, contact);
    TEST_ASSERT_NOT_NULL(list->head);

    deleteNode(list, contact);
    TEST_ASSERT_NULL(list->head);
}

void test_edit_simple(void)
{
    Fullname old_fn = {"Саньков", "Андрей", "Иванович"};
    Fullname new_fn = {"Иванов", "Иван", "Иванович"};

    Work w = {"НГТУ", "Студент"};

    Contact old_contact;
    old_contact.fullname = old_fn;
    old_contact.work = w;
    strncpy(old_contact.phone, "+79133896816", sizeof(old_contact.phone));
    strncpy(old_contact.email, "andreysankov2004@gmail.com", sizeof(old_contact.email));
    old_contact.socialCnt = 0;

    Contact new_contact;
    new_contact.fullname = new_fn;
    new_contact.work = w;
    strncpy(new_contact.phone, "+77777777777", sizeof(new_contact.phone));
    strncpy(new_contact.email, "ivanov@gmail.com", sizeof(new_contact.email));
    new_contact.socialCnt = 0;

    addNode(list, old_contact);
    editNode(list, old_contact, new_contact);

    TEST_ASSERT_NOT_NULL(list->head);
    TEST_ASSERT_EQUAL_STRING("Иванов", list->head->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("+77777777777", list->head->contact.phone);
}

void test_multiple_contacts(void)
{
    Contact contacts[4];
    Fullname fn1 = {"Иванов", "Иван", "Иванович"};
    Work w1 = {"Элтекс", "Программист"};
    contacts[0].fullname = fn1;
    contacts[0].work = w1;
    strncpy(contacts[0].phone, "+78888888888", sizeof(contacts[0].phone));
    strncpy(contacts[0].email, "ivan@gmail.com", sizeof(contacts[0].email));
    contacts[0].socialCnt = 0;

    Fullname fn2 = {"Александров", "Александр", "Александрович"};
    Work w2 = {"Убер", "Таксист"};
    contacts[1].fullname = fn2;
    contacts[1].work = w2;
    strncpy(contacts[1].phone, "+79999999999", sizeof(contacts[1].phone));
    strncpy(contacts[1].email, "alesan4@gmail.com", sizeof(contacts[1].email));
    contacts[1].socialCnt = 0;

    Fullname fn3 = {"Саньков", "Андрей", "Иванович"};
    Work w3 = {"НГТУ", "Студент"};
    contacts[2].fullname = fn3;
    contacts[2].work = w3;
    strncpy(contacts[2].phone, "+79133896816", sizeof(contacts[2].phone));
    strncpy(contacts[2].email, "andreysankov2004@gmail.com", sizeof(contacts[2].email));
    contacts[2].socialCnt = 0;

    Fullname fn4 = {"Борисов", "Борис", "Борисович"};
    Work w4 = {"Школа", "Директор"};
    contacts[3].fullname = fn4;
    contacts[3].work = w4;
    strncpy(contacts[3].phone, "+75555555555", sizeof(contacts[3].phone));
    strncpy(contacts[3].email, "boris@mail.ru", sizeof(contacts[3].email));
    contacts[3].socialCnt = 0;

    for (int i = 0; i < 4; i++)
    {
        addNode(list, contacts[i]);
    }

    int count = 0;
    Node *current = list->head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    TEST_ASSERT_EQUAL_INT(4, count);
    TEST_ASSERT_NOT_NULL(list->head);
    TEST_ASSERT_EQUAL_STRING("Александров", list->head->contact.fullname.surname);
    TEST_ASSERT_NOT_NULL(list->head->next);
    TEST_ASSERT_EQUAL_STRING("Борисов", list->head->next->contact.fullname.surname);
    TEST_ASSERT_NOT_NULL(list->head->next->next);
    TEST_ASSERT_EQUAL_STRING("Иванов", list->head->next->next->contact.fullname.surname);
    TEST_ASSERT_NOT_NULL(list->head->next->next->next);
    TEST_ASSERT_EQUAL_STRING("Саньков", list->head->next->next->next->contact.fullname.surname);
    TEST_ASSERT_NOT_NULL(list->tail);
    TEST_ASSERT_EQUAL_STRING("Саньков", list->tail->contact.fullname.surname);

    deleteNode(list, contacts[3]);
    count = 0;
    current = list->head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    TEST_ASSERT_EQUAL_INT(3, count);
    TEST_ASSERT_EQUAL_STRING("Александров", list->head->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("Иванов", list->head->next->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("Саньков", list->head->next->next->contact.fullname.surname);
    TEST_ASSERT_NULL(list->head->prev);
    TEST_ASSERT_EQUAL_PTR(list->head, list->head->next->prev);
    TEST_ASSERT_EQUAL_PTR(list->head->next, list->head->next->next->prev);

    deleteNode(list, contacts[1]);
    count = 0;
    current = list->head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    TEST_ASSERT_EQUAL_INT(2, count);
    TEST_ASSERT_EQUAL_STRING("Иванов", list->head->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("Саньков", list->head->next->contact.fullname.surname);
    TEST_ASSERT_NULL(list->head->prev);

    deleteNode(list, contacts[2]);
    count = 0;
    current = list->head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    TEST_ASSERT_EQUAL_INT(1, count);
    TEST_ASSERT_EQUAL_STRING("Иванов", list->head->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("Иванов", list->tail->contact.fullname.surname);
    TEST_ASSERT_EQUAL_PTR(list->head, list->tail);
    TEST_ASSERT_NULL(list->head->next);
    TEST_ASSERT_NULL(list->head->prev);

    deleteNode(list, contacts[0]);

    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_add_simple);
    RUN_TEST(test_delete_simple);
    RUN_TEST(test_edit_simple);
    RUN_TEST(test_multiple_contacts);
    return UNITY_END();
}
