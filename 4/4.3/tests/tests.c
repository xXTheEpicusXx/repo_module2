#include "../unity/unity.h"
#include "../src/tree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern Tree *tree;

void setUp(void)
{
    if (tree != NULL)
    {
        clearTree(tree);
        free(tree);
        tree = NULL;
    }
    tree = initTree();
    if (tree == NULL)
    {
        TEST_FAIL();
    }
}
void tearDown(void)
{
    if (tree != NULL)
    {
        clearTree(tree);
        free(tree);
        tree = NULL;
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

    addNode(tree, contact);

    TEST_ASSERT_NOT_NULL(tree->root);
    TEST_ASSERT_EQUAL_STRING("Саньков", tree->root->contact.fullname.surname);
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

    addNode(tree, contact);
    TEST_ASSERT_NOT_NULL(tree->root);

    deleteNode(tree, contact);
    TEST_ASSERT_NULL(tree->root);
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

    addNode(tree, old_contact);
    editNode(tree, old_contact, new_contact);

    TEST_ASSERT_NOT_NULL(tree->root);
    TEST_ASSERT_EQUAL_STRING("Иванов", tree->root->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("+77777777777", tree->root->contact.phone);
}

void test_multiple_contacts_operations(void)
{
    // Первый контакт
    Fullname fn1 = {"Саньков", "Андрей", "Иванович"};
    Work w1 = {"НГТУ", "Студент"};
    Contact contact1;
    contact1.fullname = fn1;
    contact1.work = w1;
    strncpy(contact1.phone, "+79133896816", sizeof(contact1.phone));
    strncpy(contact1.email, "andreysankov2004@gmail.com", sizeof(contact1.email));
    contact1.socialCnt = 0;

    // Второй контакт должен быть правее в дереве
    Fullname fn2 = {"Иванов", "Иванов", "Иванов"};
    Work w2 = {"Элтекс", "Разработчик"};
    Contact contact2;
    contact2.fullname = fn2;
    contact2.work = w2;
    strncpy(contact2.phone, "+79999999999", sizeof(contact2.phone));
    strncpy(contact2.email, "ivan@microsoft.com", sizeof(contact2.email));
    contact2.socialCnt = 0;

    // Третий контакт должен быть левее в дереве
    Fullname fn3 = {"Фетров", "Петр", "Петрович"};
    Work w3 = {"Google", "Менеджер"};
    Contact contact3;
    contact3.fullname = fn3;
    contact3.work = w3;
    strncpy(contact3.phone, "+75554443322", sizeof(contact3.phone));
    strncpy(contact3.email, "petr@google.com", sizeof(contact3.email));
    contact3.socialCnt = 0;

    // Добавляем три контакта
    addNode(tree, contact1);
    addNode(tree, contact2);
    addNode(tree, contact3);

    // Проверяем, что все контакты добавлены
    TEST_ASSERT_NOT_NULL(tree->root);
    TEST_ASSERT_NOT_NULL(tree->root->left);
    TEST_ASSERT_NOT_NULL(tree->root->right);

    // Проверяем порядок в дереве по фамилиям
    TEST_ASSERT_EQUAL_STRING("Саньков", tree->root->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("Иванов", tree->root->left->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("Фетров", tree->root->right->contact.fullname.surname);

    // Проверяем поиск контактов
    Node *found1 = copyNode(tree, contact1);
    Node *found2 = copyNode(tree, contact2);
    Node *found3 = copyNode(tree, contact3);

    TEST_ASSERT_NOT_NULL(found1);
    TEST_ASSERT_NOT_NULL(found2);
    TEST_ASSERT_NOT_NULL(found3);

    TEST_ASSERT_EQUAL_STRING("Саньков", found1->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("Иванов", found2->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("Фетров", found3->contact.fullname.surname);

    // Удаляем корень
    deleteNode(tree, contact1);

    // Проверяем, что корень изменился
    TEST_ASSERT_NOT_NULL(tree->root);
    TEST_ASSERT_NULL(tree->root->right); // После удаления корня правый потомок должен стать новым корнем
    TEST_ASSERT_NOT_NULL(tree->root->left);

    TEST_ASSERT_EQUAL_STRING("Фетров", tree->root->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("Иванов", tree->root->left->contact.fullname.surname);

    deleteNode(tree, contact2);
    deleteNode(tree, contact3);

    TEST_ASSERT_NULL(tree->root);
}

void test_tree_balancing_with_visualization(void)
{
    // Создаем контакты в порядке для образования вырожденного дерева
    Contact contacts[7];

    Fullname fns[7] = {
        {"А", "Андрей", "А"},
        {"Б", "Борис", "Б"},
        {"В", "Виктор", "В"},
        {"Г", "Григорий", "Г"},
        {"Д", "Дмитрий", "Д"},
        {"Е", "Евгений", "Е"},
        {"Ж", "Жора", "Ж"}};

    Work w = {"Компания", "Должность"};

    for (int i = 0; i < 7; i++)
    {
        contacts[i].fullname = fns[i];
        contacts[i].work = w;
        snprintf(contacts[i].phone, sizeof(contacts[i].phone), "+7913%d", 1000000 + i);
        snprintf(contacts[i].email, sizeof(contacts[i].email), "user%d@mail.com", i);
        contacts[i].socialCnt = 0;
        addNode(tree, contacts[i]);
    }

    printf("\nДерево ДО балансировки:\n");
    inorderTraversal(tree);
    // В вырожденном дереве должен быть только правый потомок у каждого узла
    TEST_ASSERT_NOT_NULL(tree->root);
    TEST_ASSERT_NULL(tree->root->left);      // Левый потомок корня должен быть NULL
    TEST_ASSERT_NOT_NULL(tree->root->right); // Правый потомок существует

    // Выполняем балансировку
    balanceTree(tree);

    printf("\nДерево ПОСЛЕ балансировки:\n");
    inorderTraversal(tree);

    TEST_ASSERT_NOT_NULL(tree->root);

    // Проверяем, что корень = средний элемент(Г)
    TEST_ASSERT_EQUAL_STRING("Г", tree->root->contact.fullname.surname);

    // Проверяем наличие обоих потомков у корня
    TEST_ASSERT_NOT_NULL(tree->root->left);
    TEST_ASSERT_NOT_NULL(tree->root->right);

    // Проверяем структуру сбалансированного дерева
    TEST_ASSERT_EQUAL_STRING("Б", tree->root->left->contact.fullname.surname);
    TEST_ASSERT_EQUAL_STRING("Е", tree->root->right->contact.fullname.surname);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_add_simple);
    RUN_TEST(test_delete_simple);
    RUN_TEST(test_edit_simple);
    RUN_TEST(test_multiple_contacts_operations);
    RUN_TEST(test_tree_balancing_with_visualization);
    return UNITY_END();
}
