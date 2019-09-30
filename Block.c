//Nikhil Krishna
//niekrish
//CMPS-12B/M
//Block.c
//Implements the creator method, the destructor method, a hash function and a print method.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Block.h"

// constructor for the Block type, create the space for the data, make a copy!
Block newBlock(char* data, int id, long hash){
	Block temp =(Block) malloc(sizeof(struct BlockObj));
	temp->data = (char *) malloc(sizeof(strlen(data) + 1));
	strcpy(temp->data, data);
	temp->id = id;
	temp->prevHash = hash;//save the hash value
	temp->next = NULL;
	return temp; 
}

// destructor for the Block type
void freeBlock(Block B){
	if(B != NULL){
		if(B->data != NULL) free((void*)B->data);//first free the space allocated for data
		B->next = NULL;
		free((void*)B);
	}
}

// return a pointer to this block's data.
// It would probably be better to return a copy to avoid, easy erroneous manipulation of blocks,
// but for demonstration purposes we are going to expose the actual block data.
char* data(Block B){
	return B->data;
}
// return the stored previousHash from this block
long previousHash(Block B){
	return B->prevHash;
}

// recomute the hash value for this block
long hash(Block B){
	long temp = 0;
	int length;
	int i;
	if(B == NULL) return -1;
	length = strlen(B->data);
	for(i = 0; i < length; i++){
		temp = temp + B->data[i];
		temp = temp << 6; // preserve order of data
		temp = temp ^ temp >> 32; //keep MSB history
	}
	return temp;
}

// print the block id and data
// (NOTE: for debugging purposes you may want to have it also print the hash and previousHash values during development.)
void printBlock(FILE* out, Block B){
	//fprintf(out, "id = %d, data = %s, hash = %lx, prevHash = %lx\n", B->id, B->data, hash(B), B->prevHash);
	fprintf(out, "id = %d, data = %s\n", B->id, B->data);
}

