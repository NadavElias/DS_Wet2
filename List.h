//
// Created by sagil on 31/12/2018.
//

#ifndef DS_WET2_LIST_H
#define DS_WET2_LIST_H

#include "LNode.h"
#include "library.h"
#include <assert.h>


template <class K, class V>
class List {
    ListNode<K, V>* first;
    int size;

public:
    List():
            first (NULL), size (0){}

    ~List(){
        ListNode<K, V>* curr = first;
        while (curr != NULL) {
            ListNode<K, V> *temp = curr->GetNext();
            delete curr;
            curr = temp;
        }
    }
    //add to front of list O(1). does not check if key is already in list!!!
    StatusType Add(const K& key, const V& value, ListNode<K, V>** node){
        ListNode<K, V>* new_node = new ListNode<K, V>(key, value, NULL, first);
        if(first != NULL){
            first->SetPrev(new_node);
        }
        first = new_node;
        *node = new_node;
        size++;
        return SUCCESS;
    }
/*
    //add as sorted list O(n)
    StatusType Add(K key, V value, ListNode<K, V>** node){
        ListNode<K, V>* before = NULL;
        for (ListNode<K, V>* curr = first; curr != NULL; before = curr, curr = curr->GetNext()){
            if (curr->GetKey() == key) {
                return FAILURE;
            }
            if (curr->GetKey() > key){
                ListNode<K, V>* new_node = new ListNode<K, V>(key, value, curr->GetPrev(), curr);
                ListNode<K, V>* prev = curr->GetPrev();
                if (prev != NULL){
                    prev->SetNext(new_node);
                } else{
                    first = new_node;
                }
                curr->SetPrev(new_node);
                *node = new_node;
                size++;
                return SUCCESS;
            }
        }
        ListNode<K, V>* new_node = new ListNode<K, V>(key, value, before, NULL);
        if (before != NULL) {
            before->SetNext(new_node);
        } else{
            first = new_node;
        }
        *node = new_node;
        size++;
        return SUCCESS;
    }
*/
    StatusType Find(const K& key, V* value){
        for (ListNode<K, V>* curr = first; curr != NULL; curr = curr->GetNext()){
            if (curr->GetKey() == key){
                *value = curr->GetValue(); // יש מצב שצריך להקצות דינמית. כי זה מועתק בתוך הפונקציה ונמחק כשיוצאים ממנה(?)
                return SUCCESS;
            }
        }
        return FAILURE;
    }
    StatusType Delete(const K& key){
        for (ListNode<K, V>* curr = first; curr != NULL; curr = curr->GetNext()){
            if (curr->GetKey() == key){
                DeleteByPointer(curr);
                return SUCCESS;
            }
        }
        return FAILURE;
    }

    StatusType DeleteByPointer(ListNode<K, V>* node){ // לבדוק האם מקבלים מצביע לנוד או את הנוד עצמו
        ListNode<K, V>* prev = node->GetPrev();
        ListNode<K, V>* next = node->GetNext();
        if (prev != NULL){
            prev->SetNext(next);
        } else{
            first = next;
        }
        if (next != NULL){
            next->SetPrev(prev);
        }
        delete node;
        size--;
        return SUCCESS;
    }

    StatusType Size(int *n){
        *n = size;
        return SUCCESS;
    }

    void CopyKeysToArray(K *array){
        ListNode<K, V>* curr = first;
        int i = 0;
        while (curr != NULL) {
            assert(i<size);
            array[i] = curr->GetKey();
            curr = curr->GetNext();
            i++;
        }
    }
};



#endif //DS_WET2_LIST_H
