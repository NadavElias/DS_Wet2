//
// Created by nadav.elias on 01-Jan-19.
//

#ifndef DS_WET2_STATICEYE_H
#define DS_WET2_STATICEYE_H

#include "HTable.h"
#include "library.h"

class StaticEye {
    int numOfPixels;
    HTable images;

public:
    StaticEye(int numOfPixels);

    StatusType AddImage(int imageID);

    StatusType DeleteImage(int imageID);

    StatusType SetLabelScore(int imageID, int pixel, int label, int score);

    StatusType ResetLableScore(int imageID, int pixel, int label);

    StatusType GetHighestScoredLabel(int imageID, int pixel, int* label);

    StatusType MergeSuperPixels(int imageID, int pixel1, int pixel2);
};

#endif //DS_WET2_STATICEYE_H
