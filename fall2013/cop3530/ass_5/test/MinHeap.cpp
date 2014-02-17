#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include "MinHeap.h"

using namespace std;

/*int main(){


  arrayList *a = new arrayList();
  for (int i = 0; i < 10; i++){
        a->insert(i, 10-i); // rand()%100
  }

  MinHeap* min;
  min = new MinHeap;
  min->initialize(a,10);
  // min->preOrder(0);
  // cout << endl;
  // min->inOrder(0);
  // cout << endl;
  // min->postOrder(0);
  // cout << endl;
  // min->sort();
  min->insert(1);
  min->insert(5);
  min->insert(2);
  // min->preOrder(0); 
  min->bin->elems->traverse();

}*/

void MinHeap::initialize(arrayList* a, int length){
    bin = new BinaryTree;
    bin->initialize(a, length);
}
void MinHeap::preOrder(int beg){

  bin->preOrder(beg);

}

void MinHeap::inOrder(int beg){

  bin->inOrder(beg);

}

void MinHeap::postOrder(int beg){

  bin->postOrder(beg);

}

void MinHeap::sort(){

  bin->sort();

}

void MinHeap::heapify(int index){

    bin->heapify(index, true);

}

void MinHeap::insert(int elem){

    bin->insert(elem);

}