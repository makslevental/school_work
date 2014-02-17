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
#include "BinaryTree.h"

using namespace std;

/*int main(){


  arrayList *a = new arrayList();
  for (int i = 0; i < 10; i++){
        a->insert(i, 10-i); //rand()%100*
  }

  BinaryTree* bin;
  bin = new BinaryTree;
  bin->initialize(a,10);
  // bin->preOrder(0);
  // cout << endl;
  // bin->inOrder(0);
  // cout << endl;
  // bin->postOrder(0);
  // cout << endl;
  // bin->sort();
  bin->insert(1);
  bin->insert(5);
  bin->insert(2);
  // bin->preOrder(0); 
  bin->elems->traverse();
}*/

void BinaryTree::initialize(arrayList *a, int length){
  
  this->size = length;
  elems = new arrayList(size+1);

  elems->insert(0,99999);
  for(int i = 1; i <= size; i++){
    elems->insert(i,*(a->get(i-1)));
  }
  // cout << "base array " << endl;
  // elems->traverse();

  for(int i = floor(this->size/2); i >= 1; i--){
      heapify(i,true);
  }
  // cout << "heapified array " << endl;
  // elems->traverse();
  cout << endl;
}

void BinaryTree::heapify(int index, bool minMax){

  int parent = index;
  int leftChild = 2*index;
  int rightChild = 2*index + 1;

  if(minMax == true){

      if(leftChild <= size && *elems->get(leftChild) < *elems->get(parent)){
          int templChild = *elems->get(leftChild);
          int temppR = *elems->get(parent);
          parent = leftChild;
      }
          
      if(rightChild <= size && *elems->get(rightChild) < *elems->get(parent)){
          int temprChild = *elems->get(rightChild);
          int temppR = *elems->get(parent);
          parent = rightChild;
      }
      if(parent != index){
          //swap elems[parent] <-> elems[index]
          
          int temp1 = *elems->get(index);
          int temp2 = *elems->get(parent);
          
          elems->erase(index);
          elems->insert(index, temp2);

          elems->erase(parent);
          elems->insert(parent, temp1);

          heapify(parent, minMax);
      }}

  if(minMax == false){

      if(leftChild <= size && *elems->get(leftChild) > *elems->get(parent)){
          int templChild = *elems->get(leftChild);
          int temppR = *elems->get(parent);
          parent = leftChild;
      }
          
      if(rightChild <= size && *elems->get(rightChild) > *elems->get(parent)){
          int temprChild = *elems->get(rightChild);
          int temppR = *elems->get(parent);
          parent = rightChild;
      }
      if(parent != index){
          //swap elems[parent] <-> elems[index]
          
          int temp1 = *elems->get(index);
          int temp2 = *elems->get(parent);
          
          elems->erase(index);
          elems->insert(index, temp2);

          elems->erase(parent);
          elems->insert(parent, temp1);

          heapify(parent, minMax);
      }}

  
  
}
void BinaryTree::preOrder(int beg){
    preOrder1(beg+1);
}

void BinaryTree::preOrder1(int beg){
    cout << *elems->get(beg) << " ";
    if(2*beg < size+1)
        preOrder1(2*beg);
    
    if(2*beg + 1 < size+1)
        preOrder1(2*beg+1);
}

void BinaryTree::inOrder(int beg){
        inOrder1(beg+1);
}

void BinaryTree::inOrder1(int beg){
    
    if(2*beg < size+1)
        inOrder1(2*beg);

    cout << *elems->get(beg) << " ";
    
    if(2*beg + 1 < size+1)
        inOrder1(2*beg+1);
        

}

void BinaryTree::postOrder(int beg){
        postOrder1(beg+1);
}

void BinaryTree::postOrder1(int beg){
    
    if(2*beg < size+1)
        postOrder1(2*beg);
    
    if(2*beg + 1 < size+1)
        postOrder1(2*beg+1);

    cout << *elems->get(beg) << " ";  
        

}
int BinaryTree::pop(){
    size--;
    int temp = *elems->get(0);
    elems->erase(0);
    return temp;
}
void BinaryTree::sort(){
  int tempSize = size;
  for(int j = size; j >=1; j--, size--){    
  
      for(int i = floor(j/2); i >= 1; i--){
          heapify(i,false);
      }
      // cout << "heapified array"
      // elems->traverse();
      // swap root <-> last position
      
      int temp1 = *elems->get(1);
      
      elems->insert(j+1, temp1);
      elems->erase(1);
      // cout << "sorted array"
      // elems->traverse();

  
  }
  size = tempSize;
  arrayList b = *elems;
  delete elems;
  elems = &b;
  this->pop();
  while(size > -1){
      cout << this->pop() << " ";
  }


}

void BinaryTree::percolateUp(int index){

    int parent = *elems->get(floor(index/2));
    int elem = *elems->get(index);
    // minheap insert
    if(parent > elem){
            
        elems->erase(floor(index/2));
        elems->insert(floor(index/2), elem);
        elems->erase(index);
        elems->insert(index,parent);
        percolateUp((int)floor(index/2));

    }

}

void BinaryTree::insert(int elem){

    elems->insert(++size, elem);
    percolateUp(size);


}