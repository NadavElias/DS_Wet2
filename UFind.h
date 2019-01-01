//
// Created by nadav.elias on 30-Dec-18.
//

#ifndef DS_WET2_UFIND_H
#define DS_WET2_UFIND_H

#include "Pixel.h"

class UFind {
    Pixel** pixels;
    int numOfPixels;
public:

    UFind(int numOfPixels):  pixels(new Pixel*[numOfPixels]), numOfPixels(numOfPixels){
        for (int i = 0; i < numOfPixels; ++i) {
            pixels[i] = new Pixel(i);
        }
    };

    Pixel* Find(int pixelNum){
        Pixel* curr = pixels[pixelNum];
        while(curr->GetFather() != NULL){
            curr = curr->GetFather();
        }
        Pixel* headOfGroup = curr;
        curr = pixels[pixelNum];
        while(curr->GetFather() != NULL){
            Pixel* temp = curr->GetFather();
            curr->SetFather(headOfGroup);
            curr = temp;
        }
        return headOfGroup;
    }



    StatusType Merge(int pixel1, int pixel2){
        if (Find(pixel1) == Find(pixel2))
            return FAILURE;
        Pixel::Combine(Find(pixel1), Find(pixel2));
        return SUCCESS;
    }

    ~UFind(){
        for (int i = 0; i < numOfPixels; ++i) {
            delete pixels[i];
        }
        delete[] pixels;
    }

};
#endif //DS_WET2_UFIND_H
