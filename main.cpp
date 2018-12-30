#include <iostream>
#include <assert.h>
#include "RTree.h"

void RTreeTests(){
    RTree<int, int>* tree1 = new RTree<int, int>;
    RTree<int, int>* tree2 = new RTree<int, int>;
    TNode<int, int>* temp = NULL;
    assert(tree1 != NULL);
    assert(tree2 != NULL);

    assert(tree1->Add(3, 3, &temp) == SUCCESS);
    assert(tree1->Add(1, 1, &temp) == SUCCESS);
    assert(tree1->Add(6, 5, &temp) == SUCCESS);
    assert(tree2->Add(4, 4, &temp) == SUCCESS);
    assert(tree2->Add(2, 2, &temp) == SUCCESS);
    assert(tree2->Add(7, 7, &temp) == SUCCESS);
    assert(tree2->Add(6, 6, &temp) == SUCCESS);

    RTree<int, int>* M = RTree<int, int>::MergeTrees(tree1, tree2);


}

int main() {
    std::cout << "Begin Tests:" << std::endl;
    RTreeTests();
    std::cout << "End Tests" << std::endl;

    return 0;
}