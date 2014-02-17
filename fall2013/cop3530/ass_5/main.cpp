
#include <iostream>
#include "PriorityQueue.h"
using namespace std;




int main (){
	PriorityQueue *m = new PriorityQueue();
	arrayList *a = new arrayList();
	for (int i = 0; i < 10; i++)
    	 	a->insert(i, 10-i);
	m->initialize(a, 10);
	cout<<"The inorder travesal is: ";
	m->inOrder(0);
	cout<<endl;
	cout<<"The preorder travesal is: ";
	m->preOrder(0);
	cout<<endl;
	cout<<"The postorder travesal is: ";
	m->postOrder(0);
	cout<<endl;
	cout<<"The sorted list is: ";
	m->sort();
	cout<<endl;

}



