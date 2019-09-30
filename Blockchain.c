//Nikhil Krishna
//niekrish
//CMPS-12B/M
//Blockchain.c
//Methods to start a blockchain, delete a blockchain, remove from a blockchain, adding to the end of a blockchain, and checking the validity of a blockchain.

#include <stdio.h>
#include <stdlib.h>
#include "Blockchain.h"

// constructor for the Blockchain type
Blockchain newBlockchain(){
	Blockchain temp =(Blockchain) malloc(sizeof(struct BlockchainObj));
	temp->head = NULL;
	temp->hash = 0;
	temp->size = 0;
	return temp;
}

// destructor for the Blockchain type
void freeBlockchain(Blockchain B){
	while(B->size) removeLast(B);
	if (B != NULL) free((void *) B); //free the blockchain
}

// append a new block to the chain with the data specified in the new block
// return the size of the block chain if successful and 0 otherwise
int append(Blockchain B, char* data){
	Block temp;
	int travel = 1;
	if(B == NULL) return 0;
	temp = B->head;
	if(B->head == NULL){ //if it is first element
		B->head = newBlock(data, B->size, B->hash);
		B->hash = hash(B->head);
		B->size = B->size + 1;
		return B->size;
	}
	while(temp->next != NULL){ //move to the end of the blockchain
		temp = temp->next;
		travel++; //keep track of how many steps you moved
	}
	if(travel != B->size){ //check that the number of steps matches the size of the blockchain
		fprintf(stderr, "Blockchain size error\n");
	}
	temp->next = newBlock(data, B->size, hash(temp)); //add at the end of the blockchain
	B->size = B->size + 1;
	return B->size;
}	

// return the number of blocks in this chain
int size(Blockchain B){
	return B->size;
}

// return the block at index idx in the chain
Block get(Blockchain B, int idx){
	Block temp;
	if(B == NULL) return NULL;
	temp = B->head;
	while(temp->id != idx){ //move through blockchain until id is found
		if(temp->next == NULL) return NULL;
		temp = temp->next;
	}
	return temp;	
}

// check if this is a valid chain by checking the stored previousHash values in each block
// return 1 if valid, 0 otherwise
int valid(Blockchain B){
	Block temp;
	long keepHash;
	if(B == NULL) return 0;
	if(B->head == NULL){ //zero element blockchain is still valid
		if(B->size == 0) return 1;
		else return 0;
	}
	else{
		if(B->hash != hash(B->head)) return 0;
	}
	temp = B->head;
	while(temp->next != NULL){
		keepHash = hash(temp);
		temp = temp->next;
		if(temp != NULL){
			if(temp->prevHash != keepHash) return 0; //if previous hash does not match the blockchain is not valid
		}
	}
	return 1;
}

// shorten the chain by revmoing the last block
// do nothing if the chain is already empty
void removeLast(Blockchain B){
	Block temp;
	Block prevTemp;
        if(B == NULL) return;
	if(B->head == NULL) return;
	if(B->size == 1){ //remove the first element in the blockchain
		freeBlock(B->head);
		B->size = 0;
		B->hash = 0;
		B->head = NULL;
		return;
	}
	temp = B->head;
	prevTemp = temp;
	while(temp->next != NULL){ //move to the last element, prevTemp has the last but one element
		prevTemp = temp;
		temp = temp->next;
	}
	freeBlock(temp);
	prevTemp->next = NULL;
	B->size--;
}

// print the chain
void printBlockchain(FILE* out, Blockchain B){
	Block temp;
	if(B == NULL) fprintf(out, "Empty block chain\n");
	if(B->head == NULL) fprintf(out, "No elements in chain\n");
	temp = B->head;
	while(temp != NULL){
		printBlock(out, temp);
		temp = temp->next;
	}
}
