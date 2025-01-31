#ifndef _arraylist
#define _arraylist
#include "Arraylist.h"
#endif

#ifndef _stack
#define _stack

#include "RatinMaze.h"

using namespace std; 

class stack : public arrayList{
   	public:
      	    stack(int initialCapacity = 10);
	    ~stack(){delete [] stak;}
	    bool empty() const {return stackTop == -1;}
	    int size() const
	          {return stackTop + 1;}
	    int* top();
	    void pop();
	    void push(const int& theElement);
	    void print();
		RatInMaze::position* top_position_ptr();
	    void push_position_ptr(RatInMaze::position* pos);
	    void pop_position_ptr();
	
	private:
	    int stackTop;         // current top of stack, contains element
	    int arrayLength;      // stack capacity
	    arrayList *stak;      // element array
};
#endif
