/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#ifndef BinPacking_
#define BinPacking_

#include "MaxWinnerTree.h"

class BinPacking{

	public:

		BinPacking(bool which, int numObject, int binCapacity);
		~BinPacking();
		void firstFit(int n);
		void bestFit(int n);

		MaxWinnerTree* max;
		BinaryTree* bin;
		int bins;
		int size;
		bool whic;
		int bucketsopen;
		int objectpacked;
		int* list;


};

#endif

