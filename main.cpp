#include <iostream>
#include <assert.h>
#include "RTree.h"
#include "UFind.h"

void RTreeTests(){
    RTree<int, int>* check1 = new RTree<int, int>();
    RTree<int, int>* check2 = new RTree<int, int>();
    TNode<int, int>* temp = NULL;
    for (int i = 0; i < 100; ++i) {
        check1->Add(i, i, &temp);
    }
    for (int i = 50; i < 170; ++i) {
        check2->Add(i, i, &temp);
    }

    assert(check1->IsBalanced());
    assert(check1->IsSearch());

    assert(check2->IsBalanced());
    assert(check2->IsSearch());

    RTree<int, int>* M = new RTree<int, int>();

    M = RTree<int, int>::MergeTrees(check1, check2);

    assert(M->IsBalanced());
    assert(M->IsSearch());
    delete check1;
    delete check2;
    delete M;
}

int main() {
    std::cout << "Begin Tests:" << std::endl;
    RTreeTests();
    std::cout << "End Tests" << std::endl;

    return 0;
}