#ifndef HASHMAP_H
#define HASHMAP_H

//credit for the hashmap is given to UTHash from: http://troydhanson.github.io/uthash/
#include "uthash.h"
#include "index.h"

//holds the key and a LinkedList of Indexes, from index.c
//UT_hash_handle is what uthash uses to create our hashmap
struct Hashmap{
	char * key;
	IndexPtr indexList;
	UT_hash_handle hh;
};
typedef struct Hashmap * hashPtr;

/*
 * Used to clear our hash in main when we are done with it
 */
void clearHash(hashPtr *);

/*
 * Adds an index to a hash, given a key (the token)
 */
void addIndex(hashPtr *, char *, IndexPtr);

/*
 * Not used, only for debugging
 */
void printTable(hashPtr *);


#endif