#include <iostream>
#include <assert.h>
#include "RTree.h"

void RTreeTests(){
    RTree<int, int>* check = new RTree<int, int>;
    TNode<int, int>* temp = NULL;
    assert(check != NULL);


    for (int i = 0; i < 100; ++i) {
        assert(check->Add(i, 0, &temp) == SUCCESS);
        assert(check->GetMax() == i);
    }



}

int main() {
    std::cout << "Begin Tests:" << std::endl;
    RTreeTests();
    std::cout << "End Tests" << std::endl;

    return 0;
}