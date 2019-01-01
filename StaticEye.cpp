#include "StaticEye.h"//
// Created by nadav.elias on 01-Jan-19.
//

StaticEye::StaticEye(int numOfPixels) : numOfPixels(numOfPixels), images(numOfPixels){};

StatusType StaticEye::AddImage(int imageID){
    if (imageID <= 0)
        return INVALID_INPUT;
    return images.Add(imageID);
}

StatusType StaticEye::DeleteImage(int imageID){
    if (imageID <= 0)
        return INVALID_INPUT;
    return images.Remove(imageID);
}

StatusType StaticEye::SetLabelScore(int imageID, int pixel, int label, int score){
    if (imageID <= 0 || score <= 0 || label <= 0 || pixel < 0 || pixel >=  numOfPixels)
        return INVALID_INPUT;
    UFind* image = images.Find(imageID);
    if (image == NULL)
        return FAILURE;
    TNode<int, int>* trash;
    return image->Find(pixel)->GetLabels()->Add(label, score, &trash);
}

StatusType StaticEye::ResetLableScore(int imageID, int pixel, int label){
    if (imageID <= 0 || label <= 0 || pixel < 0 || pixel >=  numOfPixels)
        return INVALID_INPUT;
    UFind* image = images.Find(imageID);
    if (image == NULL)
        return FAILURE;
    TNode<int, int>* trash;
    return image->Find(pixel)->GetLabels()->Delete(label);
}

StatusType StaticEye::GetHighestScoredLabel(int imageID, int pixel, int* label){
    if (imageID <= 0 || label == NULL || pixel < 0 || pixel >=  numOfPixels)
        return INVALID_INPUT;
    UFind* image = images.Find(imageID);
    if (image == NULL)
        return FAILURE;
    TNode<int, int>* trash;
    return image->Find(pixel)->GetLabels()->GetMax(label);
}

StatusType StaticEye::MergeSuperPixels(int imageID, int pixel1, int pixel2){
    if (imageID <= 0 || pixel1 < 0 || pixel1 >=  numOfPixels || pixel2 < 0 || pixel2 >=  numOfPixels)
        return INVALID_INPUT;
    UFind* image = images.Find(imageID);
    if (image == NULL)
        return FAILURE;
    return image->Merge(pixel1, pixel2);
}

#include "StaticEye.h"
