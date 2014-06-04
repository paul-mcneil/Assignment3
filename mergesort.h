#ifndef MERGESORT_H
#define MERGESORT_H

#include "index.h"

/**
 * Finds the middle point of the list head and stores the first half
 * in the given frontStorage and backStorage
 * @param head     List which you are trying to split in half
 * @param frontStorage Empty list1 given from caller
 * @param backStorage Empty list2 given from caller
 */
void splitList(IndexPtr head, IndexPtr *, IndexPtr *);

/**
 * Merges two separate lists in a sorted fashion
 * @return        A pointer to a sorted list acquired by 
 * merging list1 and list2, takes no longer than O(n), where
 * n is the total number of elements (from list1 and list2)
 */
IndexPtr sortedMerge(IndexPtr, IndexPtr);

//simple mergesort implementation
void mergeSort(IndexPtr *);

#endif
