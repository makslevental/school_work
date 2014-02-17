#ifndef _arraylist
#define _arraylist
#include "Arraylist.h"
#endif

#ifndef _queue
#define _queue

#include "RatinMaze.h"
using namespace std; 

class queue:public arrayList{
  public:
    // constructor, copy constructor and destructor
    queue(int initialCapacity = 10);
    //queue(const queue& theList); copy constructor
    ~queue(){delete [] qoui;}
    bool empty() const {return theFront == theBack;}
    int size() const {return (theBack - theFront);}
    
    int* front();
    int* back();
    void pop();
    void push(const int& theElement);
    void print();
    RatInMaze::position* back_position_ptr();
    RatInMaze::position* front_position_ptr();
    void push_position_ptr(RatInMaze::position* pos);
    void pop_position_ptr();


  private:
    int theFront;       // should be the left end
    int theBack;        // the right end, +1 of the correct index
    int arrayLength;    // queue capacity
    arrayList* qoui;    // element array
};



#endif