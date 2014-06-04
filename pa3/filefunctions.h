#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include "sorted-list.h"
#include "hashmap.h"
#include "tokenizer.h"
#include "mergesort.h"

/*
 * Truncates the slash at the end of a path name if one exists, simply for formatting reasons
 * because traverseDir already adds a slash
 * If no slash exists text is not altered
 */
void truncateSlash(char *);

/*
 * Returns the size of the file given in order to allocate enough memory for the buffer
 * The buffer allocated at real time assures that no tokens are broken up wtihout doing
 * any complicated checks. Buffer is not allocated dynamically so memory is given back
 * when function returns
 */
long getFileSize(FILE *);

/*
* Will read a certain file given to it and fill in the given list of ordered words
* Returns: 0 if sucessful, nonzero if error occurs
*/
int readsFile(FILE *, char *, SortedListPtr, hashPtr *);

/*
* Writes out the results of our hash to the file specified by the argument
* Returns: 0 if successful, nonzero if error occurs
*/
int SortedWriteToFile(FILE *, SortedListPtr, hashPtr *);

/*
* Traverses a directory recursively and whenever it encounters a file in the directory calls readsFile();
* Returns: 0 if successful, nonzero if error occurs
*/
int traverseDir(char *, char *, SortedListPtr, hashPtr *);

#endif