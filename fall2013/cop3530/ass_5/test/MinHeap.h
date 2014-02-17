#ifndef MinHeap_
#define MinHeap_

#include "BinaryTree.h"

using namespace std;

class MinHeap{
  public:
    MinHeap(){};
    void initialize(arrayList*, int);
    void preOrder(int);
    void inOrder(int);
    void postOrder(int);
    void sort();
    void insert(int);
    BinaryTree *bin;
  protected:

    void heapify(int);


};

#endif
