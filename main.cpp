#include <iostream>
#include <assert.h>
#include "RTree.h"

void RTreeTests(){
    MyTree<int, int>* check = new MyTree<int, int>;
    TNode<int, int>* temp = NULL;
    assert(check != NULL);


    for (int i = 0; i < 100; ++i) {
        assert(check->Add(200-i, i, &temp) == SUCCESS);
        assert(check->GetMax() == 200-i);
    }

    assert(check->SetValue(101, 0) == SUCCESS);




}

int main() {
    std::cout << "Begin Tests:" << std::endl;
    RTreeTests();
    std::cout << "End Tests" << std::endl;

    return 0;
}