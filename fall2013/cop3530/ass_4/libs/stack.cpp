#include <iostream>
#include <sstream>
#include "myException.h"
#include "stack.h"

using namespace std; 
RatInMaze::position* ints_to_ptr(int high, int low);
int* ptr_to_ints(RatInMaze::position* ptr);
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
	rim->stak = new stack;
	
	rim->stak->push_position_ptr(rim->current_pos);
	cout << rim->stak->top_position_ptr() << endl;
	rim->stak->pop_position_ptr();
	rim->stak->print();

	rim->stak->push_position_ptr(rim->current_pos);
	cout << rim->stak->top_position_ptr() << endl;
	rim->stak->pop_position_ptr();
	rim->stak->print();
	
	stack *bob = new stack;
	for(int i = 0; i < 10; i++){
		bob->push(i);
		bob->print();
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
stack::stack(int initialCapacity){
	if (initialCapacity < 1){
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    stak = new arrayList(arrayLength);
    stackTop = -1;
}

int* stack::top(){
	if (stackTop == -1){
	   	ostringstream s;
	    s << "Stack is empty";
	    throw illegalParameterValue(s.str());
    }
	return stak->get(stackTop);
}
void stack::pop(){
	if (stackTop == -1){
	   	ostringstream s;
	    s << "Stack is empty";
	    throw illegalParameterValue(s.str());
    }
    stak->erase(stackTop--);  // destructor for T
}

void stack::push(const int& theElement){
	stak->insert(++stackTop, theElement);
}

void stack::print(){
	cout << "top index " << stackTop;	
	stak->traverse();
}

/*using 2 auxilliary methods ptr_to_ints and ints_to_ptr position pointers are stored on the int stack. 
the position pointers are broken up into high and low bits and stored sequentially 
stack is seen as growing left to right. ptrs are therefore inserted left to right
high then low so if you looked at the stack with ptr-ints in them you would read the 
addresses two at a time left to right as usual, as you would if wrote out the address on paper.*/
void stack::push_position_ptr(RatInMaze::position* pos){

	static int highAndLow[2];
	highAndLow[0] = ptr_to_ints(pos)[0];
	highAndLow[1] = ptr_to_ints(pos)[1];
	//cout<< "high " << highAndLow[0] << " low " << highAndLow[1];
	push(highAndLow[0]);
	push(highAndLow[1]);

}
// 
RatInMaze::position* stack::top_position_ptr(){
	if (stackTop == -1){
		   	ostringstream s;
		    s << "Stack is empty";
		    throw illegalParameterValue(s.str());
    }

	static RatInMaze::position* ptr;
	ptr = ints_to_ptr(*stak->get(stackTop-1),*stak->get(stackTop));
	return ptr;	

}

//since ptrs on 64 bit systems are 64 bits they require 2 positions in the stack. hence 2 pops.
void stack::pop_position_ptr(){
	pop();
	pop();
}

// converts 2 ints into a pointer of position type. int high is are the 32 high bits and int low are the 32 low bits
RatInMaze::position* ints_to_ptr(int high, int low){
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
int* ptr_to_ints(RatInMaze::position* ptr){
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