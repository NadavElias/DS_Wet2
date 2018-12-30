#include <iostream>
#include <assert.h>
#include "RTree.h"
#include "UFind.h"

void RTreeTests(){
    UFind* check = new UFind(10);
    Pixel* temp;
    temp = check->Find(4);
    assert(temp->GetSize() == 1);
    assert(temp->GetFather() == NULL);

    check->Merge(3, 5);
    assert(check->Find(3) == check->Find(5));
    assert(check->Find(3) != check->Find(4));
    check->Merge(6, 7);
    assert(check->Find(6) == check->Find(7));
    assert(check->Find(6) != check->Find(5));
    check->Merge(6, 3);
    assert(check->Find(5) == check->Find(7));
    assert(check->Find(6) != check->Find(8));
}

int main() {
    std::cout << "Begin Tests:" << std::endl;
    RTreeTests();
    std::cout << "End Tests" << std::endl;

    return 0;
}