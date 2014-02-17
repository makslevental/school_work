/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/
#include <iostream>
#include <sstream>
#include <string>
#include "Myexception.h"
#include "Chain.h"

using namespace std; 

// constructor
chain::chain(int initialCapacity){
	try
	{
   		if (initialCapacity < 1)
   		{
			ostringstream s;
    			s << "Initial capacity = " 
      				<< initialCapacity << " Must be > 0";
    			throw illegalParameterValue(s.str());
		}
	}
	catch(illegalParameterValue& e){
		e.outputMessage();
		return;
	} 
	firstNode = NULL;
	listSize = 0;
}

// copy constructor
chain::chain(const chain& theList){
	listSize = theList.listSize;
	//empty list
	if(listSize == 0){
		firstNode = NULL;
		return;
	}
	// non-empty list
	chainNode* sourceNode = theList.firstNode; // node to copy from
	firstNode = new chainNode(sourceNode->element); // copy first elem of list
	sourceNode = sourceNode->next;
	chainNode* targetNode = firstNode; // current last node in *this
	// copy remaining elements
	while(sourceNode != NULL){
		targetNode->next = new chainNode(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL; // end of chain
}	
// destructr
chain::~chain(){
	while(firstNode != NULL){
		chainNode* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

// return element whose index is theIndex
int* chain::get(int theIndex) const{
	// throw illegalIndex if no such element
	try{
		checkIndex(theIndex);
	}
	catch(illegalIndex &e){
		e.outputMessage();
		return NULL;
	}

	// move to desired node
	chainNode* currentNode = firstNode;
	for(int i = 0; i < theIndex; i++){
		currentNode = currentNode->next;
	}
	int* p = &currentNode->element;
	return p;
}

// return index of first occurrence 
// return -1 if theElement not in list
int chain::indexOf(const int& theElement) const{
	// search chain for theElement
	chainNode* currentNode = firstNode;
	int index = 0; // index of the currentNode
	while(currentNode != NULL && currentNode->element != theElement){
		// move to next node
		currentNode = currentNode->next;
		index++;
	}

	if(currentNode == NULL) return -1;
	else return index;
}

// delete the element whose index is theIndex
void chain::erase(int theIndex){
	// throw illegalIndex if no such element
	try{
		checkIndex(theIndex);
	}
	catch(illegalIndex &e){
		e.outputMessage();
		return;
	}

	// valid index, locate node with element to delete
	chainNode* deleteNode;
	// remove first node from chain
	if(theIndex == 0){
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	// else use p to get predecessor of desired node
	else{
		chainNode* p = firstNode;
		for(int i = 0; i < theIndex - 1; i++){
			p = p->next;
		}
		deleteNode = p->next;
		p->next = p->next->next; // remove deleteNode from chain
	}
	listSize--;
	delete deleteNode;
}

// insert theElement so that its index is theIndex
void chain::insert(int theIndex, const int& theElement){
	// invalid index
	try{
   		if (theIndex < 0 || theIndex > listSize)
   		{// invalid index
    		// code to throw an exception comes here
			ostringstream s;
    			s << "index = " << theIndex << " size = " 
                    		<< listSize<<", the input index is invalid";
    			throw illegalIndex(s.str());
		}
	}
	catch(illegalIndex &e){
		e.outputMessage();
		return;
	}	
	// insert at front
	if(theIndex == 0){
		firstNode = new chainNode(theElement, firstNode);
	}
	// find predecessor of new element
	else{
		chainNode* p = firstNode;
		for(int i = 0; i < theIndex - 1; i++){
			p = p->next;
		}
		// insert after p
		p->next = new chainNode(theElement, p->next);
	}
	listSize++;
}

// put the list into the stream out
void chain::output(ostream& out) const{
	for(chainNode* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
		out << currentNode->element << " ";
}

void chain::traverse(){
	
	output(cout);

}

// Verify that theIndex is between 0 and listSize - 1.
void chain::checkIndex(int theIndex) const{
   if (theIndex < 0 || theIndex >= listSize)
   {ostringstream s;
    s << "index = " << theIndex << " size = " << listSize;
    throw illegalIndex(s.str());
   }
}

void chain::MaxMin(){
	int min = this->firstNode->element;
	int max = this->firstNode->element;
	for(chainNode* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next){
		if(min > currentNode->element) min = currentNode->element;
		if(max < currentNode->element) max = currentNode->element;
 	}

 	cout << "The maximum element is " << min << endl;
 	cout << "The minimum element is " << max << endl;
}