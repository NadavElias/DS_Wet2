//
// Created by nadav.elias on 30-Dec-18.
//

#ifndef DS_WET2_TNODE_H
#define DS_WET2_TNODE_H

#include<stdlib.h>
#include <assert.h>

template <class K, class V>
class TNode {
    K key;
    V value;
    K maxKey;
    V maxValue;

    TNode* father;
    TNode* leftSon;
    TNode* rightSon;

    int height;

public:
    TNode (const K& key,const V& value) :
            key(key), value(value), maxKey(key), maxValue(value), father(NULL), leftSon(NULL), rightSon(NULL), height(0){}

    TNode (const K& key, const V& value, TNode<K, V>* father, TNode<K, V>* leftSon, TNode<K, V>* rightSon) :
            key(key), value(value), maxKey(key), maxValue(value), father(father), leftSon(leftSon), rightSon(rightSon){
        UpdateHeight();
    }

    K GetKey (){
        return key;
    }
    V GetValue (){
        return value;
    }
    V GetMaxValue (){
        return maxValue;
    }
    V GetMaxKey (){
        return maxKey;
    }
    V* GetValueByPointer (){
        return &value;
    }
    int GetHeight (){
        return height;
    }
    int GetLeftSonHeight (){
        return leftSon == NULL ? -1 : leftSon->height;
    }
    int GetRightSonHeight (){
        return rightSon == NULL ? -1 : rightSon->height;
    }
    int GetBalanceFactor(){
        return (GetLeftSonHeight()) - (GetRightSonHeight());
    }
    TNode<K, V>* GetLeftSon (){
        return leftSon;
    }
    TNode<K, V>* GetRightSon (){
        return rightSon;
    }
    TNode<K, V>* GetFather (){
        return father;
    }
    void SetLeftSon(TNode<K, V>* node){
        leftSon = node;
    }
    void SetRightSon(TNode<K, V>* node){
        rightSon = node;
    }
    void SetFather(TNode<K, V>* node){
        father = node;
    }
    void SetKey(K new_key){
        key = new_key;
    }
    void SetValue(V new_value){
        value = new_value;
    }
    void SetMaxValue(V new_value){
        maxValue = new_value;
    }
    void SetMaxKey(K new_value){
        maxKey = new_value;
    }
    //assumes the heights of left and right son are updated. (use this function for upwards recursion)
    void UpdateHeight(){
        int lH = -1, rH = -1;
        if(leftSon != NULL){
            lH = leftSon->height;
        }
        if(rightSon != NULL){
            rH = rightSon->height;
        }
        height = lH >= rH ? lH + 1 : rH + 1;
    }

    void UpdateMax(){
        maxValue = value;
        maxKey = key;
        if(leftSon != NULL) {
            if (leftSon->maxValue > value) {
                maxValue = leftSon->maxValue;
                maxKey = leftSon->maxKey;
            }
        }
        if(rightSon != NULL) {
            if (rightSon->maxValue >= value) {
                maxValue = rightSon->maxValue;
                maxKey = rightSon->maxKey;
            }
        }
    }


    bool IsBalanced (){
        if (leftSon != NULL){
            leftSon->IsBalanced();
        }
        if (rightSon != NULL) {
            rightSon->IsBalanced();
        }
        assert(GetLeftSonHeight() - GetRightSonHeight() >= -1);
        assert(GetLeftSonHeight() - GetRightSonHeight() <= 1);
        return true;
    }

    bool IsSearch (){
        if (leftSon != NULL){
            if (leftSon->GetKey() > key || leftSon->IsSearch() == false)
                return false;
        }
        if (rightSon != NULL){
            if (rightSon->GetKey() < key || rightSon->IsSearch() == false)
                return false;
        }
        return true;
    }
};



#endif //DS_WET2_TNODE_H
