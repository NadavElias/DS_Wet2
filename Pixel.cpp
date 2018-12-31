//
// Created by nadav.elias on 30-Dec-18.
//

#include "Pixel.h"

Pixel::Pixel() : labels(new RTree<int, int>()), size(1), father(NULL) {

}

void Pixel::Combine(Pixel* p1, Pixel* p2){
    if (p1 == p2)
        return;
    RTree<int, int>* labels = RTree<int, int>::MergeTrees(p1->labels, p2->labels);
    delete p1->labels;
    delete p2->labels;
    p1->labels = NULL;
    p2->labels = NULL;
    if (p1->size < p2->size){
        p1->father = p2;
        p2->size += p1->size;
        p2->labels = labels;
    } else{
        p2->father = p1;
        p1->size += p2->size;
        p1->labels = labels;
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
Pixel::~Pixel(){
    delete labels;
}
