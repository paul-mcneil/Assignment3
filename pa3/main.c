#include <stdio.h>
#include <string.h>
#include "sorted-list.h"
#include "filefunctions.h"
#include "sorted-list.h"
#include "hashmap.h"

int main(int argc, char** argv)
{
	if(argc != 3){
		printf("Illegal number of arguments\n");
		exit(1);
	}
	else{
		char * outputFileName = argv[1];
		char * inputDirName = argv[2];
		FILE * ifp; //input file sream
		FILE * ofp; //output file stream
		//sl is used as a sort of "sorted keyset" for the hashmap since key values are returned
		//by time added, this makes sure keys are sorted
		SortedListPtr sl = SLCreate(compareStrings, destroyBasicTypeAlloc);
		hashPtr indexHash = NULL;
		char option = '\0';

		if((ifp = fopen(inputDirName,"r+")) == NULL)
			if(errno == EISDIR){
				//if a slash is added to the end of directory remove it
				//only for formatting purposes
				truncateSlash(inputDirName);
				traverseDir(inputDirName, NULL, sl, &indexHash);
			}
			else{
				perror("Error encountered while trying to open file or directory");
				exit(2);
			}
		else{
			readsFile(ifp, inputDirName, sl, &indexHash);
		}

		if((ofp = fopen(outputFileName,"r")) == NULL){ //check if file exists
			if(errno == ENOENT){ //if it doesnt
				fclose(ofp); //close the file opened for reading
				ofp = fopen(outputFileName,"w"); //and create it for writing
				if(SortedWriteToFile(ofp, sl, &indexHash) == -2)
				printf("No words were found.\n");
			}
			else{
				perror("Error trying to open output file");
				exit(2);	
			}
		}
		else{
			printf("File exists, override file (y/n)? "); //if it exists ask user to override
			scanf("%c", &option);
			if(option == 'y'){
				fclose(ofp);
				ofp = fopen(outputFileName,"w");
				if(SortedWriteToFile(ofp, sl, &indexHash) == -2)
					printf("No words were found.\n");
			}
		}
		
		//clean mess
		if(ifp!=NULL)
			fclose(ifp);
		if(ofp!=NULL)
			fclose(ofp);
		clearHash(&indexHash);
		SLDestroy(sl);
	}	

	return 0;
}
