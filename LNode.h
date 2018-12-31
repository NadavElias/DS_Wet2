//
// Created by sagil on 31/12/2018.
//

#ifndef DS_WET2_LNODE_H
#define DS_WET2_LNODE_H

#include <iostream>

template <class K, class V>
class ListNode {
    K key;
    V value;

    ListNode* prev;
    ListNode* next;

public:
    ListNode (K key, V value) :
            key(key), value(value), prev(NULL), next(NULL){}
    ListNode (K key, V value, ListNode<K, V>* prev, ListNode<K, V>* next) :
            key(key), value(value), prev(prev), next(next){}
    K GetKey (){
        return key;
    }
    V GetValue (){
        return value;
    }
    ListNode<K, V>* GetNext (){
        return next;
    }
    ListNode<K, V>* GetPrev (){
        return prev;
    }
    void SetNext(ListNode<K, V>* node){
        next = node;
    }
    void SetPrev(ListNode<K, V>* node){
        prev = node;
    }
    void SetKey(K new_key){
        key = new_key;
    }
    void SetValue(V new_value){
        value = new_value;
    }
};



#endif //DS_WET2_LNODE_H
