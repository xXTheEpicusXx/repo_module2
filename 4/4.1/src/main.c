#include "double_linked_list.h"

extern DoubleLinkedList *list;

int main()
{
    list = initList();
    clearList(list);
    return 0;
}
