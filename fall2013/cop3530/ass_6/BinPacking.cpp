/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "BinPacking.h"


BinPacking::BinPacking(bool which, int numObject, int binCapacity){
	
	bins = numObject;
	size = binCapacity;
	whic = which;
	list = new int[bins];
	bucketsopen = 0;
	objectpacked = 0;

	if(which){
		max = new MaxWinnerTree(numObject, binCapacity);
	}
	else{
		bin = new BinaryTree();
	}
}
BinPacking::~BinPacking(){
	if(whic){
		delete max;
	}
	else
		delete bin;
}
void BinPacking::firstFit(int n){
	MaxWinnerTree::Node* current = max->root;

	while(current->leftChild){
		if(current->value >= n)
			current = current->leftChild;
		else if(current->value < n)
			if(current == max->root){
				if(max->bucketsOpened == bins){
					cout << "no more new buckets available";
					return;
				}
				MaxWinnerTree::Node* newBucket = max->returnFirstEmpty();
				max->openBucket(newBucket);
			}
			else
				current = current->parent->rightChild;
	}
	// while loop dies before search is able to get out of leaf node
	// that's too small. but if you're at a leaf node that means
	// leaf node's parent had a winner value greater than or equal
	// to object size. so bin's right neighbor, parent's other child
	// must be the right one.
	if(current->value < n) current = current->parent->rightChild;
	list[objectpacked++] = current->key - pow(2,ceil(log2(bins)));
	max->placeItem(n, current);
	if(objectpacked == bins){
		for(int i = 0; i < objectpacked; i++)
			cout << "Pack object " << i+1 << " in bin " << list[i]+1 << endl;
	}
}

void BinPacking::bestFit(int n){

	MaxWinnerTree::Node* current = bin->root;
	MaxWinnerTree::Node* next;
	MaxWinnerTree::Node* candidate = new MaxWinnerTree::Node(999999, 4416);
	while(current){
		if(current->key == n){
			candidate = current;
			break;
		}
		else if(current->key > n){
			if(current->key < candidate->key){
				candidate = current;
				current = current->leftChild;
			}
			else{
				current = current->leftChild;
			}
		}
		else if(current->key < n)
			current = current->rightChild;
	}

	if(candidate->value == 4416){
		int k = ++bucketsopen;
		bin->insert(size-n, k);
		list[objectpacked++] = k;
	}
	else{
		int candidateSize = candidate->key;
		// value is bin number, in order of bins created
		int candidateValue = candidate->value;
		list[objectpacked++] = candidateValue;
		bin->eraseNode(candidate);
		bin->insert(candidateSize-n, candidateValue);
	}
	if(objectpacked == bins){
		for(int i = 0; i < objectpacked; i++){
			cout << "Pack object " << i+1 << " in bin " << list[i];
			cout << endl;
		}
	}
	
}
/*
int main(){
	// BinPacking* binPackFirst = new BinPacking(true, 12, 6);
	// binPackFirst->firstFit(2);
	// binPackFirst->firstFit(5);
	// binPackFirst->firstFit(5);
	// binPackFirst->firstFit(1);
	// binPackFirst->firstFit(1);
	// binPackFirst->firstFit(3);
	// binPackFirst->firstFit(4);
	// binPackFirst->firstFit(6);
	// binPackFirst->firstFit(2);
	// binPackFirst->firstFit(5);
	// binPackFirst->firstFit(6);
	// binPackFirst->firstFit(1);


 	BinPacking* binPackFirst = new BinPacking(false, 12, 6);
	binPackFirst->bestFit(2);
	binPackFirst->bestFit(5);
	binPackFirst->bestFit(5);
	binPackFirst->bestFit(1);
	binPackFirst->bestFit(1);
	binPackFirst->bestFit(3);
	binPackFirst->bestFit(4);
	binPackFirst->bestFit(6);
	binPackFirst->bestFit(2);
	binPackFirst->bestFit(5);
	binPackFirst->bestFit(6);
	binPackFirst->bestFit(1);

}*/