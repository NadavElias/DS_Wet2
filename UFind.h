//
// Created by nadav.elias on 30-Dec-18.
//

#ifndef DS_WET2_UFIND_H
#define DS_WET2_UFIND_H

template<class T>
class UFind {
    T* items;
    int numOfItems;
public:

    UFind(int numOfItems): numOfItems(numOfItems), items(new T[numOfItems]){};

};
#endif //DS_WET2_UFIND_H
