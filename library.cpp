//
// Created by nadav.elias on 01-Jan-19.
//

#include "library.h"
#include "StaticEye.h"

void * Init(int pixels){
    try {
        if (pixels <= 0)
            return NULL;
        return new StaticEye(pixels);
    }
    catch (std::bad_alloc &e){
        return NULL;
    }
}

StatusType AddImage(void *DS, int imageID){
    try {
        if (DS == NULL)
            return INVALID_INPUT;
        return ((StaticEye *) DS)->AddImage(imageID);
    }
    catch (std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
}

StatusType DeleteImage(void *DS, int imageID){
    try {
        if (DS == NULL)
            return INVALID_INPUT;
        return ((StaticEye*)DS)->DeleteImage(imageID);
    }
    catch (std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
}

StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score){
    try {
        if (DS == NULL)
            return INVALID_INPUT;
        return ((StaticEye*)DS)->SetLabelScore(imageID, pixel, label, score);
    }
    catch (std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
}

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label){
    try {
        if (DS == NULL)
            return INVALID_INPUT;
        return ((StaticEye*)DS)->ResetLableScore(imageID, pixel, label);
    }
    catch (std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
}

StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label){
    try {
        if (DS == NULL)
            return INVALID_INPUT;
        return ((StaticEye*)DS)->GetHighestScoredLabel(imageID, pixel, label);
    }
    catch (std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
}

StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2){
    try {
        if (DS == NULL)
            return INVALID_INPUT;
        return ((StaticEye*)DS)->MergeSuperPixels(imageID, pixel1, pixel2);
    }
    catch (std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
}

void Quit(void** DS){
    if (DS == NULL || *DS == NULL)
        return;
    delete *((StaticEye**)DS);
    *DS = NULL;
}
