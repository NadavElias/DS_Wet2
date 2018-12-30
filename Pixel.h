//
// Created by nadav.elias on 30-Dec-18.
//

#ifndef DS_WET2_PIXEL_H
#define DS_WET2_PIXEL_H

#include "RTree.h"


class Pixel {
    RTree<int, int> labels;
    int size;
    Pixel* father;

public:
    int GetSize();
    Pixel* GetFather();
    void AddSize(int add);

    void SetFather(Pixel *p);
};


#endif //DS_WET2_PIXEL_H
