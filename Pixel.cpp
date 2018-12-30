//
// Created by nadav.elias on 30-Dec-18.
//

#include "Pixel.h"

int Pixel::GetSize(){
    return size;
}
Pixel* Pixel::GetFather(){
    return father;
}
void Pixel::SetFather(Pixel* p){
    father = p;
}
void Pixel::AddSize(int add){
    size+=add;
}
