#ifndef INDEX_H
#define INDEX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//simply a linkedlist of index items, which holds the filename (full path) and the frequency of
//the word in that file
struct IndexItem{
	char * filename; 
	int wordCount;
	struct IndexItem * next;
};
typedef struct IndexItem * IndexPtr;

/*
* compares indexes so that the frequency can be incremented
* which simply means if there are more than one of this word in this file
* 1 means they are the same, 0 means they arent (true or false)
*/
int sameIndexes(IndexPtr, IndexPtr);

/*
* sorting function for the frequencies, used in mergesort.c
*/
int sortFrequencies(IndexPtr, IndexPtr);

/*
* Creates an index item with the given path
*/
IndexPtr indexCreate(char *);

/*
 * Returns a pointer to an index being looked for in a given list
 * or the last pointer in the list if it was not found (so that it could be added)
 */
IndexPtr indexFind(IndexPtr, IndexPtr);

/*
 * Destroys ALL the indexes given a list, used to clear the hashtable
 */
void destroyIndexList(IndexPtr);

#endif