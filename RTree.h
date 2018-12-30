//
// Created by nadav.elias on 30-Dec-18.
//

#ifndef DS_WET2_RTREE_H
#define DS_WET2_RTREE_H
//
// Created by nadav.elias on 26-Nov-18.
//

#include<stdlib.h>
#include <assert.h>
#include "TNode.h"
#include "library.h"


template <class K, class V>
class RTree {
    TNode<K, V>* root;
    int size;

    static void treeToArrays(TNode<K, V>* curr, K* keys, V* values, int* index){//assumes the length of the array is correct
        if(curr == NULL){
            return;
        }
        treeToArrays(curr->GetLeftSon(), keys, values, index);
        keys[*index] = curr->GetKey();
        values[*index] = curr->GetValue();
        (*index)++;
        treeToArrays(curr->GetLeftSon(), keys, values, index);
    }
    static int MergeArrays(K* keys1, V* values1, K* keys2, V* values2, int length1, int length2, K** mergedKeys, V** mergedValues){//check if works!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int ptr1 = 0, ptr2 = 0, totalPtr = 0;
        while(ptr1 < length1 && ptr2 < length2){
            if(keys1[ptr1] < keys2[ptr2]){
                (*mergedKeys)[totalPtr] = keys1[ptr1];
                (*mergedValues)[totalPtr] = values1[ptr1];
                ptr1++;
                totalPtr++;
            }
            else if(keys1[ptr1] > keys2[ptr2]){
                (*mergedKeys)[totalPtr] = keys2[ptr2];
                (*mergedValues)[totalPtr] = values2[ptr2];
                ptr2++;
                totalPtr++;
            }
            else{
                (*mergedKeys)[totalPtr] = keys2[ptr2];
                (*mergedValues)[totalPtr] = values2[ptr2] + values1[ptr1];
                ptr2++;
                ptr1++;
                totalPtr++;
            }
        }
        while(ptr1 < length1){
            (*mergedKeys)[totalPtr] = keys1[ptr1];
            (*mergedValues)[totalPtr] = values1[ptr1];
            ptr1++;
            totalPtr++;
        }
        while(ptr2 < length2){
            (*mergedKeys)[totalPtr] = keys2[ptr2];
            (*mergedValues)[totalPtr] = values2[ptr2];
            ptr2++;
            totalPtr++;
        }
        return totalPtr;
    }
    static RTree<K, V>* MergeTrees(RTree<K, V>* tree1, RTree<K, V>* tree2){
        int length1;
        tree1->Size(&length1);
        int length2;
        tree2->Size(&length2);
        K* keys1 = new K[length1];
        V* values1 = new V[length1];
        K* keys2 = new K[length2];
        V* values2 = new V[length2];

        int index = 0;
        treeToArrays(tree1->root, keys1, values1, &index);
        index = 0;
        treeToArrays(tree2->root, keys2, values2, &index);

        K* keys = new K[length1+length2];
        V* values = new V[length1+length2];
        int length = MergeArrays(keys1, values1, keys2, values2, length1, length2, &keys, &values);

        RTree<K, V>* mergedTree = new RTree(arraysToTree(keys, values, length), length);

        delete[] keys1;
        delete[] keys2;
        delete[] values1;
        delete[] values2;
        delete[] keys;
        delete[] values;

        return mergedTree;
    }
    StatusType FindAux(TNode<K, V>* node, K key, V* value) {
        if (node == NULL) {
            return FAILURE;
        }
        if(node->GetKey() == key){
            *value = node->GetValue();// יש מצב שצריך להקצות דינמית. כי זה מועתק בתוך הפונקציה ונמחק כשיוצאים ממנה(?)
            return SUCCESS;
        }
        if(node->GetKey() > key){
            return FindAux(node->GetLeftSon(), key, value);
        }

        return FindAux(node->GetRightSon(), key, value);
    }
    StatusType SetValueAux(TNode<K, V>* node, K key, V value) {
        if (node == NULL) {
            return FAILURE;
        }
        if(node->GetKey() == key){
            node->SetValue(value);
            node->UpdateMax();
            return SUCCESS;
        }
        if(node->GetKey() > key){
            StatusType temp = SetValueAux(node->GetLeftSon(), key, value);
            node->UpdateMax();
            return temp;
        }

        StatusType temp = SetValueAux(node->GetRightSon(), key, value);
        node->UpdateMax();
        return temp;
    }
    StatusType AddAux(TNode<K, V>* node, K key,const V& value, TNode<K, V>** new_node) {
        if (node == NULL){
            *new_node = new TNode<K, V>(key, value, node, NULL, NULL);
            root = *new_node;
            size++;
            return SUCCESS;
        }
        if (node->GetKey() == key) {
            return FAILURE;
        }
        if (node->GetKey() > key) {
            if (node->GetLeftSon() == NULL) {
                *new_node = new TNode<K, V>(key, value, node, NULL, NULL);
                node->SetLeftSon(*new_node);
                size++;
                DoRoll(node, true);
                return SUCCESS;
            }
            return AddAux(node->GetLeftSon(), key, value, new_node);
        }

        if (node->GetRightSon() == NULL) {
            *new_node = new TNode<K, V>(key, value, node, NULL, NULL);
            node->SetRightSon(*new_node);
            size++;
            DoRoll(node, true);
            return SUCCESS;
        }
        return AddAux(node->GetRightSon(), key, value, new_node);
    }
    StatusType DeleteAux(TNode<K, V>* node, K key) {
        if (node == NULL) {
            return FAILURE;
        }
        if(node->GetKey() == key){
            return DeleteByPointer(node);
        }
        if(node->GetKey() > key){
            return DeleteAux(node->GetLeftSon(), key);
        }

        return DeleteAux(node->GetRightSon(), key);
    }
/*
    void GetAllSegmentsByLabelAux(TNode<K, V>* image, int label, int *images, int *segments, int *numOfSegments, int* temp, int index){//לבטל תלות בעץ (להעביר את הפונקציה לstaticeye) על ידי הוספת getroot
        if(image == NULL){
            return;
        }
        GetAllSegmentsByLabelAux(image->GetLeftSon(), label, images, segments, numOfSegments, temp, index);
        int imageSegmentsNum = ((Photo)(image->GetValue())).GetSegmentsByLabel(temp, label);
        *numOfSegments += imageSegmentsNum;
        for (int i = 0; i < imageSegmentsNum; ++i) {
            images[index] = image->GetKey();
            segments[index] = temp[i];
            index++;
        }
        GetAllSegmentsByLabelAux(image->GetRightSon(), label, images, segments, numOfSegments, temp, index);
    }
    */

    TNode<K, V>* DeleteNode(TNode<K, V>* node){
        TNode<K, V>* father = node->GetFather();
        if (node->GetLeftSon() == NULL && node->GetRightSon() == NULL){
            if(node->GetFather() != NULL){
                if (node->GetFather()->GetRightSon() == node){
                    node->GetFather()->SetRightSon(NULL);
                } else{
                    node->GetFather()->SetLeftSon(NULL);
                }
            } else{
                root = NULL;
            }
            delete node;
            return father;
        }

        if (node->GetLeftSon() == NULL){
            if(node->GetFather() != NULL){
                if (node->GetFather()->GetRightSon() == node){
                    node->GetFather()->SetRightSon(node->GetRightSon());
                } else{
                    node->GetFather()->SetLeftSon(node->GetRightSon());
                }
            } else{
                root = node->GetRightSon();
            }
            node->GetRightSon()->SetFather(node->GetFather());
            delete node;
            return father;
        }

        if (node->GetRightSon() == NULL){
            if(node->GetFather() != NULL){
                if (node->GetFather()->GetLeftSon() == node){
                    node->GetFather()->SetLeftSon(node->GetLeftSon());
                } else{
                    node->GetFather()->SetRightSon(node->GetLeftSon());
                }
            } else{
                root = node->GetLeftSon();
            }
            node->GetLeftSon()->SetFather(node->GetFather());
            delete node;
            return father;
        }

        TNode<K, V>* nodeToChange = FindMostLeft(node->GetRightSon());
        nodeToChange->SetLeftSon(node->GetLeftSon());
        nodeToChange->GetLeftSon()->SetFather(nodeToChange);
        TNode<K, V>* temp = node->GetRightSon();
        if ( nodeToChange->GetRightSon() != NULL) {
            nodeToChange->GetRightSon()->SetFather(node);
        }
        node->SetRightSon(nodeToChange->GetRightSon());
        if (temp != nodeToChange){
            nodeToChange->SetRightSon(temp);
            temp->SetFather(nodeToChange);
        } else{
            nodeToChange->SetRightSon(node);
        }
        node->SetLeftSon(NULL);
        temp = node->GetFather();
        if (nodeToChange->GetFather() == node){
            node->SetFather(nodeToChange);
        }else {
            node->SetFather(nodeToChange->GetFather());
            node->GetFather()->SetLeftSon(node);
        }
        nodeToChange->SetFather(temp);
        if (temp != NULL) {
            if (temp->GetLeftSon() == node){
                temp->SetLeftSon(nodeToChange);
            } else{
                temp->SetRightSon(nodeToChange);
            }
        } else{
            root = nodeToChange;
        }

        return DeleteNode(node);
    }
    TNode<K, V>* FindMostLeft(TNode<K, V>* node){
        if (node->GetLeftSon() == NULL){
            return node;
        }
        return FindMostLeft(node->GetLeftSon());
    }
    // onlyOnce is true if we need to roll only once or false if until we get to the root.
    void DoRoll(TNode<K, V>* node, bool onlyOnce){
        if(node == NULL){
            return;
        }
        bool didRoll = false;
        node->UpdateHeight();
        node->UpdateMax();
        if(node->GetBalanceFactor() >= 2){
            if(node->GetLeftSon()->GetBalanceFactor() >= 0){
                assert(node->GetLeftSon() != NULL);
                LLRoll(node->GetLeftSon(),node);
                didRoll = true;
            }
            else {
                assert(node->GetLeftSon() != NULL && node->GetLeftSon()->GetRightSon() != NULL);
                LRRoll(node->GetLeftSon(), node->GetLeftSon()->GetRightSon(), node);
                didRoll = true;
            }
        }
        else if(node->GetBalanceFactor() <= -2){
            if(node->GetRightSon()->GetBalanceFactor() <= 0){
                assert(node->GetRightSon() != NULL);
                RRRoll(node->GetRightSon(),node);
                didRoll = true;
            }
            else {
                assert(node->GetRightSon() != NULL && node->GetRightSon()->GetLeftSon() != NULL);
                RLRoll(node->GetRightSon(), node->GetRightSon()->GetLeftSon(), node);
                didRoll = true;
            }
        }
        /*if(onlyOnce && didRoll) {
            return;
        }*/
        DoRoll(node->GetFather(), onlyOnce);
    }
    //A is the Left son of B at first
    void LLRoll(TNode<K, V>* A, TNode<K, V>* B){
        B->SetLeftSon(A->GetRightSon());
        if(A->GetRightSon() != NULL) {
            A->GetRightSon()->SetFather(B);
        }
        A->SetRightSon(B);
        A->SetFather(B->GetFather());
        if(A->GetFather() != NULL){
            if(A->GetFather()->GetRightSon() == B){
                A->GetFather()->SetRightSon(A);
            }
            else{
                A->GetFather()->SetLeftSon(A);
            }
        }
        else{
            root = A;
        }
        B->SetFather(A);
        B->UpdateHeight();
        B->UpdateMax();
        A->UpdateHeight();
        A->UpdateMax();
    }
    //A is the right son of B at first
    void RRRoll(TNode<K, V>* A, TNode<K, V>* B){
        B->SetRightSon(A->GetLeftSon());
        if(A->GetLeftSon() != NULL) {
            A->GetLeftSon()->SetFather(B);
        }
        A->SetLeftSon(B);
        A->SetFather(B->GetFather());
        if(A->GetFather() != NULL){
            if(A->GetFather()->GetRightSon() == B){
                A->GetFather()->SetRightSon(A);
            }
            else{
                A->GetFather()->SetLeftSon(A);
            }
        }
        else{
            root = A;
        }
        B->SetFather(A);
        B->UpdateHeight();
        B->UpdateMax();
        A->UpdateHeight();
        A->UpdateMax();
    }
    //B is the right son of A, A is the left son of C at first
    void LRRoll(TNode<K, V>* A, TNode<K, V>* B, TNode<K, V>* C){
        A->SetRightSon(B->GetLeftSon());
        if(A->GetRightSon() != NULL){
            A->GetRightSon()->SetFather(A);
        }
        C->SetLeftSon(B->GetRightSon());
        if(C->GetLeftSon() != NULL){
            C->GetLeftSon()->SetFather(C);
        }
        B->SetFather(C->GetFather());
        if(B->GetFather() != NULL){
            if(B->GetFather()->GetRightSon() == C){
                B->GetFather()->SetRightSon(B);
            }
            else{
                B->GetFather()->SetLeftSon(B);
            }
        }
        else{
            root = B;
        }
        C->SetFather(B);
        A->SetFather(B);
        B->SetLeftSon(A);
        B->SetRightSon(C);
        A->UpdateHeight();
        A->UpdateMax();
        C->UpdateHeight();
        C->UpdateMax();
        B->UpdateHeight();
        B->UpdateMax();
    }
    //B is the left son of A, A is the right son of C at first
    void RLRoll(TNode<K, V>* A, TNode<K, V>* B, TNode<K, V>* C){
        A->SetLeftSon(B->GetRightSon());
        if(A->GetLeftSon() != NULL){
            A->GetLeftSon()->SetFather(A);
        }
        C->SetRightSon(B->GetLeftSon());
        if(C->GetRightSon() != NULL){
            C->GetRightSon()->SetFather(C);
        }
        B->SetFather(C->GetFather());
        if(B->GetFather() != NULL){
            if(B->GetFather()->GetRightSon() == C){
                B->GetFather()->SetRightSon(B);
            }
            else{
                B->GetFather()->SetLeftSon(B);
            }
        }
        else{
            root = B;
        }
        C->SetFather(B);
        A->SetFather(B);
        B->SetRightSon(A);
        B->SetLeftSon(C);
        A->UpdateHeight();
        A->UpdateMax();
        C->UpdateHeight();
        C->UpdateMax();
        B->UpdateHeight();
        B->UpdateMax();
    }
    void TreeDestroyer(TNode<K, V>* toDelete){
        if(toDelete == NULL){
            return;
        }
        TreeDestroyer(toDelete->GetLeftSon());
        TreeDestroyer(toDelete->GetRightSon());
        delete(toDelete);
    }

public:
    RTree():root (NULL), size (0){}

    ~RTree(){
        TreeDestroyer(root);
    }

    StatusType Add(const K& key, const V& value, TNode<K, V>** node){
        return AddAux(root, key, value, node);
    }

    StatusType Find(const K& key, V* value) {
        return FindAux(root, key, value);
    }

    StatusType Delete(const K& key){
        return DeleteAux(root, key);
    }

    StatusType DeleteByPointer(TNode<K, V>* node){ // לבדוק האם מקבלים מצביע לנוד או את הנוד עצמו
        TNode<K, V>* bottom = DeleteNode(node);
        size--;
        DoRoll(bottom, false);
        return SUCCESS;
    }

    StatusType Size(int *n){
        *n = size;
        return SUCCESS;
    }

    bool IsSearch(){
        return root->IsSearch();
    }

    bool IsBalanced(){
        return root->IsBalanced();
    }

    TNode<K, V>* GetRoot(){
        return root;
    }

    V GetMax(){
        return root->GetMaxKey();
    }

    StatusType SetValue(const K& key,const V& value){
        return SetValueAux(root, key, value);
    }


/*
    void GetAllSegmentsByLabel(int label, int *images, int *segments, int *numOfSegments, int* temp){
        GetAllSegmentsByLabelAux(root, label, images, segments, numOfSegments, temp, 0);
    }
    */
};



#endif //DS_WET2_RTREE_H
