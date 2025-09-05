#include "tests.h"
#include "tree.h"

extern Tree *tree;

int main()
{
    tree = initTree();
    test();
    clearTree(tree);
    return 0;
}
