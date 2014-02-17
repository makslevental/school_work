#include <iostream>
#include <sstream>
#include "myException.h"

#include "Arraylist.h"

using namespace std; 


arrayList::arrayList(int initialCapacity)
{// Constructor.
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

	arrayLength = initialCapacity;
   	element = new int[arrayLength];
   	listSize = 0;
}


arrayList::arrayList(const arrayList& theList)
{// Copy constructor.
   	arrayLength = theList.arrayLength;
   	listSize = theList.listSize;
   	element = new int[arrayLength];
   	copy(theList.element, theList.element +
                         listSize, element);
}

void arrayList::changeValue(int theIndex, int newValue){
	try{
		checkIndex(theIndex);
	}
	catch(illegalIndex &e){
		e.outputMessage();
		return;
	}
	element[theIndex]=newValue;

}

void arrayList::checkIndex(int theIndex) const
{
// Verify that theIndex is between 0 and 
 // listSize - 1.

   	if (theIndex < 0 || theIndex >= listSize){
		ostringstream s;
    		s << "index = " << theIndex << " size = " 
                    << listSize<<", the input index is invalid";
    		throw illegalIndex(s.str());
	}
 
}

void arrayList::changeLength1D(int*& a, int oldLength, 
                           int newLength)
{
	int* temp = new int[newLength];     
       // new array
   	int number = min(oldLength, newLength); 
       // number to copy
   	copy(a, a + number, temp);
   	delete [] a;                    
       // deallocate old memory
   	a = temp;
}


int* arrayList::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such
 // element.
	try{
		checkIndex(theIndex);
	}
	catch(illegalIndex &e){
		e.outputMessage();
		return NULL;
	}
	return &element[theIndex];
}


int arrayList::indexOf(const int& theElement)
                                        const
{
   	// Return index of first occurrence of theElement.
   	// search for theElement
   	int theIndex = -1;
   	for(int i=0; i<listSize;i++){
     		if(element[i]==theElement){
       	theIndex=i;
       	break;
     		}
   	}
   // check if theElement was found
   	if (theIndex == listSize)return -1; // not found
   	else return theIndex;
 }


void arrayList::erase(int theIndex)
{// Delete the element whose index is theIndex.
	try{
		checkIndex(theIndex);
	}
	catch(illegalIndex &e){
		e.outputMessage();
		return;
	}
   // valid index, shift elements with higher index
	copy(element + theIndex + 1, element + 
                   listSize,element + theIndex);
        --listSize;


  }


void arrayList::insert(int theIndex, 
                          const int& theElement)
{// Insert theElement.
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
	// valid index, make sure we have space
   	if (listSize == arrayLength)
      	{// no space, double capacity
         	changeLength1D(element, arrayLength, 
                             2 * arrayLength);
         	arrayLength *= 2;
		//cout << "No space!! The capacity of the list is going to double!"<<endl;
		//cout<<"The new capacity of the list is "<<capacity()<<endl;
		//return;
	}
	// shift elements right one position
   	copy_backward(element + theIndex, 
                 element + listSize,
                 element + listSize + 1);

   	element[theIndex] = theElement;
   	listSize++;
 }


void arrayList::traverse()
{
  	if(listSize==0){
    		cout<<"List is Empty"<<endl;
    		return;
  	}
  	for (int i= 0; i<listSize;i++) {
    		cout<<element[i]<<" ";
  	}
  	cout<<endl;
}


void arrayList::MaxMin(){
	if(listSize==0){
    		cout<<"List is Empty"<<endl;
   	 return;
	}
	int max=-100000;
	int min=100000;
	for (int i= 0; i<listSize;i++) {
		if(element[i]>max)max=element[i];
		if(element[i]<min)min=element[i];    		
  	}
	cout<<"The maximum element in the list is "<<max<<endl;
	cout<<"The minimum element in the list is "<<min<<endl;

}
