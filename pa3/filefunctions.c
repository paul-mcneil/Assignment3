#include "filefunctions.h"

void truncateSlash(char * path){
	if(path[strlen(path)-1] == '/')
		path[strlen(path)-1] = '\0';
}

long getFileSize(FILE *fp){
	long fileSize;

	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);

	return fileSize;
}

int readsFile(FILE * fp, char * path, SortedListPtr sl, hashPtr *hash_t){
	long fileSize = getFileSize(fp);
	char line[fileSize]; //initiate the buffer to the size of the file so tokens aren't broken
	TokenizerT * tk;
	char * data;

	while(fgets(line, fileSize, fp) != NULL){
		tk = TKCreate(line);
		IndexPtr index; //explanation of IndexPtr in index.h

		while((data = TKGetNextToken(tk)) != NULL){
			allToLowerCase(data); //function I created in tokenizer.c
			index = indexCreate(path);
			addIndex(hash_t, data, index); //adds the index item to the hashtable with token as the key
			SLInsert(sl, data); //keeps track of all the words, a sorted keyset for the hashtable
		}
		TKDestroy(tk);
	}

	//since this function  is the one that does all the work 
	//in the file we can safely close it
	fclose(fp);

	return 0;
}

int SortedWriteToFile(FILE * fp, SortedListPtr sl, hashPtr *hash_t){
	if(sl == NULL || hash_t == NULL) //either of the two structs weren't allocated properly
		return -1;
	else if(sl->head == NULL) //no words in the list
		return -2;
	else{
		char * token;
		IndexPtr traverse;
		hashPtr hashLocation; //HASH_FIND_STR needs an output pointer
		SortedListIteratorPtr iter = SLCreateIterator(sl); //sorted keyset

		while((token = SLNextItem(iter)) != NULL){
			fprintf(fp, "<list> %s\n", token);
			HASH_FIND_STR(*hash_t, token, hashLocation); //get the values in a sorted fashion
			traverse = hashLocation->indexList;
			mergeSort(&traverse); //sort the indexes by decreasing frequency

			while(traverse!=NULL){
				fprintf(fp, "%s %d ", traverse->filename, traverse->wordCount);
				traverse=traverse->next;
			}

			fprintf(fp, "\n<\\list>\n");
		}
		return 0;
	}
}

int traverseDir(char * dirname, char * parent, SortedListPtr sl, hashPtr *hash_t){
	DIR * direc=NULL;
	FILE * fp;
	struct dirent * entry;    
	extern int errno;	
	int length; //used to concat paths and truncate paths

	//first call to function, from main, parent will be NULL
	if(parent == NULL){	
		char fulldir[750]; //max length of directory is 750 characters which should be enough for regular tests
		strcpy(fulldir, dirname); //fulldir will hold the full path of whatever we visit
		length = strlen(fulldir); //used for adding a new directory to the end

		if((fp = fopen(fulldir,"r+")) == NULL){ //try to open as file
			if(errno == EISDIR){ //if it is a directory
				if((direc = opendir(fulldir))==NULL){ //if an error occurs opening directory
					printf("ERROR with file or directory - %s: %s\n", fulldir, strerror(errno));
					return -1;
				}
				else{
					while((entry = readdir(direc)) != NULL){ //recursively open the directory
						if(entry->d_name[0] != '.'){
							traverseDir(entry->d_name, fulldir, sl, hash_t);
							fulldir[length] = '\0'; // after recursion is done bring it back to original directory
						}
					}
				}
			}
			else{
				printf("ERROR with file or directory - %s: %s\n", fulldir, strerror(errno));
				return -1;
			}
		}	
		else{
			readsFile(fp, fulldir, sl, hash_t); //if opening the file wasn't a problem, read it
		}
	}
	else{
		length = strlen(parent);
		parent[length] = '/';
		parent[++length] = '\0';
		strcat(parent, dirname);
		
		if((fp = fopen(parent,"r+")) == NULL){
			if(errno == EISDIR){
				if((direc = opendir(parent))==NULL){
					printf("ERROR with file or directory - %s: %s\n", parent, strerror(errno));
					return -1;
				}		
				else{	
					while((entry = readdir(direc)) != NULL){
						length = strlen(parent); //saves length for getting back to this directory
						if(entry->d_name[0] != '.'){
							traverseDir(entry->d_name, parent, sl, hash_t);
							parent[length] = '\0'; //after you get back to original path cut the old directories out
						}
					}
				}
			}
			else{
				printf("ERROR with file or directory - %s: %s\n", parent, strerror(errno));
				return -1;
			}
		}	
		else{
			readsFile(fp, parent, sl, hash_t);
		}
	}	
	
	if(direc != NULL)
		closedir(direc);

	return 0;
}
