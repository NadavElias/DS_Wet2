//
// Created by nadav.elias on 30-Dec-18.
//

#ifndef DS_WET2_HTABLE_H
#define DS_WET2_HTABLE_H

#include "UFind.h"
#include "List.h"

class HTable {
    int tableSize, numOfImages, numOfPixels;
    List<int, UFind*>* table;

public:
    HTable(int numOfPixels) : tableSize(8), numOfImages(0), numOfPixels(numOfPixels), table(new (List<int, (UFind*)>)[tableSize]){}
};

#endif //DS_WET2_HTABLE_H
