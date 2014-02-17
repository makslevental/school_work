#ifndef BinaryTree_
#define BinaryTree_

#include "Arraylist.h"

using namespace std;

class BinaryTree{
  public:
    BinaryTree(){};
    // ~BinaryTree();
    void initialize(arrayList*, int);
    void preOrder(int);
    void preOrder1(int);
    void inOrder(int);
    void inOrder1(int);
    void postOrder(int);
    void postOrder1(int);
    void sort();
    void heapify(int, bool);
    void insert(int);
    arrayList *elems;
    
  protected:
    int size;
    void percolateUp(int);

};

#endif

