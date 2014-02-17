#ifndef PriorityQueue_
#define PriorityQueue_

#include "MinHeap.h"

using namespace std;

class PriorityQueue{
  public:
    PriorityQueue(){};
    void initialize(arrayList*, int);
    void preOrder(int);
    void inOrder(int);
    void postOrder(int);
    void sort();
    void insert(int);
    MinHeap *min;

};

#endif
