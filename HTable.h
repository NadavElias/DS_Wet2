//
// Created by nadav.elias on 30-Dec-18.
//

#ifndef DS_WET2_HTABLE_H
#define DS_WET2_HTABLE_H

#define INITIAL_SIZE 2

#include "UFind.h"
#include "List.h"

class HTable {
    int tableSize, numOfImages, numOfPixels;
    List<int, UFind*>* table;

    int hash(int imageID){
        return imageID % tableSize;
    }

    void checkIsBig(){
        if(numOfImages < tableSize){
            return;
        }
        tableSize *= 2;
        List<int, UFind*>* temp = new List<int, UFind*>[tableSize];
        ListNode<int, UFind*>* trash;
        for (int i = 0; i < tableSize/2; ++i) {
            ListNode<int, UFind*>* it = table[i].getFirst();
            while (it != NULL){
                temp[hash(it->GetKey())].Add(it->GetKey(), it->GetValue(), &trash);
                delete it->GetValue();
            }
        }
        delete[] table;
        table = temp;
    }

    void checkIsSmall(){
        if(numOfImages > tableSize/4 || tableSize <= INITIAL_SIZE){
            return;
        }
        tableSize /= 2;
        List<int, UFind*>* temp = new List<int, UFind*>[tableSize];
        ListNode<int, UFind*>* trash;
        for (int i = 0; i < tableSize*2; ++i) {
            ListNode<int, UFind*>* it = table[i].getFirst();
            while (it != NULL){
                temp[hash(it->GetKey())].Add(it->GetKey(), it->GetValue(), &trash);
                delete it->GetValue();
            }
        }
        delete[] table;
        table = temp;
    }

public:
    HTable(int numOfPixels) : tableSize(INITIAL_SIZE), numOfImages(0), numOfPixels(numOfPixels), table(new List<int, UFind*>[tableSize]){}
    ~HTable(){
        for (int i = 0; i < tableSize ; ++i) {
            ListNode<int, UFind*>* it = table[i].getFirst();
            while (it != NULL){
                delete it->GetValue();
                it = it->GetNext();
            }
        }
        delete[] table;
    }

    UFind* Find (int imageID){
        UFind* res = NULL;
        if (table[hash(imageID)].Find(imageID, &res) == FAILURE){
            return NULL;
        }
        return res;
    }

    StatusType Add (int imageID){
        checkIsBig();
        UFind* res = NULL;

        if (Find(imageID) != NULL){
            return FAILURE;
        }
        ListNode<int, UFind*>* n = NULL;
        table[hash(imageID)].Add(imageID, new UFind(numOfPixels), &n);
        numOfImages++;
        return SUCCESS;
    }

    StatusType Remove (int imageID){
        if (Find(imageID) == NULL){
            return FAILURE;
        }
        delete Find(imageID);
        table[hash(imageID)].Delete(imageID);
        numOfImages--;
        checkIsSmall();
        return SUCCESS;
    }
};

#endif //DS_WET2_HTABLE_H
