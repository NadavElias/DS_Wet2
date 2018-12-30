//
// Created by nadav.elias on 30-Dec-18.
//

#include "Pixel.h"

static void Pixel::Combine(Pixel& p1, Pixel& p2){
    RTree<int, int>* labels = MergeTrees(p1.labels, p2.labels);
    delete p1.labels;
    delete p2.labels;
    if (p1.size < p2.size){
        p1.father = &p2;
        p2.size += p1.size;
        p2.labels = labels;
    } else{
        p2.father = &p1;
        p1.size += p2.size;
        p1.labels = labels;
    }
}

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
