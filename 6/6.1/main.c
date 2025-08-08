#include "double_linked_list.h"
#include "tests.h"

DoubleLinkedList *list;

int main()
{
    list = initList();
    test();
    clearList(list);
    return 0;
}
