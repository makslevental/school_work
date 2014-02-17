/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#ifndef MaxWinnerTree_
#define MaxWinnerTree_

#include "BinaryTree.h"

using namespace std;

class BinaryTree;

class MaxWinnerTree : public BinaryTree{
	
	public:
		MaxWinnerTree(){}
		MaxWinnerTree(const int& bins, const int& binsize);
		~MaxWinnerTree(){}
		void ReplayMatches(Node* bucket);
		void insert(const int& key, const int& value);
		void initialize(Node *ptr, int key, int value, int depth, int limit);
		void placeItem(int n, Node* bucket);
		void openBucket(Node* bucket);
		Node* returnFirstEmpty();
		void showAllBuckets();
		Node** buckets;
		int binCapacity;
		int bucketsOpened;
};










#endif