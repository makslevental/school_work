/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include "PriorityQueue.h"

using namespace std;

/*int main(){


  arrayList *a = new arrayList();
  for (int i = 0; i < 10; i++){
        a->insert(i, 10-i); // rand()%100
  }

  PriorityQueue* pri;
  pri = new PriorityQueue;
  pri->initialize(a,10);
  // pri->preOrder(0);
  // cout << endl;
  // pri->inOrder(0);
  // cout << endl;
  // pri->postOrder(0);
  // cout << endl;
  // pri->sort();
  pri->insert(1);
  pri->insert(5);
  pri->insert(2);
  // pri->preOrder(0); 
  pri->min->bin->elems->traverse();

}*/

void PriorityQueue::initialize(arrayList* a, int length){
    min = new MinHeap;
    min->initialize(a, length);
}
void PriorityQueue::preOrder(int beg){

  min->preOrder(beg);

}

void PriorityQueue::inOrder(int beg){

  min->inOrder(beg);

}

void PriorityQueue::postOrder(int beg){

  min->postOrder(beg);

}

void PriorityQueue::sort(){

  min->sort();

}

void PriorityQueue::insert(int elem){

    min->insert(elem);

}