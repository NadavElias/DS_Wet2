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

    UFind(int numOfItems):  pixels(new Pixel*[numOfPixels]), numOfPixels(numOfPixels){
        for (int i = 0; i < numOfPixels; ++i) {
            pixels[i] = new Pixel();
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
            curr->SetFather(headOfGroup);
        }
        return headOfGroup;
    }



    void Merge(int pixel1, int pixel2){
        Pixel::Combine(Find(pixel1), Find(pixel2));
    }

    ~UFind(){
        for (int i = 0; i < numOfPixels; ++i) {
            delete pixels[i];
        }
    }

};
#endif //DS_WET2_UFIND_H
