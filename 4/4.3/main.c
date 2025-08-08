#include "tests.h"
#include "tree.h"

Tree *tree;

int main()
{
    tree = initTree();
    test();
    clearTree(tree);
    return 0;
}
