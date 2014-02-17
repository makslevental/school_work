#include <iostream>
#include <sstream>
#include "myException.h"
#include "queue.h"
#include "RatinMaze.h"

using namespace std; 
RatInMaze::position* intss_to_ptr(int high, int low);
int* ptr_to_intss(RatInMaze::position* ptr);

/* unit test
int main (){

	RatInMaze* rim = new RatInMaze;
	char maze[13][15]={
		'0','0','0','1','0','0','0','0','0','0','1','0','0','0','0',
		'0','0','0','1','0','0','1','0','0','0','0','0','0','0','0',
		'0','0','0','0','0','0','0','1','1','1','1','1','1','1','1',
		'0','0','0','1','1','1','0','0','1','0','0','1','0','0','0',
		'0','0','0','0','0','1','1','0','0','1','0','0','1','0','0',
		'1','1','0','0','0','1','1','0','0','1','0','0','0','0','0',
		'0','1','1','0','0','1','1','0','0','1','0','0','0','0','0',
		'0','0','1','0','0','1','1','0','0','1','0','0','0','0','0',
		'0','1','1','0','0','1','0','0','0','0','0','0','0','0','0',
		'0','0','1','0','0','0','1','1','1','1','1','1','1','1','1',
		'0','0','1','0','1','0','0','0','0','0','0','0','0','0','0',
		'0','0','1','0','1','0','0','0','1','0','0','0','0','0','0',
		'0','0','0','0','1','0','0','1','0','0','0','0','0','0','0' };

	rim->load(maze,13,15);

	rim->current_pos = &rim->maze[2][5];
	cout << rim->current_pos << endl;
	
	rim->qoi->push_position_ptr(rim->current_pos);
	cout << rim->qoi->front_position_ptr() << endl;
	rim->qoi->pop_position_ptr();
	rim->qoi->print();

	rim->qoi->push_position_ptr(rim->current_pos);
	cout << rim->qoi->front_position_ptr() << endl;
	rim->qoi->pop_position_ptr();
	rim->qoi->print();

	rim->qoi->push_position_ptr(rim->current_pos);
	cout << rim->qoi->back_position_ptr() << endl;
	rim->qoi->pop_position_ptr();
	rim->qoi->print();

	rim->qoi->push_position_ptr(rim->current_pos);
	cout << rim->qoi->back_position_ptr() << endl;
	rim->qoi->pop_position_ptr();
	rim->qoi->print();

	
	queue *bob = new queue;
	
	for(int i = 0; i < 10; i++){
		bob->push(i);
		bob->print();
		cout << "size " << bob->size() << endl;
	}

	cout << "************" << endl;
	
	for(int i = 0; i < 10; i++){
		bob->pop();
		bob->print();
	}
	
	cout << "************" << endl;
	
	for(int i = 0; i < 10; i++){
		bob->push(i);
		bob->print();
	}
	
	
}
*/
//front is left side. queue grows right
queue::queue(int initialCapacity){// Constructor.
	if (initialCapacity < 1){
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    qoui = new arrayList(arrayLength);
    theFront = 0;
    theBack = 0;
}

int* queue::front(){// return front element
	if (empty()){
	   	ostringstream s;
	    s << "Queue is empty";
	    throw illegalParameterValue(s.str());
    }
    return (qoui->get(theFront));
}

int* queue::back(){// return theBack element
	if (empty()){
	   	ostringstream s;
	    s << "Queue is empty";
	    throw illegalParameterValue(s.str());
    }
    return (qoui->get(theBack-1));
}

void queue::pop(){// remove theFront element
	if (empty()){
	   	ostringstream s;
	    s << "Queue is empty";
	    throw illegalParameterValue(s.str());
    }
  	qoui->erase(theFront);
  	theBack--;
}

void queue::push(const int& theElement){// Add theElement to queue.
   // put theElement at the theBack of the queue
   qoui->insert(theBack++, theElement);
   
}

void queue::print(){
	cout << "front " << theFront << endl;
	cout << "back " << theBack << endl;
	qoui->traverse();
}

RatInMaze::position* queue::front_position_ptr(){
	if (empty()){
		   	ostringstream s;
		    s << "Queue is empty";
		    throw illegalParameterValue(s.str());
    }

	static RatInMaze::position* ptr;
	ptr = intss_to_ptr(*qoui->get(theFront),*qoui->get(theFront+1));
	return ptr;	

}
/*using 2 auxilliary methods ptr_to_ints and ints_to_ptr position pointers are stored on the int stack. 
the position pointers are broken up into high and low bits and stored sequentially 
queue is seen as growing left to right. ptrs are therefore inserted left to right
high then low so if you looked at the queue with ptrints in them you would read the 
addresses two at a time left to right as usual.*/
void queue::push_position_ptr(RatInMaze::position* pos){

	static int highAndLow[2];
	highAndLow[0] = ptr_to_intss(pos)[0];
	highAndLow[1] = ptr_to_intss(pos)[1];
	//cout<< "high " << highAndLow[0] << " low " << highAndLow[1];
	push(highAndLow[0]);
	push(highAndLow[1]);

}
RatInMaze::position* queue::back_position_ptr(){
	if (empty()){
		   	ostringstream s;
		    s << "Queue is empty";
		    throw illegalParameterValue(s.str());
    }

	static RatInMaze::position* ptr;
	ptr = intss_to_ptr(*qoui->get(theBack-2),*qoui->get(theBack-1));
	return ptr;	

}
//since ptrs on 64 bit systems are 64 bits they require 2 positions in the stack. hence 2 pops.
void queue::pop_position_ptr(){
	pop();
	pop();
}

// converts 2 ints into a pointer of position type. int high is are the 32 high bits and int low are the 32 low bits
RatInMaze::position* intss_to_ptr(int high, int low){
	long HIGH = (long)high;
	long LOW = (long)low;
	HIGH = HIGH << 32;

	long ptr;
	ptr = HIGH | LOW;
	RatInMaze::position* final_ptr;
	final_ptr = (RatInMaze::position*)ptr;
	return final_ptr;
}
// converts 64 bit position pointer to 2 ints. return pointer to array with high bits at index 0 and low bits at index
// 1
int* ptr_to_intss(RatInMaze::position* ptr){
	long longPtr = (long)ptr;
	long low = longPtr << 32;
	low = low >> 32;
	long high = longPtr >> 32;
	int HIGH = (int)high;
	int LOW = (int)low;
	static int highLow[2];
	highLow[0] = HIGH;
	highLow[1] = LOW;
	int* final_ptr = highLow;
	return final_ptr;
}