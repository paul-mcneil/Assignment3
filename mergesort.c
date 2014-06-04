#include "mergesort.h"

void mergeSort(IndexPtr * list){
	IndexPtr head= *list;
	IndexPtr store1; //when list is split in half first half is stored in store1
	IndexPtr store2; //and the second half is stored in store2

	if((head== NULL) || (head->next == NULL))
		return;
	
	splitList(*list, &store1, &store2);

	mergeSort(&store1); 
	mergeSort(&store2);

	*list = sortedMerge(store1, store2); //but them back together in a sorted manner
}

IndexPtr sortedMerge(IndexPtr list_a, IndexPtr list_b){
	IndexPtr result = (IndexPtr) malloc(sizeof(struct IndexItem));
	IndexPtr tail = result;

	if(list_a == NULL)
		return list_b;
	else if(list_b == NULL)
		return list_a;
	else{
		while(list_a!=NULL && list_b!=NULL){
			if(sortFrequencies(list_a, list_b) <1){ //compare function from index.c
				tail->next = list_a; list_a = list_a->next;
			}
			else{
				tail->next = list_b; list_b = list_b->next;
			}
			tail = tail->next;
		}
		//if one of the lists was longer than the other
		while(list_a!=NULL){
			tail->next = list_a; list_a = list_a->next; tail = tail->next;
		}
		while(list_b!=NULL){
			tail->next = list_b; list_b = list_b->next; tail = tail->next;
		}
		tail = result; //don't need tail anymore so use it to free the 
		//first element in result which was used as a placeholder
		result = result->next; //first node of result is a null placeholder
		free(tail); 
	}
	return result;
}

void splitList(IndexPtr head, IndexPtr * frontStorage, IndexPtr * backStorage){
	//used to find the middle of the list
	IndexPtr middleNode;
	IndexPtr endNode;

	// length < 2, base case
	if(head == NULL || head == NULL){
		*frontStorage = head;
		*backStorage = NULL;
		return;
	}
	else{
		middleNode = head;
		endNode = head->next;
		/* Advance endNode two nodes and middleNode one node */
		while(endNode != NULL)
		{
			endNode = endNode->next;
			if(endNode != NULL)
			{
				middleNode = middleNode->next;
				endNode = endNode->next;
			}
		}
		/* middleNode is before the midpoint in the list
		*  so split it in two
		*/
		*frontStorage = head;
		*backStorage = middleNode->next;
		middleNode->next = NULL;
	}
}
