//
// Created by nadav.elias on 30-Dec-18.
//

#ifndef DS_WET2_PIXEL_H
#define DS_WET2_PIXEL_H

#include "RTree.h"


class Pixel {
    RTree<int, int>* labels;
    int size;
    Pixel* father;

public:
    Pixel();
    ~Pixel();
    int GetSize();
    Pixel* GetFather();
    void AddSize(int add);

    void SetFather(Pixel *p);

    // gets two pixels that are *head of groups* and combines the groups
    static void Combine(Pixel* p1, Pixel* p2);
};


#endif //DS_WET2_PIXEL_H
