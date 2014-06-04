#include "index.h"

int sameIndexes(IndexPtr i1, IndexPtr i2){
	return (strcmp(i1->filename, i2->filename) == 0) ? 1 : 0;
}

int sortFrequencies(IndexPtr i1, IndexPtr i2){
	return (i1->wordCount < i2->wordCount) ? 1 : (i1->wordCount > i2->wordCount) ? -1 : 0;
}

IndexPtr indexCreate(char * file){
	char * fileptr = NULL;

	IndexPtr index = (IndexPtr) malloc(sizeof(struct IndexItem));
	//must allocate memory for the file char or else it'll be lost
	if(file != NULL){
		fileptr = (char *) malloc(strlen(file)+1);
		strcpy(fileptr, file);
	}
	
	index->filename = fileptr;
	index->wordCount = 1;
	index->next = NULL;

	return index;
}

IndexPtr indexFind(IndexPtr listOfIndexes, IndexPtr indexToFind){
	IndexPtr traverse = listOfIndexes; //create a separate pointer so list isn't lost

	if(listOfIndexes == NULL || listOfIndexes->filename == NULL ) //if the list is empty
		return NULL;
	else{
		while(traverse->next != NULL){
			if(sameIndexes(traverse, indexToFind))
				return traverse;
			traverse=traverse->next;
		}
	}
	
	//if it falls outside of loop it wasn't found, it returns the address to the last item so that it could be added
	return traverse;
}

void destroyIndexList(IndexPtr head){
	IndexPtr deleter;
	while(head!=NULL){
		deleter = head;
		head = head->next;
		free(deleter->filename);
		free(deleter);
	}
}