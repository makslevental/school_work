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
#include "myException.h"
#include "MaxWinnerTree.h"

MaxWinnerTree::MaxWinnerTree(const int& bins, const int& binsize){
	
	size = bins;
	binCapacity = binsize; 
	bucketsOpened = 0;
	int depth = (int)ceil(log2(bins));
	buckets = new Node*[(int)pow(2,depth)];
	root = new Node(1,0);
	initialize(root,2,0,1,depth);

}

void MaxWinnerTree::initialize(Node *ptr, int key, int value, int depth, int limit){
	
	ptr->leftChild = new Node(key, ptr, value);
	ptr->rightChild = new Node(key+1, ptr, value);
	if(depth == limit){ 
		buckets[key-(int)pow(2,limit)] = ptr->leftChild;
		buckets[key+1-(int)pow(2,limit)] = ptr->rightChild;
		return;
	}
	initialize(ptr->leftChild,2*key, value, depth+1, limit);
	initialize(ptr->rightChild,2*(key+1), value, depth+1, limit);

}

void MaxWinnerTree::ReplayMatches(Node* bucket){
	Node* current = bucket;
	while(current->parent){
		current = current->parent;
		current->value = current->leftChild->value>=current->rightChild->value?current->leftChild->value:current->rightChild->value;
	}
}

void MaxWinnerTree::insert(const int& key, const int& value){
	return;
}

void MaxWinnerTree::placeItem(int n, Node* bucket){
	bucket->value -= n;
	ReplayMatches(bucket);
}

BinaryTree::Node* MaxWinnerTree::returnFirstEmpty(){
	// so that it starts searching in front of opened buckets
	// instead of returning buckets whose capacity has been reduced
	// to zero.
	int i = bucketsOpened;
	while(i<size)
		if(buckets[i++]->value == 0)
			return buckets[i-1];
}

void MaxWinnerTree::openBucket(Node* bucket){
	bucketsOpened++;
	bucket->value = binCapacity;
	ReplayMatches(bucket);
}

void MaxWinnerTree::showAllBuckets(){
	for(int i = 0; i < size; i++){
		buckets[i]->print();
	}
}
/*
int main(){
	int n;
	cout << "buckets ";
	cin >> n;
	MaxWinnerTree* max = new MaxWinnerTree(n,10);
	max->preOrderPrint();
	cout << endl;
	for(int i = 0; i < max->size; i++){
		max->buckets[i]->print();
	}
	cout << endl;
	srand(time(NULL));
	for(int i = 0; i < max->size; i++){
		max->buckets[i]->value = rand()%10;
		max->ReplayMatches(max->buckets[i]);
	}
	cout << endl;
	for(int i = 0; i < max->size; i++){
		max->buckets[i]->print();
	}
	cout << endl;
	max->root->print();

	int k;
	cin >> k;
	max->buckets[k]->value = 0;
	max->ReplayMatches(max->buckets[k]);
	max->root->print();
	
}*/